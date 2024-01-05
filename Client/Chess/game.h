#ifndef game_H
#define game_H

#include <QWidget>
#include <QGraphicsView>
#include "chesssquare.h"

namespace Ui {
class game;
}

enum Side {
    WHITE,
    BLACK
};

class game : public QWidget
{
    Q_OBJECT

public:
    explicit game(Side side, QString opponentName, QWidget *parent = nullptr);
    ~game();

    void setupBoard();
    void drawBoxes();

    ChessSquare *collection[8][8];
    QPair<int, int> squareSelected;
public slots:
    void chessSquareClicked(int row, int col);
private:
    Ui::game *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    Side side;
    QString opponentName;
    // QList <ChessPiece *> whiteDead;
    // QList <ChessPiece *> blackDead;
    // QList <ChessPiece> white;
    // QList <ChessPiece> black;
    // QGraphicsRectItem * deadHolder;
    // QString turn;
    // ChessBoard *chess;
    // QList <QGraphicsItem *> listG;
    // QGraphicsTextItem * turnDisplay;

};

#endif // game_H
