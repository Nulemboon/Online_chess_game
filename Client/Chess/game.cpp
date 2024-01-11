#include "game.h"
#include "ui_game.h"
#include "../gameplay.h"

game::game(Side side, QString opponentName, MainWindow* mainwindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::game), side(side), opponentName(opponentName), mainwindow(mainwindow)
{
    ui->setupUi(this);
    ui->lbDim->setVisible(false);
    ui->frConfirm->setVisible(false);

    // Disable resizing for columns
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(col, QHeaderView::Fixed);
    }

    // Disable resizing for rows
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        ui->tableWidget->verticalHeader()->setSectionResizeMode(row, QHeaderView::Fixed);
    }

    // Set fixed size for columns and rows
    ui->tableWidget->setColumnWidth(0, 54);
    ui->tableWidget->setColumnWidth(1, 84);
    ui->tableWidget->setColumnWidth(2, 84);

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        ui->tableWidget->setRowHeight(row, 30);
    }

    // Set players name
    ui->lbOpponentName->setText(opponentName);
    ui->lbPlayerName->setText(mainwindow->user);

    // Set alignment for the captured layout
    ui->hboxPlayer->setAlignment(Qt::AlignLeft);
    ui->hboxOpponent->setAlignment(Qt::AlignLeft);

    drawBoxes();
    setupBoard();
    squareSelected.first = -1; squareSelected.second = -1;
}

game::~game()
{
    delete ui;
}

void game::drawBoxes()
{
    int SHIFT = 70;
    QString color;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            if((i+j)%2==0)
                color = "#AB6C00";
            else
                color = "#F4DCC5";
            ChessSquare *box = new ChessSquare(color, ui->frChessBoard);
            collection[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;

            if (side == WHITE) {
                // Player: White side
                box->setGeometry((SHIFT*j),(SHIFT*(7-i)), 70, 70);
            } else {
                // Player: Black side
                box->setGeometry((SHIFT*(7-j)), (SHIFT*i), 70, 70);
            }

            // Connect the clicked signal to the chessSquareClicked slot
            connect(collection[i][j], &ChessSquare::clicked, this, &game::chessSquareClicked);
        }
    }

}

void game::setupBoard() {

    // Black pieces
    collection[0][0]->placePiece(RookW);
    collection[0][1]->placePiece(KnightW);
    collection[0][2]->placePiece(BishopW);
    collection[0][3]->placePiece(QueenW);
    collection[0][4]->placePiece(KingW);
    collection[0][5]->placePiece(BishopW);
    collection[0][6]->placePiece(KnightW);
    collection[0][7]->placePiece(RookW);
    for (int i = 0; i< 8; i++) {
        collection[1][i]->placePiece(PawnW);
    }

    // White pieces
    for (int i = 0; i< 8; i++) {
        collection[6][i]->placePiece(PawnB);
    }
    collection[7][0]->placePiece(RookB);
    collection[7][1]->placePiece(KnightB);
    collection[7][2]->placePiece(BishopB);
    collection[7][3]->placePiece(QueenB);
    collection[7][4]->placePiece(KingB);
    collection[7][5]->placePiece(BishopB);
    collection[7][6]->placePiece(KnightB);
    collection[7][7]->placePiece(RookB);

}

QString game::getPath(ChessPiece piece) {
    QString path = ":/ChessPiece/assets/";

    switch (piece) {
    case PawnB:
        path += "pawnB.png";
        break;
    case PawnW:
        path += "pawnW.png";
        break;
    case RookB:
        path += "rookB.png";
        break;
    case RookW:
        path += "rookW.png";
        break;
    case KnightB:
        path += "horseB.png";
        break;
    case KnightW:
        path += "horseW.png";
        break;
    case BishopB:
        path += "bishopB.png";
        break;
    case BishopW:
        path += "bishopW.png";
        break;
    case QueenB:
        path += "queenB.png";
        break;
    case QueenW:
        path += "queenW.png";
        break;
    case KingB:
        path += "kingB.png";
        break;
    case KingW:
        path += "kingW.png";
        break;
    default:
        path = "";
        break;
    }
    return path;
}

void game::addDead() {
    while (!playerDead.empty()) {
        QLabel* newLabel = new QLabel;
        newLabel->setFixedSize(30, 30);

        QPixmap backgroundImage(getPath(playerDead.first()));
        newLabel->setPixmap(backgroundImage.scaled(newLabel->size(), Qt::KeepAspectRatio));
        ui->hboxPlayer->addWidget(newLabel);
        playerDead.removeFirst();
    }

    while (!opponentDead.empty()) {
        QLabel* newLabel = new QLabel;
        newLabel->setFixedSize(30, 30);

        QPixmap backgroundImage(getPath(opponentDead.first()));
        newLabel->setPixmap(backgroundImage.scaled(newLabel->size(), Qt::KeepAspectRatio));
        ui->hboxOpponent->addWidget(newLabel, Qt::AlignLeft);
        opponentDead.removeFirst();
    }
}

void game::moves(ChessSquare* src, ChessSquare* dst) {
    if (dst->getPiece() != NONE && src->getPiece() != NONE) {
        Side pieceSide = dst->side;
        if (pieceSide == side) {
            playerDead.append(dst->getPiece());
            addDead();
        } else {
            opponentDead.append(dst->getPiece());
            addDead();
        }
    }

    dst->placePiece(src->getPiece());
    src->placePiece(NONE);

}

void game::chessSquareClicked(int row, int col)
{
    qDebug() << row << " " << col;
    // Deselect
    if (squareSelected.first != -1 && (row == squareSelected.first && col == squareSelected.second)) {
        collection[squareSelected.first][squareSelected.second]->resetColor();
        squareSelected.first = -1;
        squareSelected.second = -1;
        return;
    }

    // Selecting
    if (squareSelected.first == -1) {
        if (side != collection[row][col]->side) return;
        squareSelected.first = row;
        squareSelected.second = col;
        collection[row][col]->setColor("#FF0000");

    }

    // Consume the select moves
    if (squareSelected.first != -1 && (row != squareSelected.first || col != squareSelected.second)) {
        collection[squareSelected.first][squareSelected.second]->resetColor();

        // MoveMessage* msg;

        // if (side == WHITE) {
        //     msg = new MoveMessage(QString::number((7 - squareSelected.first)*10 + squareSelected.second).toStdString(),
        //                           QString::number((7 - row)*10 + col).toStdString());
        // } else {
        //     msg = new MoveMessage(QString::number(squareSelected.first * 10 + (7 - squareSelected.second)).toStdString(),
        //                           QString::number(row * 10 + (7 - col)).toStdString());
        // }

        // mainwindow->sendMessage(mainwindow->connfd, msg);
        // Message* rcv = mainwindow->receiveMessage(mainwindow->connfd);

        // switch (rcv->getType()) {
        // case MOVE_NOT_OK:
        //     return;

        // case OK:
            moves(collection[squareSelected.first][squareSelected.second], collection[row][col]);
        //     break;
        // }

        squareSelected.first = -1;
        squareSelected.second = -1;

    }
}

void game::on_btnDraw_clicked()
{
    ui->lbDim->setVisible(true);
    ui->frConfirm->setVisible(true);
    ui->lbCfTitle->setText("Are you sure to offer draw?");
    choice = 1;
}


void game::on_btnYes_clicked()
{
    Message *msg;
    switch (choice) {
    case 1: // Offer draw
        msg = new Message(OFFER_DRAW);
        mainwindow->sendMessage(mainwindow->connfd, msg);
        break;
    case 2: // Resign
        msg = new Message(RESIGN);
        mainwindow->sendMessage(mainwindow->connfd, msg);
        break;
    default:
        break;
    }
    choice = 0;

    // Close pop-up notification
    ui->lbDim->setVisible(false);
    ui->frConfirm->setVisible(false);
}


void game::on_btnNo_clicked()
{
    // Close pop-up notification
    ui->lbDim->setVisible(false);
    ui->frConfirm->setVisible(false);
}


void game::on_btnResign_clicked()
{
    ui->lbDim->setVisible(true);
    ui->frConfirm->setVisible(true);
    ui->lbCfTitle->setText("Are you sure to resign?");
    choice = 2;
}

