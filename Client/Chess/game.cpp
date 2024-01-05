#include "game.h"
#include "ui_game.h"

game::game(Side side, QString opponentName, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::game), side(side), opponentName(opponentName)
{
    ui->setupUi(this);

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

    ui->lbOpponentName->setText(opponentName);

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
            box->setGeometry((SHIFT*j),(SHIFT*i), 70, 70);

            // Connect the clicked signal to the chessSquareClicked slot
            connect(collection[i][j], &ChessSquare::clicked, this, &game::chessSquareClicked);
        }
    }

}

void game::setupBoard() {

    if (side == WHITE) {

        // Black pieces
        collection[0][0]->placePiece(RookB);
        collection[0][1]->placePiece(KnightB);
        collection[0][2]->placePiece(BishopB);
        collection[0][3]->placePiece(QueenB);
        collection[0][4]->placePiece(KingB);
        collection[0][5]->placePiece(BishopB);
        collection[0][6]->placePiece(KnightB);
        collection[0][7]->placePiece(RookB);
        for (int i = 0; i< 8; i++) {
            collection[1][i]->placePiece(PawnB);
        }

        // White pieces
        for (int i = 0; i< 8; i++) {
            collection[6][i]->placePiece(PawnW);
        }
        collection[7][0]->placePiece(RookW);
        collection[7][1]->placePiece(KnightW);
        collection[7][2]->placePiece(BishopW);
        collection[7][3]->placePiece(QueenW);
        collection[7][4]->placePiece(KingW);
        collection[7][5]->placePiece(BishopW);
        collection[7][6]->placePiece(KnightW);
        collection[7][7]->placePiece(RookW);
    } else {
        // Black pieces
        collection[7][0]->placePiece(RookB);
        collection[7][1]->placePiece(KnightB);
        collection[7][2]->placePiece(BishopB);
        collection[7][4]->placePiece(QueenB);
        collection[7][3]->placePiece(KingB);
        collection[7][5]->placePiece(BishopB);
        collection[7][6]->placePiece(KnightB);
        collection[7][7]->placePiece(RookB);
        for (int i = 0; i< 8; i++) {
            collection[6][i]->placePiece(PawnB);
        }

        // White pieces
        for (int i = 0; i< 8; i++) {
            collection[1][i]->placePiece(PawnW);
        }
        collection[0][0]->placePiece(RookW);
        collection[0][1]->placePiece(KnightW);
        collection[0][2]->placePiece(BishopW);
        collection[0][4]->placePiece(QueenW);
        collection[0][3]->placePiece(KingW);
        collection[0][5]->placePiece(BishopW);
        collection[0][6]->placePiece(KnightW);
        collection[0][7]->placePiece(RookW);
    }

}

void game::chessSquareClicked(int row, int col)
{
    // Print coordinates of the clicked box
    qDebug() << "Clicked on box at row:" << row << "column:" << col;

    // Deselect
    if (squareSelected.first != -1 && (row == squareSelected.first && col == squareSelected.second)) {
        collection[squareSelected.first][squareSelected.second]->resetColor();
        squareSelected.first = -1;
        squareSelected.second = -1;
        return;
    }

    // Selecting
    if (squareSelected.first == -1) {
        squareSelected.first = row;
        squareSelected.second = col;
        collection[row][col]->setColor("#FF0000");
    }
}
