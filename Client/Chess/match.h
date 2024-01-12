#ifndef MATCH_H
#define MATCH_H

#include <QWidget>
#include <QGraphicsView>
#include "chesssquare.h"
#include "mainwindow.h"
class MainWindow;
namespace Ui {
class Match;
}

class Match : public QWidget
{
    Q_OBJECT

public:
    explicit Match(Side side, QString opponentName, MainWindow* mainwindow, QWidget *parent = nullptr);
    ~Match();


    void setupBoard();
    void drawBoxes();
    void addDead();
    QString getPath(ChessPiece piece);
    void reset();

    QString opponentName;
    ChessSquare *collection[8][8];
    std::vector<std::pair<int, int>> moveList;
    Ui::Match *ui;

private slots:
    void on_btnExit_clicked();

    void on_btnForward_clicked();

    void on_btnBack_clicked();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    MainWindow* mainwindow;
    QList <ChessPiece> playerDead;
    Side side;
    QList <ChessPiece> opponentDead;
    int currentMove;

    void moves(ChessSquare* src, ChessSquare* dst);
};

#endif // MATCH_H
