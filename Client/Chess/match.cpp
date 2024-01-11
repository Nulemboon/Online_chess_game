#include "match.h"
#include "ui_match.h"

Match::Match(Side side, QString opponentName, MainWindow* mainwindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Match), side(side), opponentName(opponentName), mainwindow(mainwindow)
{
    ui->setupUi(this);
    currentMove = 0;

    std::pair<int, int> box;
    box.first = 10; box.second = 30;
    moveList.push_back(box);
    box.first = 67; box.second = 47;
    moveList.push_back(box);

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
}

Match::~Match()
{
    delete ui;
}

void Match::drawBoxes()
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
        }
    }

}

void Match::setupBoard() {

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

QString Match::getPath(ChessPiece piece) {
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

void Match::addDead() {
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

void Match::on_btnExit_clicked()
{
    mainwindow->switchScene(HISTORYS);
}

void Match::reset() {
    setupBoard();
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            collection[i][j]->placePiece(NONE);
        }
    }
}

void Match::moves(ChessSquare* src, ChessSquare* dst) {
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

void Match::on_btnForward_clicked()
{
    if (currentMove == moveList.size()) return;
    int src, dst;
    src = moveList[currentMove].first;
    dst = moveList[currentMove].second;

    moves(collection[src/10][src%10], collection[dst/10][dst%10]);
    currentMove++;
}


void Match::on_btnBack_clicked()
{
    if (currentMove == 0) return;
    int src, dst;
    src = moveList[currentMove - 1].first;
    dst = moveList[currentMove - 1].second;

    moves(collection[dst/10][dst%10], collection[src/10][src%10]);
    currentMove--;
}

