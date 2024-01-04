#include <bits/stdc++.h>

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>

#include "game.cpp"
#include "message/message.h"
#include "database/database.h"

const int PORT = 5500;
const int BACKLOG = 5;
const int BUFF_SIZE = 1024;
const int HEADER_SIZE = 3;
const int MAX_QUEUE_TIME = 30;

struct Client {
    int clientSock;
    std::string username;
    int ELO;
    std::chrono::time_point<std::chrono::system_clock> start;
};

std::unordered_map<std::string, int> session;
std::vector<Client> waitingQueue;
std::unordered_map<int, ChessGame> gameList; //map fron gameID to chess game
std::unordered_map<int, int> gameMap; //map from client socket to gameID
std::unordered_map<int, std::pair<int, int>> playerMap; // map from gameID to client socket
std::vector<std::pair<std::string, int>> readyList; //ready-to-play players

void sendMessage(int clientSocket, Message *message) {
    int n = send(clientSocket, message->serialize().c_str(), message->getLength() + HEADER_SIZE, 0);
    if (n < 0) {
        std::cerr << "Error sending message" << std::endl;
    }
}

void registerUser(int clientSocket, Message *message, Database *db) {
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
    sendMessage(clientSocket, replyMessage);
    delete replyMessage;
    delete userMessage;
}

void login(int clientSocket, Message* msg, std::string *username, int *failLogin, Database* db) {
    // Construct UserMessage from Message
    UserMessage *acc = new UserMessage(*msg);
    Message* replyMessage; // Message for reply

    // Check if this user is currently blocked
    if (*failLogin >= 5) {
        replyMessage = new Message(USER_BLOCKED);
        sendMessage(clientSocket, replyMessage);
        delete replyMessage;
        delete acc;
    }

    // Check if this user is already logged in
    if (session.find(acc->getUsername()) != session.end()) {
        replyMessage = new Message(USER_LOGGED_IN);
        sendMessage(clientSocket, replyMessage);
        delete replyMessage;
        delete acc;
        return;
    }

    // Validate user
    int status = db->validateUser(acc->getUsername(), acc->getPassword());
    std::cout << "User '" << acc->getUsername() << "' logging in:" << (status == 1?"Correct credentials":status == 0?"Wrong credentials":"Error occured") << std::endl;

    switch (status) {
        case 1:
            // Send login success message
            replyMessage = new Message(LOGIN_SUCCESSFUL);
            sendMessage(clientSocket, replyMessage);
            *username = acc->getUsername(); // Assign the username of this session
            session.insert({*username, clientSocket}); // Add this user to the online list
            *failLogin = 0; // Clear failed login records
            break;
        case 0:
            // Send login failure message (Wrong password)
            *failLogin += 1;
        case 2:
            // Send login failure message (Wrong username)
            replyMessage = new Message(LOGIN_FAIL);
            sendMessage(clientSocket, replyMessage);
            break;
        default:
            // Send error message
            std::string err(sqlite3_errmsg(db->getConnection()));
            replyMessage = new ErrorMessage(err);
            sendMessage(clientSocket, replyMessage);
            break;
    }
}

void logout(int clientSocket) {
    for (auto& p : session) {
        if (p.second == clientSocket) {
            session.erase(p.first);
            sendMessage(clientSocket, new Message(OK));
            return;
        }
    }

    sendMessage(clientSocket, new Message(NOT_OK));
}


void seeHistory(int clientSocket, std::string username, Database* db) {
    // Get history
    std::vector<std::map<std::string, std::string>> matchList = db->getHistory(username);
    std::cout << "User '" << username << "' see his history" << std::endl;

    // Send history message
    HistoryMessage* historyMsg = new HistoryMessage(HISTORY, matchList);
    sendMessage(clientSocket, historyMsg);
    delete historyMsg;
}

//Search by ID and send back match log 
void seeMatch(int clientSocket, std::string username, Message *msg, Database* db) {
    // Construct MatchMessage from Message
    MatchMessage* matchMsg = new MatchMessage(*msg);
    // Get match
    int match_id = matchMsg->getMatchID();
    std::vector<std::map<std::string, std::string>> match = db->getMatch(match_id);
    std::cout << "User '" << username << "' see his match " << match_id << std::endl;

    // Send match message
    HistoryMessage* historyMsg = new HistoryMessage(MATCH, match);
    sendMessage(clientSocket, historyMsg);
    delete historyMsg;
    delete matchMsg;
}

void createRoom(int clientSocket, Database* db) {
    std::string username = "";
    for (auto& p : session) {
        if (p.second == clientSocket) {
            username = p.first;
            break;
        }
    }
    int ELO = db->getELO(username);
    readyList.push_back({username, ELO});
    // sendMessage(clientSocket, new Message(OK));
}

void deleteRoom(int clientSocket) {
    std::string username = "";
    for (auto& p : session) {
        if (p.second == clientSocket) {
            username = p.first;
            break;
        }
    }
    for (int i = 0; i < readyList.size(); i++) {
        if (readyList[i].first == username) {
            readyList.erase(readyList.begin() + i);
        }
    }
}

void invite(int clientSocket, Message* msg) {
    UserMessage* userMsg = new UserMessage(*msg);
    std::string username = userMsg->getUsername();

    int receiver = session[username];

}

void randomMatch(int clientSocket, std::string username, Database* db) {
    int ELO = db->getELO(username);
    bool flag = false;
    for (int i = 0; i < waitingQueue.size(); i++) {
        if (abs(waitingQueue[i].ELO - ELO) <= 100) {
            Message* found = new Message(MATCH_FOUND);
            sendMessage(clientSocket, found);
            sendMessage(waitingQueue[i].clientSock, found);
            
            //update ready list
            deleteRoom(clientSocket);
            deleteRoom(waitingQueue[i].clientSock);

            waitingQueue.erase(waitingQueue.begin() + i);
            flag = true;
            break;
        }
    }
    //not found match
    if (!flag) {
        waitingQueue.push_back(Client(clientSocket, username, ELO, std::chrono::system_clock::now()));
    }
}

void move(int clientSock, Message *msg) {
    int gameID = gameMap[clientSock];
    ChessGame curGame = gameList[gameID];
    MoveMessage* moveMsg = new MoveMessage(*msg);
    std::string src = moveMsg->getSource();
    std::string dest = moveMsg->getDestination();
    int startRow = (int)(src[0] - '0');
    int startCol = (int)(src[1] - '0');
    int endRow = (int)(dest[0] - '0');
    int endCol = (int)(dest[1] - '0');

    bool valid = curGame.validateMove(curGame.chessboard.MainGameBoard, startRow, startCol, endRow, endCol);
    if (valid) {
        curGame.AlternateTurn();
        if (clientSock == playerMap[gameID].first) {
            sendMessage(playerMap[gameID].second, moveMsg);
        } else {
            sendMessage(playerMap[gameID].first, moveMsg);
        }
        Message* rep1;
        Message* rep2;
        switch(curGame.IsGameOver()) {
            case 0: {
                rep1 = new Message(OK);

                sendMessage(playerMap[gameID].first, rep1);
                sendMessage(playerMap[gameID].second, rep2);
                break;
            }
            case 1: {
                rep1 = new Message(GAME_WIN);
                rep2 = new Message(GAME_LOSE);

                sendMessage(playerMap[gameID].first, rep1);
                sendMessage(playerMap[gameID].second, rep2);
                break;
            }
            case 2: {
                rep1 = new Message(GAME_WIN);
                rep2 = new Message(GAME_LOSE);

                sendMessage(playerMap[gameID].first, rep2);
                sendMessage(playerMap[gameID].second, rep1);
                break;
            }
            case 3: {
                rep1 = new Message(STALEMATE);

                sendMessage(playerMap[gameID].first, rep1);
                sendMessage(playerMap[gameID].second, rep1);
                break;
            }
            case 4: {
                rep1 = new Message(THREE_FOLD);

                sendMessage(playerMap[gameID].first, rep1);
                sendMessage(playerMap[gameID].second, rep1);
                break;
            }
            case 5: {
                rep1 = new Message(FIFTY);

                sendMessage(playerMap[gameID].first, rep1);
                sendMessage(playerMap[gameID].second, rep1);
                break;
            }
            
            default: {}
        }

        //Update game list
        if (curGame.IsGameOver() > 0) {
            gameList.erase(gameID);
            gameMap.erase(playerMap[gameID].first);
            gameMap.erase(playerMap[gameID].second);
            playerMap.erase(gameID);
        }
        delete(rep1);
        delete(rep2);

    } else {
        MoveMessage* moveErr = new MoveMessage(MOVE_NOT_OK);
        sendMessage(clientSock, moveErr);
    }
}

void offerDraw(int clientSocket) {
    int gameID = gameMap[clientSocket];

    int opponent = playerMap[gameID].first == clientSocket ? playerMap[gameID].second : playerMap[gameID].first;
    sendMessage(opponent, new Message(OFFER_DRAW));
    char buff[BUFF_SIZE];
    int rc = recv(opponent, buff, BUFF_SIZE, 0);
    std::string rcv(buff, rc);
    Message* msg = new Message(rcv);
    if (msg->getType() == OK) {
        sendMessage(clientSocket, new Message(GAME_DRAW));
        sendMessage(opponent, new Message(GAME_DRAW));

        //Update game list
        gameList.erase(gameID);
        gameMap.erase(playerMap[gameID].first);
        gameMap.erase(playerMap[gameID].second);
        playerMap.erase(gameID);
    } else {
        sendMessage(clientSocket, new Message(NOT_OK));
    }

}

void resign(int clientSocket) {
    int gameID = gameMap[clientSocket];

    int opponent = playerMap[gameID].first == clientSocket ? playerMap[gameID].second : playerMap[gameID].first;

    sendMessage(clientSocket, new Message(GAME_LOSE));
    sendMessage(opponent, new Message(GAME_WIN));

    //Update game list
    gameList.erase(gameID);
    gameMap.erase(playerMap[gameID].first);
    gameMap.erase(playerMap[gameID].second);
    playerMap.erase(gameID);
}

void checkWaitingQueue() {
    while (1) {
        auto curTime = std::chrono::system_clock::now();
        for (int i = 0; i < waitingQueue.size(); i++) {
            int clientSock = waitingQueue[i].clientSock;
            auto queueTime = std::chrono::duration_cast<std::chrono::seconds>(curTime - waitingQueue[i].start).count();
            if (queueTime >= MAX_QUEUE_TIME) {
                waitingQueue.erase(waitingQueue.begin() + i);
                Message* timeout = new Message(MATCHMAKING_TIMEOUT);
                sendMessage(clientSock, timeout);
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void handleClient(int clientSocket, Database *db) {
    char buff[BUFF_SIZE];
    int n, failLogin = 0;
    std::string username;

    while ((n = recv(clientSocket, buff, BUFF_SIZE, 0)) > 0) {
        std::string rcv(buff, n);
        // Construct Message from string of message received
        Message *msg = new Message(rcv);
        switch (msg->getType()) {
            case OK:
                break;

            case NOT_OK:
                break;

            case SEE_HISTORY:
                seeHistory(clientSocket, username, db);
                break;

            case RANDOM_MATCHMAKING:
                randomMatch(clientSocket, username, db);
                break;

            case CREATE_ROOM:
                createRoom(clientSocket, db);
                break;

            case OFFER_DRAW:
                offerDraw(clientSocket);
                break;

            case RESIGN:
                resign(clientSocket);
                break;

            case REGISTER: // <username> <password>
                registerUser(clientSocket, msg, db);
                break;

            case LOGIN: // <username> <password>
                login(clientSocket, msg, &username, &failLogin, db);
                break;

            case LOGOUT: // <username>
                logout(clientSocket);
                break;

            case INVITE: // <username>
                invite(clientSocket, msg);
                break;

            case MOVE: // <source_position> <destination_position>
                move(clientSocket, msg);
                break;

            case DELETE_ROOM: // <username>
                deleteRoom(clientSocket);
                break;

            case ACCEPT_INVITE: // <username>
                break;

            case REJECT_INVITE: // <username>
                break;

            case SEE_MATCH: // <match_id>
                seeMatch(clientSocket, username, msg, db);
                break;
            
            default:
                break;
        }
    }

    if (n < 0) {
        perror("Read error");
        exit(1);
    } else if (n == 0) {
        printf("Client disconnected\n");
    }
    close(clientSocket);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    
    // Open database connection
    Database db("database/chess.db");
    if (!db.open()) {
        std::cerr << "Error opening database connection" << std::endl;
        exit(1);
    }

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        return 1;
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding socket");
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, BACKLOG) == -1) {
        perror("Error listening for connections");
        return 1;
    }

    std::cout << "Chess Server listening on port " << PORT << std::endl;

    std::thread(checkWaitingQueue).detach();

    while (true) {
        // Accept a new connection
        if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen)) == -1) {
            perror("Error accepting connection");
            continue;
        }
        std::cout << "Accepted connection from " << inet_ntoa(clientAddr.sin_addr) << std::endl;

        // Threading
        std::thread(handleClient, static_cast<int>(clientSocket), db).detach();
    }

    // Close the server socket
    close(serverSocket);

    return 0;
}