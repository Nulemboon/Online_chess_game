#include "history.h"
#include "ui_history.h"

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

    // Set fixed size for each row
    for (int row = 0; row < ui->historyView->rowCount(); ++row) {
        ui->historyView->setRowHeight(row,65.5);
    }

}

history::~history()
{
    delete ui;
}
