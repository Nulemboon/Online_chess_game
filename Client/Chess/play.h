#ifndef PLAY_H
#define PLAY_H

#include <QWidget>
#include "mainwindow.h"
class MainWindow;
namespace Ui {
class play;
}

class play : public QWidget
{
    Q_OBJECT

public:
    explicit play(MainWindow* mainwindow, QWidget *parent = nullptr);
    ~play();

    void fetchData();
    void getPlayData();


    Ui::play *ui;
    std::vector<std::pair<std::string, int>> list;
private slots:
    void on_btnRefresh_clicked();

    void on_btnBack_clicked();

    void on_btnInvite_clicked();

    void on_btnMM_clicked();

private:
    MainWindow* mainwindow;
};

#endif // PLAY_H
