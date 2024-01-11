#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "../message/message.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum Scene {
    HOMES,
    HISTORYS,
    MATCHS,
    PLAYS,
    GAMES,
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void sendMessage(int clientSocket, Message *message);
    Message* receiveMessage(int clientSocket);
    void switchScene(Scene sceneType);

    int connfd;
    QString user;
    QStackedWidget *stackedWidget;
private:
    Ui::MainWindow *ui;
    void connectServer();
    const int BUFF_SIZE = 1024;
    char buffer[1024];

};
#endif // MAINWINDOW_H
