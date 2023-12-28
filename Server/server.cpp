#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include "message/message.h"
#include "database/database.h"

const int PORT = 5500;
const int BACKLOG = 5;
const int BUFF_SIZE = 1024;
const int HEADER_SIZE = 3;

std::vector<std::string> loggedInUsers;


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
    std::vector<std::string>::iterator position = std::find(loggedInUsers.begin(), loggedInUsers.end(), acc->getUsername());
    if (position != loggedInUsers.end()) {
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
            loggedInUsers.push_back(*username); // Add this user to the online list
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

void seeHistory(int clientSocket, std::string username, Database* db) {
    // Get history
    std::vector<std::map<std::string, std::string>> matchList = db->getHistory(username);
    std::cout << "User '" << username << "' see his history" << std::endl;

    // Send history message
    HistoryMessage* historyMsg = new HistoryMessage(HISTORY, matchList);
    sendMessage(clientSocket, historyMsg);
    delete historyMsg;
}

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

void handle(void* clientsock) {
    int socket = *(int *) clientsock;
    int read_len, send_stat;
    char msg[BUFF_SIZE];
    while (1) {

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
                break;

            case CREATE_ROOM:
                break;

            case OFFER_DRAW:
                break;

            case RESIGN:
                break;

            case REGISTER: // <username> <password>
                registerUser(clientSocket, msg, db);
                break;

            case LOGIN: // <username> <password>
                login(clientSocket, msg, &username, &failLogin, db);
                break;

            case LOGOUT: // <username>
                break;

            case INVITE: // <username>
                break;

            case MOVE: // <source_position> <destination_position>
                break;

            case DELETE_ROOM: // <room_id>
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

    while (true) {
        // Accept a new connection
        if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen)) == -1) {
            perror("Error accepting connection");
            continue;
        }

        // Fork a new process to handle the client
        pid_t pid = fork();

        if (pid == -1) {
            perror("Error forking process");
            close(clientSocket);
        } else if (pid == 0) {  // Child process
            close(serverSocket);  // Child doesn't need the listener

            // Handle the client in the child process
            handleClient(clientSocket, &db);

            // Exit the child process
            exit(0);
        } else {  // Parent process
            close(clientSocket);  // Parent doesn't need the client socket
        }

        // Clean up zombie processes
        while (waitpid(-1, NULL, WNOHANG) > 0) {}
    }

    // Close the server socket
    close(serverSocket);

    return 0;
}