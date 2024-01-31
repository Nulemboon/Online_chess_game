#ifndef game_H
#define game_H

#include <QWidget>
#include <QGraphicsView>
#include <QPushButton>
#include <QGridLayout>
#include "chesssquare.h"
#include "mainwindow.h"
class MainWindow;
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
    void addDead(bool isPlayer);
    void reset();
    QString getPath(ChessPiece piece);
    void moves(ChessSquare* src, ChessSquare* dst);
    void handleCastling(ChessSquare* src, ChessSquare* dst);
    void handleEnPassant(ChessSquare* src, ChessSquare* dst);

    ChessSquare *collection[8][8];
    QPair<int, int> squareSelected;
    QString opponentName;
    Side side;
    Ui::game *ui;
    bool isTurn;
    int rowPr, colPr;
    int rowClicked, colClicked, rowCheck, colCheck;
public slots:
    void chessSquareClicked(int row, int col);
private slots:
    void on_btnDraw_clicked();

    void on_btnYes_clicked();

    void on_btnNo_clicked();

    void on_btnResign_clicked();

    void on_btnPrQueen_clicked();

    void on_btnPrKnight_clicked();

    void on_btnPrRook_clicked();

    void on_btnPrBishop_clicked();

    void on_btnBack_clicked();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    MainWindow* mainwindow;
    QList <ChessPiece> playerDead;
    QList <ChessPiece> opponentDead;
    int choice;
    QGridLayout *chessboard;
    // QList <ChessPiece> white;
    // QList <ChessPiece> black;
    // QGraphicsRectItem * deadHolder;
    // QString turn;
    // ChessBoard *chess;
    // QList <QGraphicsItem *> listG;
    // QGraphicsTextItem * turnDisplay;

    void setupPromoteFrame();
    void setButtonStyleSheet(QPushButton* button, const QString& imagePath);
    void writeLog(bool isWhite, ChessSquare* src, ChessSquare* dst); // General move
    void writeLog(bool isWhite, bool isLong); // Castling only
    void addBoxes();

};

#endif // game_H
