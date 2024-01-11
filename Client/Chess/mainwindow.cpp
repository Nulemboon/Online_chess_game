#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "home.h"
#include "game.h"
#include "history.h"
#include "play.h"
#include "match.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

const int PORT = 5500;
const char SERVER_IP[] = "127.0.0.1";  // Replace with the server's IP address

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stackedWidget = new QStackedWidget(this);
    // connectServer();

    // Initiate scenes
    Home *homeWid = new Home(this, this);
    history *historyWid = new history(this);
    Match *matchWid = new Match(WHITE, "Opponent", this, this);
    play *playWid = new play(this);
    game *gameWid = new game(WHITE, "Opponent", this, this);

    // Add scenes to a stackedWidget
    stackedWidget->addWidget(homeWid);
    stackedWidget->addWidget(historyWid);
    stackedWidget->addWidget(matchWid);
    stackedWidget->addWidget(playWid);
    stackedWidget->addWidget(gameWid);

    // Set the central widget as the stacked widget
    setCentralWidget(stackedWidget);

    // Show the initial widget (home)
    stackedWidget->setCurrentIndex(MATCHS);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectServer() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(1);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (::connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting to server");
        ::close(clientSocket);
        exit(1);
    }

    std::cout << "Connected to the Chess Server" << std::endl;
    connfd = clientSocket;
}

void MainWindow::sendMessage(int clientSocket, Message *message) {
    int n = send(clientSocket, message->serialize().c_str(), message->getLength() + BUFF_SIZE, 0);
    if (n < 0) {
        qDebug() << "Error sending message";
    }
}

Message* MainWindow::receiveMessage(int clientSocket) {
    // Receive message from server
    int bytes_received = recv(connfd, buffer, BUFF_SIZE, 0);
    if (bytes_received < 0)
        qDebug() << "Error receiving message";
    else if (bytes_received == 0)
        qDebug() << "Connection closed.\n";

    buffer[bytes_received] = '\0';
    std::string bufferString(buffer);
    Message* rcv = new Message(bufferString);
    return rcv;
}

void MainWindow::switchScene(Scene sceneType) {
    stackedWidget->setCurrentIndex(sceneType);
}
