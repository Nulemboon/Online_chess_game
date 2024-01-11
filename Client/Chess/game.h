#ifndef game_H
#define game_H

#include <QWidget>
#include <QGraphicsView>
#include "chesssquare.h"
#include "mainwindow.h"

namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

public:
    explicit game(Side side, QString opponentName, MainWindow* mainwindow, QWidget *parent = nullptr);
    ~game();

    void setupBoard();
    void drawBoxes();
    void addDead();
    QString getPath(ChessPiece piece);

    ChessSquare *collection[8][8];
    QPair<int, int> squareSelected;
public slots:
    void chessSquareClicked(int row, int col);
private slots:
    void on_btnDraw_clicked();

    void on_btnYes_clicked();

    void on_btnNo_clicked();

    void on_btnResign_clicked();

private:
    Ui::game *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    MainWindow* mainwindow;
    QList <ChessPiece> playerDead;
    Side side;
    QString opponentName;
    QList <ChessPiece> opponentDead;
    int choice;
    // QList <ChessPiece> white;
    // QList <ChessPiece> black;
    // QGraphicsRectItem * deadHolder;
    // QString turn;
    // ChessBoard *chess;
    // QList <QGraphicsItem *> listG;
    // QGraphicsTextItem * turnDisplay;

    void moves(ChessSquare* src, ChessSquare* dst);

};

#endif // game_H
