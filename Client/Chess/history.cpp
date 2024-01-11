#include "history.h"
#include "ui_history.h"
#include "match.h"
#include <QStandardItemModel>
#include <QStandardItem>

history::history(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::history)
{
    ui->setupUi(this);
    //ui->historyView->resizeColumnsToContents();
    // Disable resizing for columns
    for (int col = 0; col < ui->historyView->columnCount(); ++col) {
        ui->historyView->horizontalHeader()->setSectionResizeMode(col, QHeaderView::Fixed);
    }

    // Disable resizing for rows
    for (int row = 0; row < ui->historyView->rowCount(); ++row) {
        ui->historyView->verticalHeader()->setSectionResizeMode(row, QHeaderView::Fixed);
    }

    // Set fixed size for each collumn
    ui->historyView->setColumnWidth(0, 230);
    ui->historyView->setColumnWidth(1, 160);
    ui->historyView->setColumnWidth(2, 220);

    // Set fixed size for rows
    const int fixedRowHeight = 40;
    ui->historyView->verticalHeader()->setDefaultSectionSize(fixedRowHeight);
    ui->historyView->verticalHeader()->setMinimumSectionSize(fixedRowHeight);
    ui->historyView->verticalHeader()->setMaximumSectionSize(fixedRowHeight);
    ui->historyView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->historyView->verticalHeader()->setStretchLastSection(false);
    for (int row = 0; row < ui->historyView->rowCount(); ++row) {
        ui->historyView->setRowHeight(row, fixedRowHeight);
        QTableWidgetItem *item = ui->historyView->item(row, 1);

        // Check if the item exists
        if (item) {
            // Set the text alignment to center
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }

    // Highlight the whole selected row
    ui->historyView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->historyView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->historyView->selectRow(0);
    QItemSelectionModel *selectionModel = ui->historyView->selectionModel();
    QModelIndex defaultIndex = ui->historyView->model()->index(0, 0);
    selectionModel->setCurrentIndex(defaultIndex, QItemSelectionModel::Select);

    // Fetch data into the table
    std::map<std::string, std::string> match;
    match["whiteID"] = "Tue";
    match["blackID"] = "Tri";
    match["result"] = "0";
    match["time"] = "3/10/22";
    match["matchID"] = "13";
    matches.push_back(match);
    getHistoryData();


}

history::~history()
{
    delete ui;
}

void history::getHistoryData() {
    // Send request for History data to server
    // Message *msg = new Message(SEE_HISTORY);
    // mainwindow->sendMessage(mainwindow->connfd, msg);

    // // Receive result
    // msg = mainwindow->receiveMessage(mainwindow->connfd);
    // HistoryMessage *rcv = new HistoryMessage(*msg);
    // matches = rcv->getMatches();

    // Fetch new data to the history table
    // Set the number of rows and columns
    int numberOfRow = matches.size();
    int numberOfColumn = 3;
    ui->historyView->setRowCount(numberOfRow);
    ui->historyView->setColumnCount(numberOfColumn);

    // Populate the model with data
    for (int row = 0; row < numberOfRow; ++row) {
        std::map<std::string, std::string> match = matches[row];
        QTableWidgetItem *item;

        // Get opponent name
        int sideMatch = match["whiteID"] == mainwindow->user.toStdString() ? 0 : 1; // 0 for White, 1 for Black
        QString nameO = sideMatch == 1 ? QString::fromStdString(match["blackID"]) : QString::fromStdString(match["whiteID"]);
        item = new QTableWidgetItem(nameO);
        ui->historyView->setItem(row, 0, item);

        QString result;
        // Get result of the match
        if (match["result"] == "0") {
            result = "Draw";
        } else if (match["result"] == "1") {
            if (sideMatch == 0) result = "Win";
            else result = "Lose";
        } else {
            if (sideMatch == 1) result = "Win";
            else result = "Lose";
        }
        item = new QTableWidgetItem(result);
        ui->historyView->setItem(row, 1, item);

        // Get time
        item = new QTableWidgetItem(QString::fromStdString(match["time"]));
        ui->historyView->setItem(row, 2, item);
    }
}

void history::on_historyView_cellDoubleClicked(int row, int column)
{
    // Send request for History data to server
    MatchMessage *msg = new MatchMessage(matches[row]["matchID"]);
    mainwindow->sendMessage(mainwindow->connfd, msg);

    Message *tmp;
    // Receive result
    tmp = mainwindow->receiveMessage(mainwindow->connfd);
    msg = new MatchMessage(*tmp);

    // Parse move
    std::vector<std::pair<int, int>> test;
    std::istringstream iss(msg->getMatch());

    int move1, move2;

    // Read pairs of integers from the stringstream
    while (iss >> move1 >> move2) {
        test.push_back(std::make_pair(move1, move2));
    }


    // Switch scene to game
    mainwindow->switchScene(GAMES);

    // Match* screen = qobject_cast<Match*>(mainwindow->stackedWidget->currentWidget());
    // screen->reset();
    // std::string sideO;
    // int sideMatch = match["whiteID"] == mainwindow->user.toStdString() ? 0 : 1; // 0 for White, 1 for Black
    // QString nameO = sideMatch == 1 ? QString::fromStdString(match["blackID"]) : QString::fromStdString(match["whiteID"]);
    // if (side == WHITE) {
    //     sideO = "blackID";
    // } else {
    //     sideO = "whiteID";
    // }

    // screen->opponentName = matches[row][sideO];
    // screen->moveList = test;
}

