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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Message* sendMessage(int clientSocket, Message *message);

private:
    Ui::MainWindow *ui;
    int connfd;
    void connectServer();
    const int BUFF_SIZE = 1024;
    char buffer[BUFF_SIZE];
    QString user;
};
#endif // MAINWINDOW_H
