#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include "mainwindow.h"
#include "../message/message.h"
#include <bits/stdc++.h>

namespace Ui {
class history;
}

class history : public QWidget
{
    Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr);
    ~history();

private slots:
    void on_historyView_cellDoubleClicked(int row, int column);

private:
    Ui::history *ui;
    std::vector<std::map<std::string, std::string>> matches;
    MainWindow* mainwindow;
    void getHistoryData();
};

#endif // HISTORY_H
