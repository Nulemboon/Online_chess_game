#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include "mainwindow.h"
#include "ui_game.h"
#include "ui_home.h"
#include "ui_play.h"
#include "ui_history.h"
#include "ui_match.h"

class MainWindow;
namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(MainWindow *mainwindow, QWidget *parent = nullptr);
    ~Home();
    Ui::Home*ui;


private slots:
    void on_btnQuit_clicked();

    void on_btnHistory_clicked();
    void on_btnRegister_clicked();
    void onPasswordTextChanged(const QString &text);
    void onUsernameTextChanged(const QString &text);

    void on_btnLogin_clicked();

    void on_btnLogout_clicked();

    void on_btnToRegister_clicked();

    void on_btnToLogin_clicked();

    void on_btnPlay_clicked();

private:
    MainWindow *mainwindow;
};

#endif // HOME_H
