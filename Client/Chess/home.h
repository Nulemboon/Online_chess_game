#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(MainWindow *mainwindow, QWidget *parent = nullptr);
    ~Home();


private slots:
    void on_btnQuit_clicked();

    void on_btnHistory_clicked();
    void onPasswordTextChanged(const QString &text);
    void onUsernameTextChanged(const QString &text);

    void on_btnLogin_clicked();

private:
    Ui::Home*ui;
    MainWindow *mainwindow;
};

#endif // HOME_H
