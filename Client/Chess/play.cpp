#include "play.h"
#include "ui_play.h"
#include "match.h"
#include "game.h"
#include <QStandardItemModel>
#include <QStandardItem>

play::play(MainWindow* mainwindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::play), mainwindow(mainwindow)
{
    ui->setupUi(this);
    ui->lbNoMM->setVisible(false);
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

void play::fetchData() {
    // Fetch new data to the play table
    // Set the number of rows and columns
    int numberOfRow = list.size();
    int numberOfColumn = 1;
    ui->playView->setRowCount(numberOfRow);
    ui->playView->setColumnCount(numberOfColumn);

    // Populate the model with data
    for (int row = 0; row < numberOfRow; ++row) {
        std::pair<std::string, int> player = list[row];
        QTableWidgetItem *item;

        item = new QTableWidgetItem(QString::fromStdString(player.first) + " (" + QString::number(player.second) + ")");
        ui->playView->setItem(row, 0, item);
    }
}

void play::getPlayData() {
    // Send request for online list to server
    Message *msg = new Message(ONLINE_LIST);
    mainwindow->sendMessage(msg);
}

void play::on_btnRefresh_clicked()
{
    getPlayData();
}


void play::on_btnBack_clicked()
{
    // Send DELETE_ROOM to server
    Message* msg = new Message(DELETE_ROOM);
    mainwindow->sendMessage(msg);

    mainwindow->switchScene(HOMES);
}


void play::on_btnInvite_clicked()
{
    // Get the selection model of the QTableView
    QItemSelectionModel* selectionModel = ui->playView->selectionModel();

    // Check if there is any selection
    if (selectionModel->hasSelection()) {
        // Get the current index
        QModelIndex currentIndex = selectionModel->currentIndex();
        int currentRow = currentIndex.row();

        UserMessage* msg = new UserMessage(INVITE, list[currentRow].first, "");
        mainwindow->sendMessage(msg);

        // TODO: receive result of invite

    } else {
        return;
    }
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

