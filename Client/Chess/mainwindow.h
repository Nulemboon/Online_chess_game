#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "../message/message.h"
#include "myclient.h"
#include "home.h"
#include "game.h"
#include "history.h"
#include "play.h"
#include "match.h"
class game;
class Home;
class history;
class play;
class Match;
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
    void sendMessage(Message *message);
    void switchScene(Scene sceneType);

    int connfd;
    QString user;
    QStackedWidget *stackedWidget;
private:
    Ui::MainWindow *ui;
    void connectServer();
    const int BUFF_SIZE = 1024;
    char buffer[1024];
    MyClient client;

    Home* homeWid;
    game* gameWid;
    history* historyWid;
    play* playWid;
    Match* matchWid;

    void handleHistory(Message *msg);
    void handleMatch(Message *msg);
    void handleRegisterUsernameExisted(Message *msg);
    void handleRegisterPasswordFail(Message *msg);
    void handleRegisterSuccessful(Message *msg);
    void handleLoginFail(Message *msg);
    void handleUserBlocked(Message *msg);
    void handleUserLoggedIn(Message *msg);
    void handleLoginSuccessful(Message *msg);
    void handleOnlineList(Message *msg);
    void handleMatchFound(Message *msg);
    void handleMatchmakingTimeout(Message *msg);
    void handleMoveNotOk(Message *msg);
    void handleStalemate(Message *msg);
    void handleThreeFold(Message *msg);
    void handleFifty(Message *msg);
    void handleGameDraw(Message *msg);
    void handleGameWin(Message *msg);
    void handleGameLose(Message *msg);
    void handleError(Message *msg);
    void handleMove(Message *msg);
    void handleOK(Message *msg);
    void handleInvite(Message *msg);


private slots:
    void onMessageReceived(const QString &message);

};
#endif // MAINWINDOW_H
