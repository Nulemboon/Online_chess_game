#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <poll.h>
#include <sys/wait.h>

#include "game.cpp"
#include "message/message.h"
#include "database/database.h"

#define MAX_CLIENTS 100
#define BUFF_SIZE 1024
#define MAX_QUEUE_TIME 30
#define HEADER_SIZE 3

struct Client {
    int sockfd;
    std::string username;
    int ELO;
    int gameID;
    int failLogin;
    std::chrono::system_clock::time_point start;
};

std::vector<Client> waitingQueue;

struct Client clients[MAX_CLIENTS];
std::unordered_map<std::string, int> session; //logged-in users
// int client_count = 0;
std::unordered_map<int, ChessGame*> gameList; //map from gameID to chess game
int lastGameID;
std::unordered_map<int, std::pair<int, int>> playerMap; // map from gameID to client socket
std::vector<std::pair<std::string, int>> readyList; //ready-to-play players
std::unordered_map<int, std::string> movesMap; //matches' moves log
Database *db;

//Get Random Number
int randm(int min, int max) {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Generate and return a random number
    return min + std::rand() % (max - min + 1);
}

void sendMessage(int sockfd, Message *message) {
    int n = write(sockfd, message->serialize().c_str(), message->getLength() + HEADER_SIZE);
    if (n < 0) {
        std::cerr << "Error sending message" << std::endl;
    }
}

void registerUser(int index, Message *message) {
    // Construct UserMessage from Message
    UserMessage *userMessage = new UserMessage(*message);

    // Add user to database
    int status = db->addUser(userMessage->getUsername(), userMessage->getPassword());
    Message* replyMessage;
    switch (status) {
        case 1: // Success
            replyMessage = new Message(REGISTER_SUCCESSFUL);
            std::cout << "User " << userMessage->getUsername() << " added to database" << std::endl;
            break;

        case 0: // Username taken
            replyMessage = new Message(REGISTER_USERNAME_EXISTED);
            break;

        default: // Error encountered
            std::string err(sqlite3_errmsg(db->getConnection()));
            replyMessage = new ErrorMessage(err);
            break;
    }
    sendMessage(clients[index].sockfd, replyMessage);
    delete replyMessage;
    delete userMessage;
}

void login(int index, Message* msg) {
    // Construct UserMessage from Message
    UserMessage *acc = new UserMessage(*msg);
    Message* replyMessage; // Message for reply

    // Check if this user is currently blocked
    if (clients[index].failLogin >= 5) {
        replyMessage = new Message(USER_BLOCKED);
        sendMessage(clients[index].sockfd, replyMessage);
        delete replyMessage;
        delete acc;
    }

    // Check if this user is already logged in
    if (session.find(acc->getUsername()) != session.end()) {
        replyMessage = new Message(USER_LOGGED_IN);
        sendMessage(clients[index].sockfd, replyMessage);
        delete replyMessage;
        delete acc;
        return;
    }

    // Validate user
    int status = db->validateUser(acc->getUsername(), acc->getPassword());
    std::cout << "User '" << acc->getUsername() << "' logging in:" << (status == 1?"Correct credentials":status == 0?"Wrong credentials":"Error occured") << std::endl;

    std::string username = acc->getUsername();

    switch (status) {
        case 1:
            // Send login success message
            replyMessage = new Message(LOGIN_SUCCESSFUL);
            sendMessage(clients[index].sockfd, replyMessage);
            session.insert({username, index}); // Add this user to the online list
            clients[index].failLogin = 0; // Clear failed login records
            clients[index].ELO = db->getELO(clients[index].username);
            break;
        case 0:
            // Send login failure message (Wrong password)
            clients[index].failLogin += 1;
        case 2:
            // Send login failure message (Wrong username)
            replyMessage = new Message(LOGIN_FAIL);
            sendMessage(clients[index].sockfd, replyMessage);
            break;
        default:
            // Send error message
            std::string err(sqlite3_errmsg(db->getConnection()));
            replyMessage = new ErrorMessage(err);
            sendMessage(clients[index].sockfd, replyMessage);
            break;
    }
}

void logout(int index) {
    std::string username = clients[index].username;

    session.erase(username);
    
    sendMessage(clients[index].sockfd, new Message(OK));
}


void seeHistory(int index) {
    // Get history
    std::vector<std::map<std::string, std::string>> matchList = db->getHistory(clients[index].username);
    std::cout << "User '" << clients[index].username << "' see his history" << std::endl;

    // Send history message
    HistoryMessage* historyMsg = new HistoryMessage(HISTORY, matchList);
    sendMessage(clients[index].sockfd, historyMsg);
    delete historyMsg;
}

//Search by ID and send back match log 
void seeMatch(int index, Message *msg) {
    // Construct MatchMessage from Message
    MatchMessage* matchMsg = new MatchMessage(*msg);
    // Get match
    int match_id = matchMsg->getMatchID();
    std::vector<std::map<std::string, std::string>> match = db->getMatch(match_id);
    std::cout << "User '" << clients[index].username << "' see his match " << match_id << std::endl;

    // Send match message
    HistoryMessage* historyMsg = new HistoryMessage(MATCH, match);
    sendMessage(clients[index].sockfd, historyMsg);
    delete historyMsg;
    delete matchMsg;
}

void createRoom(int index) {
    std::string username = clients[index].username;


    int ELO = clients[index].ELO;
    readyList.push_back({username, ELO});
    // sendMessage(index, new Message(OK));
}

void deleteRoom(int index) {
    for (int i = 0; i < readyList.size(); i++) {
        if (readyList[i].first == clients[index].username) {
            readyList.erase(readyList.begin() + i);
            break;
        }
    }
}

//Begin new match
void newMatch(int white, int black) {
    int gameID = lastGameID++;
    gameList.insert({gameID, new ChessGame()});
    playerMap.insert({gameID, {white, black}});
    clients[white].gameID = gameID;
    clients[black].gameID = gameID;
}

void invite(int index, Message* msg) {
    UserMessage* userMsg = new UserMessage(*msg);
    std::string username = userMsg->getUsername();
    std::string curName = clients[index].username;
    
    char buffer[BUFF_SIZE];
    int receiver = session[username];
    UserMessage* invite = new UserMessage(INVITE, curName, "");
    sendMessage(receiver, invite);
}

void accept_invite(int index, Message* msg) {
    UserMessage* userMsg = new UserMessage(*msg);
    std::string username = userMsg->getUsername();
    int op_index = session[username];

    if (clients[op_index].gameID != 0) {
        if (randm(0, 1)) {
            sendMessage(clients[index].sockfd, new UserMessage(MATCH_FOUND, "W", ""));
            sendMessage(clients[op_index].sockfd, new UserMessage(MATCH_FOUND, "B", ""));

            newMatch(index, op_index);
        } else {
            sendMessage(clients[index].sockfd, new UserMessage(MATCH_FOUND, "B", ""));
            sendMessage(clients[op_index].sockfd, new UserMessage(MATCH_FOUND, "W", ""));

            newMatch(op_index, index);
        }
    } else {
        sendMessage(clients[index].sockfd, new Message(NOT_OK));
    }
    
}


void afterMatch(int gameID, int white, int black, int res) {
    //update maps
    gameList.erase(gameID);
    playerMap.erase(gameID);
    clients[white].gameID = 0;
    clients[black].gameID = 0;

    if (res == 0) {
        int change = abs(clients[white].ELO - clients[black].ELO) / 10;
        if (clients[white].ELO > clients[black].ELO) {
            clients[white].ELO -= change;
            clients[black].ELO += change;
        } else {
            clients[white].ELO += change;
            clients[black].ELO -= change;
        }
    } else {
        int change = 25 - abs(clients[white].ELO - clients[black].ELO) / 10;
        if (res == 1) {
            clients[white].ELO += change;
            clients[black].ELO -= change;
        } else {
            clients[white].ELO -= change;
            clients[black].ELO += change;
        }
    }

    //update database
    db->addMatch(clients[white].username, clients[black].username, res, movesMap[gameID], gameID);
    db->updateELO(clients[white].username, clients[white].ELO);
    db->updateELO(clients[black].username, clients[black].ELO);

    movesMap.erase(gameID);
}

void randomMatch(int index) {

    int ELO = db->getELO(clients[index].username);
    bool flag = false;
    for (int i = 0; i < waitingQueue.size(); i++) {
        if (abs(waitingQueue[i].ELO - ELO) <= 100) {
            UserMessage* found = new UserMessage(MATCH_FOUND, "W", "");
            sendMessage(clients[index].sockfd, new UserMessage(MATCH_FOUND, "B", ""));
            sendMessage(waitingQueue[i].sockfd, new UserMessage(MATCH_FOUND, "W", ""));
            
            //update ready list
            deleteRoom(index);
            deleteRoom(waitingQueue[i].sockfd);

            newMatch(session[waitingQueue[i].username], index);

            waitingQueue.erase(waitingQueue.begin() + i);
            flag = true;
            break;
        }
    }
    //not found match
    if (!flag) {
        waitingQueue.push_back(clients[index]);
        waitingQueue.back().start = std::chrono::system_clock::now();
    }
}

void move(int index, Message *msg) {
    int gameID = clients[index].gameID;
    ChessGame* curGame = gameList[gameID];
    MoveMessage* moveMsg = new MoveMessage(*msg);
    std::string src = moveMsg->getSource();
    std::string dest = moveMsg->getDestination();
    int startRow = (int)(src[0] - '0');
    int startCol = (int)(src[1] - '0');
    int endRow = (int)(dest[0] - '0');
    int endCol = (int)(dest[1] - '0');

    bool valid = curGame->validateMove(curGame->chessboard.MainGameBoard, startRow, startCol, endRow, endCol);
    if (valid) {
        movesMap[gameID] += src + dest + ",";
        curGame->AlternateTurn();
        if (clients[index].sockfd == playerMap[gameID].first) {
            sendMessage(clients[playerMap[gameID].second].sockfd, moveMsg);
        } else {
            sendMessage(clients[playerMap[gameID].first].sockfd, moveMsg);
        }
        Message* rep1;
        Message* rep2;
        switch(curGame->IsGameOver()) {
            case 0: {
                rep1 = new Message(OK);

                sendMessage(clients[playerMap[gameID].first].sockfd, rep1);
                sendMessage(clients[playerMap[gameID].second].sockfd, rep2);
                break;
            }
            case 1: {
                rep1 = new Message(GAME_WIN);
                rep2 = new Message(GAME_LOSE);

                sendMessage(clients[playerMap[gameID].first].sockfd, rep1);
                sendMessage(clients[playerMap[gameID].second].sockfd, rep2);
                
                afterMatch(gameID, playerMap[gameID].first, playerMap[gameID].second, 1);
                break;
            }
            case 2: {
                rep1 = new Message(GAME_WIN);
                rep2 = new Message(GAME_LOSE);

                sendMessage(clients[playerMap[gameID].first].sockfd, rep2);
                sendMessage(clients[playerMap[gameID].second].sockfd, rep1);

                afterMatch(gameID, playerMap[gameID].first, playerMap[gameID].second, 2);
                break;
            }
            case 3: {
                rep1 = new Message(STALEMATE);

                sendMessage(clients[playerMap[gameID].first].sockfd, rep1);
                sendMessage(clients[playerMap[gameID].second].sockfd, rep1);

                afterMatch(gameID, playerMap[gameID].first, playerMap[gameID].second, 0);
                break;
            }
            case 4: {
                rep1 = new Message(THREE_FOLD);

                sendMessage(clients[playerMap[gameID].first].sockfd, rep1);
                sendMessage(clients[playerMap[gameID].second].sockfd, rep1);

                afterMatch(gameID, playerMap[gameID].first, playerMap[gameID].second, 0);
                break;
            }
            case 5: {
                rep1 = new Message(FIFTY);

                sendMessage(clients[playerMap[gameID].first].sockfd, rep1);
                sendMessage(clients[playerMap[gameID].second].sockfd, rep1);

                afterMatch(gameID, playerMap[gameID].first, playerMap[gameID].second, 0);
                break;
            }
            
            default: {}
        }

        delete(rep1);
        delete(rep2);

    } else {
        sendMessage(clients[index].sockfd, new Message(MOVE_NOT_OK));
    }
}

void offerDraw(int index) {
    int gameID = clients[index].gameID;

    int opponent = playerMap[gameID].first == index ? playerMap[gameID].second : playerMap[gameID].first;
    sendMessage(clients[opponent].sockfd, new Message(OFFER_DRAW));

}

void accept_draw(int index) {
    int gameID = clients[index].gameID;

    sendMessage(clients[playerMap[gameID].first].sockfd, new Message(GAME_DRAW));
    sendMessage(clients[playerMap[gameID].second].sockfd, new Message(GAME_DRAW));

    afterMatch(gameID, playerMap[gameID].first, playerMap[gameID].second, 0); 
}

void resign(int index) {
    int gameID = clients[index].gameID;

    int opponent;
    int res;
    if (playerMap[gameID].first == index) {
        opponent = playerMap[gameID].second;
        res = 2;
    } else {
        opponent = playerMap[gameID].first;
        res = 1;    
    }

    sendMessage(clients[index].sockfd, new Message(GAME_LOSE));
    sendMessage(clients[opponent].sockfd, new Message(GAME_WIN));

    afterMatch(gameID, playerMap[gameID].first, playerMap[gameID].second, res);
}


void handleClient(int index) {
    char buff[BUFF_SIZE];
    int n;

    while ((n = read(clients[index].sockfd, buff, BUFF_SIZE)) > 0) {
        std::string rcv(buff, n);
        // Construct Message from string of message received
        Message *msg = new Message(rcv);
        switch (msg->getType()) {
            case OK:
                break;

            case NOT_OK:
                break;

            case SEE_HISTORY:
                seeHistory(index);
                break;

            case RANDOM_MATCHMAKING:
                randomMatch(index);
                break;

            case CREATE_ROOM:
                createRoom(index);
                break;

            case OFFER_DRAW:
                offerDraw(index);
                break;

            case RESIGN:
                resign(index);
                break;

            case REGISTER: // <username> <password>
                registerUser(index, msg);
                break;

            case LOGIN: // <username> <password>
                login(index, msg);
                break;

            case LOGOUT: // <username>
                logout(index);
                break;

            case INVITE: // <username>
                invite(index, msg);
                break;

            case MOVE: // <source_position> <destination_position>
                move(index, msg);
                break;

            case DELETE_ROOM: // <username>
                deleteRoom(index);
                break;

            case ACCEPT_INVITE: // <username>
                accept_invite(index, msg);
                break;

            case ACCEPT_DRAW: 
                accept_draw(index);
                break;
            // case REJECT_INVITE: // <username>
            //     break;

            case SEE_MATCH: // <match_id>
                seeMatch(index, msg);
                break;
            
            default:
                break;
        }
    }

    if (n < 0) {
        perror("Read error");
        exit(1);
    } else if (n == 0) {
        std::cout << "Client disconnected\n";
        close(clients[index].sockfd);
        clients[index].sockfd = 0;

        deleteRoom(index);
        if (clients[index].gameID != 0) {
            int gameID = clients[index].gameID;
            int op_index;
            int res;
            if (index == playerMap[gameID].first) {
                res = 2;
                op_index = playerMap[gameID].second;
            } else {
                res = 1;
                op_index = playerMap[gameID].first;
            }
            sendMessage(clients[op_index].sockfd, new Message(GAME_WIN));
            afterMatch(gameID, playerMap[gameID].first, playerMap[gameID].second, res);
        }
    }
}

void checkWaitingQueue() {
    while (1) {
        auto curTime = std::chrono::system_clock::now();
        for (int i = 0; i < waitingQueue.size(); i++) {
            int sockfd = waitingQueue[i].sockfd;
            auto queueTime = std::chrono::duration_cast<std::chrono::seconds>(curTime - waitingQueue[i].start).count();
            if (queueTime >= MAX_QUEUE_TIME) {
                waitingQueue.erase(waitingQueue.begin() + i);
                Message* timeout = new Message(MATCHMAKING_TIMEOUT);
                sendMessage(sockfd, timeout);
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    int server_fd, new_socket, activity, i, valread;
    int opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFF_SIZE];

    // Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // Set socket non blocking
    if (ioctl(server_fd, FIONBIO, (char *)&opt) < 0) {
        perror("ioctl() failed");
        close(server_fd);
        exit(0);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    // Initialize the clients array
    for (i = 0; i < MAX_CLIENTS; i++) {
        clients[i].sockfd = 0;
        clients[i].username = "";
        clients[i].gameID = 0;
    }

    while (1) {
        struct pollfd fds[MAX_CLIENTS + 1];

        // Add server socket to the set
        fds[0].fd = server_fd;
        fds[0].events = POLLIN;

        // Add client sockets to the set
        for (i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i].sockfd > 0) {
                fds[i + 1].fd = clients[i].sockfd;
                fds[i + 1].events = POLLIN;
            } else {
                fds[i + 1].fd = -1;
            }
        }

        // Use poll to wait for activity on any of the sockets
        activity = poll(fds, MAX_CLIENTS + 1, -1);

        if (activity < 0) {
            perror("Poll error");
            exit(EXIT_FAILURE);
        }
        
        // If server socket is readable, there is a new connection
        if (fds[0].revents & POLLIN) {
            if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
                perror("Accept error");
                exit(EXIT_FAILURE);
            }

            // Add the new connection to the clients array
            for (i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i].sockfd == 0) {
                    clients[i].sockfd = new_socket;
                    break;
                }
            }
        }

        // Check each client for activity
        for (i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i].sockfd > 0 && fds[i + 1].revents & POLLIN) {
                handleClient(i);
            }
        }
    }

    return 0;
}
