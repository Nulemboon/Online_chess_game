#include "play.h"
#include "ui_play.h"
#include "match.h"
#include "game.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QGraphicsDropShadowEffect>

play::play(MainWindow* mainwindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::play), mainwindow(mainwindow)
{
    ui->setupUi(this);
    ui->lbNoMM->setVisible(false);
    ui->frInvite->setVisible(false);
    ui->playView->setRowCount(0);
    // Disable resizing for rows
    for (int row = 0; row < ui->playView->rowCount(); ++row) {
        ui->playView->verticalHeader()->setSectionResizeMode(row, QHeaderView::Fixed);
    }

    // Set fixed size for rows
    const int fixedRowHeight = 40;
    ui->playView->verticalHeader()->setDefaultSectionSize(fixedRowHeight);
    ui->playView->verticalHeader()->setMinimumSectionSize(fixedRowHeight);
    ui->playView->verticalHeader()->setMaximumSectionSize(fixedRowHeight);
    ui->playView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->playView->verticalHeader()->setStretchLastSection(false);
    for (int row = 0; row < ui->playView->rowCount(); ++row) {
        ui->playView->setRowHeight(row, fixedRowHeight);
        QTableWidgetItem *item = ui->playView->item(row, 1);

        // Check if the item exists
        if (item) {
            // Set the text alignment to center
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }

}

play::~play()
{
    delete ui;
}

void play::fetchData(std::vector<std::pair<std::string, int>> newList) {
    // Fetch new data to the play table
    // Set the number of rows and columns
    int numberOfColumn = 1;
    int existingRowCount = ui->playView->rowCount();
    int newRowCount = newList.size();
    ui->playView->setRowCount(existingRowCount + newRowCount);
    ui->playView->setColumnCount(numberOfColumn);
    int count = existingRowCount;  // Start from the last inserted row index

    // Populate the model with data from the new list
    for (int row = 0; row < newRowCount; ++row) {
        std::pair<std::string, int> player = newList[row];
        QTableWidgetItem *item;

        item = new QTableWidgetItem(QString::fromStdString(player.first) + " (" + QString::number(player.second) + ")");
        ui->playView->setItem(count++, 0, item);
    }
}


void play::getPlayData() {
    // Send request for online list to server
    Message *msg = new Message(ONLINE_LIST);
    mainwindow->sendMessage(msg);
}

void play::on_btnRefresh_clicked()
{
    ui->playView->setRowCount(0);
    getPlayData();
}


void play::on_btnBack_clicked()
{
    // Send DELETE_ROOM to server
    Message* msg = new Message(DELETE_ROOM);
    mainwindow->sendMessage(msg);
    ui->playView->setRowCount(0);

    mainwindow->switchScene(HOMES);
}


void play::on_btnInvite_clicked()
{
    // Get the selection model of the QTableView
    QItemSelectionModel* selectionModel = ui->playView->selectionModel();

    // Check if there is any selection
    // if (selectionModel->hasSelection()) {
        // Get the current index
        QModelIndex currentIndex = selectionModel->currentIndex();
        int currentRow = currentIndex.row();

        QString opponent = ui->playView->itemAt(currentRow, 0)->text();
        std::string tmp = opponent.toStdString();
        std::string n = "";
        for (int i = 0; i < tmp.length(); i++) {
            if (tmp[i] == '(') break;
            n += tmp[i];
        }
        n.pop_back();

        UserMessage* msg = new UserMessage(INVITE, n, "");
        qDebug() << n;
        mainwindow->sendMessage(msg);

    // } else {
    //     return;
    // }
}


void play::on_btnMM_clicked()
{
    // Disable other buttons
    ui->btnInvite->setEnabled(false);
    ui->btnRefresh->setEnabled(false);
    ui->btnBack->setEnabled(false);
    ui->btnMM->setText("FINDING MATCH...");
    ui->lbNoMM->setVisible(false);

    // Send request to random MM to server
    Message* msg = new Message(RANDOM_MATCHMAKING);
    mainwindow->sendMessage(msg);

}


void play::on_btnNo_clicked()
{
    inviteList.erase(inviteList.begin());
    if (inviteList.size() < 1) {
        ui->frInvite->setVisible(false);
    } else {
        ui->lbNameInvite->setText(QString::fromStdString(inviteList.begin()->first) + " (" + QString::number(inviteList.begin()->second));
        if (inviteList.size() > 1) {
            QGraphicsDropShadowEffect *g = new QGraphicsDropShadowEffect(this);
            QColor q(244, 220, 197, 200);
            g->setColor(q);
            ui->frInvite->setGraphicsEffect(g);
        } else {
            ui->frInvite->setGraphicsEffect(nullptr);
        }
    }

}


void play::on_btnYes_clicked()
{
    UserMessage* msg = new UserMessage(ACCEPT_INVITE, inviteList.begin()->first, "");
    mainwindow->sendMessage(msg);
    inviteList.clear();
    ui->frInvite->setVisible(false);
}

