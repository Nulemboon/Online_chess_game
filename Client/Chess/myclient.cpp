#include "myclient.h"
#include <iostream>

MyClient::MyClient(QObject *parent)
    : QObject(parent)
{
    socket = new QTcpSocket(this);

    // Connect signals and slots
    connect(socket, &QTcpSocket::connected, this, &MyClient::onConnected);

    // Connect to the server
    socket->connectToHost("192.168.1.34", 5500); // Replace with your server's IP and port
}

void MyClient::onConnected()
{
    qDebug() << "Connected to the server";

    // Connect the socketNotifier to handle socket events
    socketNotifier = new QSocketNotifier(socket->socketDescriptor(), QSocketNotifier::Read, this);
    connect(socketNotifier, &QSocketNotifier::activated, this, &MyClient::onSocketActivated);
    // Start monitoring the socket for readability
    socketNotifier->setEnabled(true);
}

void MyClient::onSocketActivated(int activatedSocket)
{
    if (activatedSocket == socketNotifier->socket()) {
        // Handle socket events
        pollSocket();
    }
}

void MyClient::pollSocket()
{
    const int bufferSize = 1024;
    char buff[bufferSize];

    qint64 bytesRead = 0;
    do {
        bytesRead = socket->read(buff, bufferSize);
        for (int i = 0; i < bytesRead; i++) {
            std::cout << static_cast<int>(buff[i]) << " ";
        }
        if (buff[0] == '\n') continue;
        std::cout << std::endl;
        if (bytesRead > 0) {
            std::string delimiter = "\n";
            std::string token = "";
            size_t pos = 0;
            std::string s(buff, bytesRead);
            // qDebug() << QString::fromStdString(s);
            // for (int i = 0; i < bytesRead; i++) {
            //     qDebug() << static_cast<int>(buff[i]);
            // }
            while ((pos = s.find(delimiter)) != std::string::npos) {
                if (s.length() <= 1) break;
                token = s.substr(0, pos);
                s.erase(0, pos + delimiter.length());


                QString message = QString::fromStdString(token);
                qDebug() << "Received message:" << message;

                // Emit the signal with the received message
                emit messageReceived(message);
            }
        }
    } while (bytesRead > 0);
}


void MyClient::sendMessage(const QString message, int length)
{
    if (!socket) qDebug() << "DEAD";
    if (socket->state() == QAbstractSocket::ConnectedState) {
        // Convert the QString to a QByteArray before sending

        qint64 bytesWritten = socket->write(message.toStdString().c_str(), length + 3);

        if (bytesWritten == -1) {
            // An error occurred during writing
            qDebug() << "Error writing to socket:" << socket->errorString();
        } else if (bytesWritten < message.size()) {
            // Not all data was written
            qDebug() << "Not all data was written. Expected:" << message.size() << ", Actual:" << bytesWritten;
        } else {
            // All data was successfully written
            qDebug() << "All data written successfully.";
        }
        for (int i = 0; i <message.size(); i++) {

            qDebug() << static_cast<int>(message.toStdString()[i]);
        }
        qDebug() << message;

        socket->flush();  // Ensure that the data is sent immediately
    } else {
        qDebug() << "Not connected to the server. Unable to send message.";
    }
}

