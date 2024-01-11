#include "chesssquare.h"
#include "ui_chesssquare.h"

ChessSquare::ChessSquare(QString color, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ChessSquare), color(color), piece(NONE)
{
    ui->setupUi(this);
    ui->frame->setStyleSheet("background-color: " + color);
    brush.setStyle(Qt::SolidPattern);
}

ChessSquare::~ChessSquare()
{
    delete ui;
}

ChessPiece ChessSquare::getPiece() const {
    return piece;
}

void ChessSquare::placePiece(ChessPiece piece_) {
    piece = piece_;
    QString path(":/ChessPiece/assets/");
    switch (piece) {
    case PawnB:
        path += "pawnB.png";
        side = BLACK;
        break;
    case PawnW:
        path += "pawnW.png";
        side = WHITE;
        break;
    case RookB:
        path += "rookB.png";
        side = BLACK;
        break;
    case RookW:
        path += "rookW.png";
        side = WHITE;
        break;
    case KnightB:
        path += "horseB.png";
        side = BLACK;
        break;
    case KnightW:
        path += "horseW.png";
        side = WHITE;
        break;
    case BishopB:
        path += "bishopB.png";
        side = BLACK;
        break;
    case BishopW:
        path += "bishopW.png";
        side = WHITE;
        break;
    case QueenB:
        path += "queenB.png";
        side = BLACK;
        break;
    case QueenW:
        path += "queenW.png";
        side = WHITE;
        break;
    case KingB:
        path += "kingB.png";
        side = BLACK;
        break;
    case KingW:
        path += "kingW.png";
        side = WHITE;
        break;
    case NONE:
        path += "Empty.png";
        side = CLEAR;
        break;
    default:
        return;
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
