#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

const int PORT = 5500;
const char SERVER_IP[] = "127.0.0.1";  // Replace with the server's IP address

const int BUFF_SIZE = 1024;

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        return 1;
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting to server");
        close(clientSocket);
        return 1;
    }

    std::cout << "Connected to the Chess Server" << std::endl;

    char buffer[BUFF_SIZE];
    int bytesRead;

    // Receive the initial message from the server
    bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead <= 0) {
        perror("Error receiving data");
        close(clientSocket);
        return 1;
    }

    buffer[bytesRead] = '\0';
    std::cout << buffer << std::endl;

    // Main game loop
    while (true) {
        std::cout << "Enter your move (or 'exit' to end the game): ";
        std::string move;
        std::getline(std::cin, move);

        // Check for the exit command
        if (move == "exit") {
            break;
        }

        // Send the move to the server
        if (send(clientSocket, move.c_str(), move.length(), 0) == -1) {
            perror("Error sending data");
            close(clientSocket);
            return 1;
        }

        // Receive the opponent's move
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            perror("Error receiving data");
            close(clientSocket);
            return 1;
        }

        buffer[bytesRead] = '\0';
        std::cout << "Opponent's move: " << buffer << std::endl;
    }

    // Close the client socket
    close(clientSocket);

    std::cout << "Game ended. Goodbye!" << std::endl;

    return 0;
}