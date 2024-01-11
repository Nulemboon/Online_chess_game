#ifndef CHESSSQUARE_H
#define CHESSSQUARE_H

#include <QFrame>

namespace Ui {
class ChessSquare;
}

enum ChessPiece {
    PawnB,
    PawnW,
    RookB,
    RookW,
    KnightB,
    KnightW,
    BishopB,
    BishopW,
    QueenB,
    QueenW,
    KingB,
    KingW,
    NONE,
};

enum Side {
    WHITE,
    BLACK,
    CLEAR
};


class ChessSquare : public QFrame
{
    Q_OBJECT

public:
    explicit ChessSquare(QString color, QWidget *parent = nullptr);
    ~ChessSquare();

    void placePiece(ChessPiece piece);
    void setColor(QString value);
    void resetColor();
    ChessPiece getPiece() const;


    int rowLoc, colLoc;
    QString color;
    Side side;
    ChessPiece piece;
protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void clicked(int row, int col);
private:
    Ui::ChessSquare *ui;
    QBrush brush;

};

#endif // CHESSSQUARE_H
