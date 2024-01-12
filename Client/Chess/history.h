#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include "mainwindow.h"
#include "../message/message.h"
#include <bits/stdc++.h>
class MainWindow;
namespace Ui {
class history;
}

class history : public QWidget
{
    Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr);
    ~history();

    void fetchData();
    void getHistoryData();

    std::vector<std::map<std::string, std::string>> matches;
    int rowClicked;
private slots:
    void on_historyView_cellDoubleClicked(int row, int column);

    void on_btnBack_clicked();

private:
    Ui::history *ui;
    MainWindow* mainwindow;
};

#endif // HISTORY_H
