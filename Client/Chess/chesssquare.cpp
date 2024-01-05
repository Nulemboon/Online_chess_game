#include "chesssquare.h"
#include "ui_chesssquare.h"

ChessSquare::ChessSquare(QString color, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ChessSquare), color(color), piece(piece)
{
    ui->setupUi(this);
    ui->frame->setStyleSheet("background-color: " + color);
    brush.setStyle(Qt::SolidPattern);
}

ChessSquare::~ChessSquare()
{
    delete ui;
}

void ChessSquare::placePiece(ChessPiece piece) {
    QString path(":/ChessPiece/assets/");
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
    }
    // Load the image from the resource file
    QPixmap logoPixmap(path);

    // Set the scaled contents property on the QPixmap
    logoPixmap = logoPixmap.scaled(ui->lbPiece->size(), Qt::KeepAspectRatio);

    // Set the pixmap to the QLabel
    ui->lbPiece->setPixmap(logoPixmap);
}

void ChessSquare::setColor(QString value) {
    ui->frame->setStyleSheet("background-color: " + value);
}

void ChessSquare::resetColor() {
    setColor(color);
}

void ChessSquare::mousePressEvent(QMouseEvent *event)
{
    // Emit the clicked signal with the row and column information
    emit clicked(rowLoc, colLoc);

    QFrame::mousePressEvent(event);
}
