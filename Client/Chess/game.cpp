#include "game.h"
#include "ui_game.h"
#include "../gameplay.h"
#include <QPointer>
#include <QObject>

game::game(Side side, QString opponentName, MainWindow* mainwindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::game), side(side), opponentName(opponentName), mainwindow(mainwindow)
{
    ui->setupUi(this);
    ui->lbDim->setVisible(false);
    ui->frConfirm->setVisible(false);
    ui->frPromote->setVisible(false);
    ui->frResult->setVisible(false);
    setupPromoteFrame();
    ui->tableWidget->verticalHeader()->hide();

    if (side == WHITE) isTurn = true;
    else isTurn = false;

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

    // Create QGridLayout inside frChessBoard
    chessboard = new QGridLayout(ui->frChessBoard);
    ui->frChessBoard->setLayout(chessboard);
    chessboard->setSpacing(0);
    chessboard->setContentsMargins(0, 0, 0, 0);

    drawBoxes();
    setupBoard();
    // addBoxes();
    // ui->lbResultPlayer->setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOff);
    // ui->lbResultOpponent->setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOff);
    squareSelected.first = -1; squareSelected.second = -1;
    rowCheck = -1; colCheck = -1;
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
            if (!box) qDebug() << "NULL";
            collection[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;

            // Connect the clicked signal to the chessSquareClicked slot
            connect(collection[i][j], &ChessSquare::clicked, this, &game::chessSquareClicked);
        }
    }
    // addBoxes();

}

void game::addBoxes() {
    int SHIFT = 70;
    for(int i=0; i<8;i++) {
        for (int j=0;j<8;j++) {
            if (side == WHITE) {
                // Player: White side
                chessboard->addWidget(collection[i][j], 7-i, j);
            } else {
                // Player: Black side
                chessboard->addWidget(collection[i][j], i, 7-j);
            }
        }
    }

    ui->frChessBoard->update();
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

    // Empty squares
    for (int i = 2; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            collection[i][j]->placePiece(NONE);
        }
    }
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

void game::addDead(bool isPlayer) {
    if (isPlayer) {
        QLabel* newLabel = new QLabel;
        newLabel->setFixedSize(30, 30);

        QPixmap backgroundImage(getPath(playerDead.last()));
        newLabel->setPixmap(backgroundImage.scaled(newLabel->size(), Qt::KeepAspectRatio));
        ui->hboxPlayer->addWidget(newLabel);
    } else {
        QLabel* newLabel = new QLabel;
        newLabel->setFixedSize(30, 30);

        QPixmap backgroundImage(getPath(opponentDead.last()));
        newLabel->setPixmap(backgroundImage.scaled(newLabel->size(), Qt::KeepAspectRatio));
        ui->hboxOpponent->addWidget(newLabel, Qt::AlignLeft);
    }
}

void game::moves(ChessSquare* src, ChessSquare* dst) {

    writeLog(src->getPiece() % 2 == 1, src, dst);

    if (dst->getPiece() != NONE && src->getPiece() != NONE) {
        Side pieceSide = dst->side;
        if (pieceSide != side) {
            playerDead.append(dst->getPiece());
            addDead(true);
        } else {
            opponentDead.append(dst->getPiece());
            addDead(false);
        }
    }

    dst->placePiece(src->getPiece());
    src->placePiece(NONE);

    // Handle Promotion
    if (side == WHITE && dst->getPiece() == PawnW) {
        if (dst->rowLoc == 7) {
            rowPr = dst->rowLoc; colPr = dst->colLoc;
            rowClicked = src->rowLoc; colClicked = src->colLoc;
        }
    } else if (side == BLACK && dst->getPiece() == PawnB) {
        if (dst->rowLoc == 0) {
            rowPr = dst->rowLoc; colPr = dst->colLoc;
            rowClicked = src->rowLoc; colClicked = src->colLoc;
        }
    }
}

void game::chessSquareClicked(int row, int col)
{
    if (!isTurn){
        return;
    }
    rowClicked = row;
    colClicked = col;

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
        // if (side != collection[row][col]->side) return;
        squareSelected.first = row;
        squareSelected.second = col;
        collection[row][col]->setColor("#fafa48");

    }

    // Consume the select moves
    if (squareSelected.first != -1 && (row != squareSelected.first || col != squareSelected.second)) {
        collection[squareSelected.first][squareSelected.second]->resetColor();
        MoveMessage* msg;

        msg = new MoveMessage(MOVE, std::to_string(squareSelected.first) + std::to_string(squareSelected.second),
                              std::to_string(row) + std::to_string(col));


        mainwindow->sendMessage(msg);

        // int sRow = squareSelected.first, sCol = squareSelected.second, dRow = row, dCol = col;
        // ChessPiece pieceToMove = collection[sRow][sCol]->getPiece();
        // if (pieceToMove == KingB || pieceToMove == KingW) {
        //     if (std::abs(sCol - dCol) > 1) {
        //         // Handle Castling
        //         handleCastling(collection[sRow][sCol], collection[dRow][dCol]);
        //     } else {
        //         moves(collection[sRow][sCol], collection[dRow][dCol]);
        //     }
        // } else if (pieceToMove == PawnB || pieceToMove == PawnW) {
        //     if ((pieceToMove == PawnW && dRow== 5) || (pieceToMove == PawnB && dRow== 2)) {
        //         if (std::abs(sCol - dCol) == 1 && collection[dRow][dCol]->piece == NONE) {
        //             // Handle En Passant
        //             handleEnPassant(collection[sRow][sCol], collection[dRow][dCol]);
        //         } else {
        //             moves(collection[sRow][sCol], collection[dRow][dCol]);
        //         }
        //     } else {
        //         moves(collection[sRow][sCol], collection[dRow][dCol]);
        //     }
        // } else {
        //     moves(collection[sRow][sCol], collection[dRow][dCol]);
        // }
        // squareSelected.first = -1;
        // squareSelected.second = -1;
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
        mainwindow->sendMessage(msg);
        break;
    case 2: // Resign
        msg = new Message(RESIGN);
        mainwindow->sendMessage(msg);
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

void game::reset() {
    // Reset chess board
    // Loop through the layout items
    for (int i = chessboard->count() - 1; i >= 0; i--) {
        // Get the item at the current index
        QLayoutItem *item = chessboard->itemAt(i);

        // Check if the item is a widget
        if (item->widget() && item->widget()->isWidgetType()) {
            // Remove the widget from the layout
            chessboard->removeWidget(item->widget());
        }
    }
    setupBoard();
    addBoxes();
    qDebug() << ((side == WHITE)? "WHITE": "BLACK");
    if (side == WHITE) isTurn = true;
    else isTurn = false;

    // Reset logs
    ui->tableWidget->setRowCount(0);;

    // Reset captured pieces holders
    while (QLayoutItem *item = ui->hboxPlayer->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    while (QLayoutItem *item = ui->hboxOpponent->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    // Setup new names
    ui->lbOpponentName->setText(opponentName);
    ui->lbPlayerName->setText(mainwindow->user);

    // Reset result frame
    ui->frResult->setVisible(false);
}

void game::setupPromoteFrame() {
    // Load the image from the resource file
    QString queenPath = getPath(side == WHITE ? QueenW : QueenB);
    QString rookPath = getPath(side == WHITE ? RookW : RookB);
    QString bishopPath = getPath(side == WHITE ? BishopW : BishopB);
    QString knightPath = getPath(side == WHITE ? KnightW : KnightB);

    // Set style sheet for buttons
    setButtonStyleSheet(ui->btnPrQueen, queenPath);
    setButtonStyleSheet(ui->btnPrRook, rookPath);
    setButtonStyleSheet(ui->btnPrBishop, bishopPath);
    setButtonStyleSheet(ui->btnPrKnight, knightPath);
}

void game::setButtonStyleSheet(QPushButton* button, const QString& imagePath) {
    // Set the style sheet with the background image
    button->setStyleSheet(QString("QPushButton {"
                                  "background-image: url('%1');"
                                  "background-repeat: no-repeat;"
                                  "background-position: center;"
                                  "background-color: #F4DCC5"
                                  "}"
                                  "QPushButton:hover {"
                                  "opacity: 0.7;"
                                  "}").arg(imagePath));
}

void game::on_btnPrQueen_clicked()
{
    ui->frPromote->setVisible(false);
    // Send message to server
    MoveMessage* msg = new MoveMessage(PROMOTE, std::to_string(rowClicked) + std::to_string(colClicked), std::to_string(rowPr) + std::to_string(colPr) + 'Q');
    mainwindow->sendMessage(msg);

    // Change Pawn into Queen
    collection[rowPr][colPr]->placePiece(side == WHITE ? QueenW : QueenB);
    rowClicked = -1; colClicked = -1;
    rowPr = -1; colPr = -1;
}


void game::on_btnPrKnight_clicked()
{
    ui->frPromote->setVisible(false);
    // Send message to server
    MoveMessage* msg = new MoveMessage(PROMOTE, std::to_string(rowClicked) + std::to_string(colClicked), std::to_string(rowPr) + std::to_string(colPr) + 'N');
    mainwindow->sendMessage(msg);

    // Change Pawn into Knight
    collection[rowPr][colPr]->placePiece(side == WHITE ? KnightW : KnightB);
    rowClicked = -1; colClicked = -1;
    rowPr = -1; colPr = -1;
}


void game::on_btnPrRook_clicked()
{
    ui->frPromote->setVisible(false);
    // Send message to server
    MoveMessage* msg = new MoveMessage(PROMOTE, std::to_string(rowClicked) + std::to_string(colClicked), std::to_string(rowPr) + std::to_string(colPr) + 'R');
    mainwindow->sendMessage(msg);

    // Change Pawn into Rook
    collection[rowPr][colPr]->placePiece(side == WHITE ? RookW : RookB);
    rowClicked = -1; colClicked = -1;
    rowPr = -1; colPr = -1;
}


void game::on_btnPrBishop_clicked()
{
    ui->frPromote->setVisible(false);
    // Send message to server
    MoveMessage* msg = new MoveMessage(PROMOTE, std::to_string(rowClicked) + std::to_string(colClicked), std::to_string(rowPr) + std::to_string(colPr) + 'B');
    mainwindow->sendMessage(msg);

    // Change Pawn into Bishop
    collection[rowPr][colPr]->placePiece(side == WHITE ? BishopW : BishopB);
    rowClicked = -1; colClicked = -1;
    rowPr = -1; colPr = -1;
}

void game::writeLog(bool isWhite, bool isLong) {
    // Create a new row
    int rowIdx = ui->tableWidget->rowCount();
    QTableWidgetItem* moveItem = new QTableWidgetItem;

    if (isLong) {
        moveItem->setText("O-O-O");
    } else {
        moveItem->setText("O-O");
    }
    moveItem->setFlags(moveItem->flags() & ~Qt::ItemIsSelectable);

    if (isWhite) {
        ui->tableWidget->insertRow(rowIdx);

        // Populate the Turn, White, and Black columns
        QTableWidgetItem* turnItem = new QTableWidgetItem(QString::number(rowIdx + 1));
        QTableWidgetItem* tmpItem = new QTableWidgetItem("");



        // Set items in the respective columns
        turnItem->setFlags(turnItem->flags() & ~Qt::ItemIsSelectable);

        ui->tableWidget->setItem(rowIdx, 0, turnItem);
        ui->tableWidget->setItem(rowIdx, 1, moveItem);
        ui->tableWidget->setItem(rowIdx, 2, tmpItem);
    } else {
        ui->tableWidget->setItem(rowIdx - 1, 2, moveItem);
    }
}

void game::handleCastling(ChessSquare* src, ChessSquare* dst) {

    // Move King
    dst->placePiece(src->getPiece());
    src->placePiece(NONE);

    // Move Rook
    if (dst->colLoc == 2) {
        if (dst->rowLoc == 0) {
            collection[0][3]->placePiece(collection[0][0]->getPiece());
            collection[0][0]->placePiece(NONE);
            writeLog(true, true);
        } else {
            collection[7][3]->placePiece(collection[7][0]->getPiece());
            collection[7][0]->placePiece(NONE);
            writeLog(false, true);
        }
    } else if (dst->colLoc == 6) {
        if (dst->rowLoc == 0) {
            collection[0][5]->placePiece(collection[0][7]->getPiece());
            collection[0][7]->placePiece(NONE);
            writeLog(true, false);
        } else {
            collection[7][5]->placePiece(collection[7][7]->getPiece());
            collection[7][7]->placePiece(NONE);
            writeLog(false, false);
        }
    }
}

void game::handleEnPassant(ChessSquare* src, ChessSquare* dst) {
    int isPlayer;
    // Player side | Piece side
    if (src->getPiece() == PawnW) {
        if (side == BLACK) isPlayer = 0; // BW
        else isPlayer = 1; // WW
    } else {
        if (side == BLACK) isPlayer = 3; // BB
        else isPlayer = 4; // WB
    }

    if (src->getPiece() == PawnW) {
        collection[4][dst->colLoc]->placePiece(NONE);
    } else {
        collection[3][dst->colLoc]->placePiece(NONE);
    }

    switch (isPlayer) {
    case 0:
        playerDead.append(PawnB);
        addDead(true);
        break;
    case 1:
        opponentDead.append(PawnB);
        addDead(false);
        break;
    case 2:
        opponentDead.append(PawnW);
        addDead(false);
        break;
    case 3:
        playerDead.append(PawnW);
        addDead(true);
        break;
    }

    moves(src, dst);
}

void game::writeLog(bool isWhite, ChessSquare* src, ChessSquare* dst) {
    // Create a new row
    int rowIdx = ui->tableWidget->rowCount();
    QTableWidgetItem* moveItem = new QTableWidgetItem;

    moveItem->setText(static_cast<char>(src->colLoc + 'A') +
                      QString::number(src->rowLoc + 1) + "-" +
                      static_cast<char>(dst->colLoc + 'A') +
                          QString::number(dst->rowLoc + 1));
    moveItem->setFlags(moveItem->flags() & ~Qt::ItemIsSelectable);
    if (isWhite) {
        ui->tableWidget->insertRow(rowIdx);

        // Populate the Turn, White, and Black columns
        QTableWidgetItem* turnItem = new QTableWidgetItem(QString::number(rowIdx + 1));
        QTableWidgetItem* tmpItem = new QTableWidgetItem("");



        // Set items in the respective columns
        turnItem->setFlags(turnItem->flags() & ~Qt::ItemIsSelectable);

        ui->tableWidget->setItem(rowIdx, 0, turnItem);
        ui->tableWidget->setItem(rowIdx, 1, moveItem);
        ui->tableWidget->setItem(rowIdx, 2, tmpItem);
    } else {
        ui->tableWidget->setItem(rowIdx - 1, 2, moveItem);
    }
}


void game::on_btnBack_clicked()
{
    mainwindow->switchScene(PLAYS);
}

