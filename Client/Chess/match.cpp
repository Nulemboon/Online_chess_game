#include "match.h"
#include "ui_match.h"

Match::Match(Side side, QString opponentName, MainWindow* mainwindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Match), side(side), opponentName(opponentName), mainwindow(mainwindow)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setVisible(false);
    currentMove = 0;
    loadedMove = 0;

    // std::pair<int, std::string> box;
    // box.first = 10; box.second = "30";
    // moveList.push_back(box);
    // box.first = 64; box.second = "06Q";
    // moveList.push_back(box);

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

    // Create QGridLayout inside frChessBoard
    chessboard = new QGridLayout(ui->frChessBoard);
    ui->frChessBoard->setLayout(chessboard);
    chessboard->setSpacing(0);
    chessboard->setContentsMargins(0, 0, 0, 0);

    drawBoxes();
    setupBoard();
    // addBoxes();

    // Push first state to the vector
    stateList.push_back(State(0, collection, playerDead, opponentDead));
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
            if (!box) qDebug() << "NULL";
            collection[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;
        }
    }
    // addBoxes();

}

void Match::addBoxes() {
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

    // Empty squares
    for (int i = 2; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            collection[i][j]->placePiece(NONE);
        }
    }
}

void Match::setupBoard(State turn) {
    // Load previous chessboard state
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j <8; j++) {
            collection[i][j]->placePiece(turn.board[i][j]);
        }
    }

    // Update captured pieces field
    int boxPlayer = ui->hboxPlayer->count();
    int boxOpponent = ui->hboxOpponent->count();
    if (boxPlayer > turn.playerDead.size()) {
        QLayoutItem* lastItem = ui->hboxPlayer->takeAt(ui->hboxPlayer->count() - 1);
        if (lastItem) {
            delete lastItem->widget();
            delete lastItem;
        }
    } else if (boxPlayer < turn.playerDead.size()) {
        QLabel* newLabel = new QLabel;
        newLabel->setFixedSize(30, 30);

        QPixmap backgroundImage(getPath(turn.playerDead.last()));
        newLabel->setPixmap(backgroundImage.scaled(newLabel->size(), Qt::KeepAspectRatio));
        ui->hboxPlayer->addWidget(newLabel);
    }

    if (boxOpponent > turn.opponentDead.size()) {
        QLayoutItem* lastItem = ui->hboxOpponent->takeAt(ui->hboxOpponent->count() - 1);
        if (lastItem) {
            delete lastItem->widget();
            delete lastItem;
        }
    } else if (boxOpponent < turn.opponentDead.size()) {
        QLabel* newLabel = new QLabel;
        newLabel->setFixedSize(30, 30);

        QPixmap backgroundImage(getPath(turn.opponentDead.last()));
        newLabel->setPixmap(backgroundImage.scaled(newLabel->size(), Qt::KeepAspectRatio));
        ui->hboxOpponent->addWidget(newLabel);
    }
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

void Match::addDead(bool isPlayer) {
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

void Match::moves(ChessSquare* src, ChessSquare* dst) {

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

    if (side == WHITE && dst->getPiece() == PawnW) {
        if (dst->rowLoc == 7) {

        }
    } else if (side == BLACK && dst->getPiece() == PawnB) {
        if (dst->rowLoc == 0) {
            // rowPr = dst->rowLoc;
            // colPr = dst->colLoc;
        }
    }
}

void Match::on_btnExit_clicked()
{
    mainwindow->switchScene(HISTORYS);
}

void Match::on_btnForward_clicked()
{
    // End match
    if (currentMove == moveList.size()) return;

    if (currentMove == loadedMove) {
        int src, dst;
        src = moveList[currentMove].first;
        std::string tmp = moveList[currentMove].second;
        if (tmp.length() == 2) {
            dst = std::stoi(tmp);
            moves(collection[src/10][src%10], collection[dst/10][dst%10]);
        } else {
            dst = std::stoi(tmp.substr(0, 2));
            moves(collection[src/10][src%10], collection[dst/10][dst%10]);
            char promote = tmp[2];
            ChessPiece pieceMoved = collection[dst/10][dst%10]->getPiece();
            Side pieceSide = (pieceMoved == PawnW ? WHITE : BLACK);
            bool isPlayer = side == pieceSide ? true : false;
            switch (promote) {
            case 'Q':
                collection[dst/10][dst%10]->placePiece(isPlayer ? QueenW : QueenB);
                break;

            case 'N':
                collection[dst/10][dst%10]->placePiece(isPlayer ? KnightW : KnightB);
                break;

            case 'R':
                collection[dst/10][dst%10]->placePiece(isPlayer ? RookW : RookB);
                break;

            case 'B':
                collection[dst/10][dst%10]->placePiece(isPlayer ? BishopW : BishopB);
                break;

            default:
                break;
            }
        }

        stateList.push_back(State(currentMove, collection, playerDead, opponentDead));
        loadedMove++;
        currentMove++;
    } else {
        setupBoard(stateList[++currentMove]);
    }
}


void Match::on_btnBack_clicked()
{
    if (currentMove == 0) return;
    setupBoard(stateList[--currentMove]);
}

void Match::reset() {
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
    moveList.clear();

    // Reset logs
    ui->tableWidget->setRowCount(0);

    // Reset captured pieces holders
    while (QLayoutItem *item = ui->hboxPlayer->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    while (QLayoutItem *item = ui->hboxOpponent->takeAt(0)) {
        delete item->widget();
        delete item;
    }
}

void Match::writeLog(bool isWhite, bool isLong) {
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

void Match::handleCastling(ChessSquare* src, ChessSquare* dst) {

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

void Match::handleEnPassant(ChessSquare* src, ChessSquare* dst) {
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

void Match::writeLog(bool isWhite, ChessSquare* src, ChessSquare* dst) {
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
