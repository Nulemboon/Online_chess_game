#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QSocketNotifier>
#include <QDebug>
#include <poll.h>

class MyClient : public QObject {
    Q_OBJECT
public:
    explicit MyClient(QObject *parent = nullptr);

public slots:
    void sendMessage(const QString message, int length);
    void onConnected();
    void onSocketActivated(int socket);

signals:
    void messageReceived(const QString &message);

private:
    void pollSocket();
    QTcpSocket *socket;
    QSocketNotifier *socketNotifier;
};

#endif // MYCLIENT_H
