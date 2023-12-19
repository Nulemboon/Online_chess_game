#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include "message/message.h"
const int PORT = 5500;
const int BACKLOG = 5;
const int BUFF_SIZE = 1024;


void login() {

}

void handle(void* clientsock) {
    int socket = *(int *) clientsock;
    int read_len, send_stat;
    char msg[BUFF_SIZE];
    while (1) {

    }

}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

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
            handleClient(clientSocket);

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