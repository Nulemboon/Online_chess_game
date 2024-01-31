#ifndef MATCH_H
#define MATCH_H

#include <QWidget>
#include <QGraphicsView>
#include <QGridLayout>
#include <QList>
#include "chesssquare.h"
#include "mainwindow.h"
class MainWindow;
namespace Ui {
class Match;
}

typedef struct State {
    int turn;
    ChessPiece board[8][8];
    QList<ChessPiece> playerDead, opponentDead;

    State() {}

    State(int _turn, ChessSquare* _board[8][8], QList<ChessPiece> _playerDead, QList<ChessPiece> _opponentDead) {
        turn = _turn;
        for (int i = 0; i < 8 ; i++) {
            for (int j = 0; j < 8; j++) {
                board[i][j] = _board[i][j]->getPiece();
            }
        }

        playerDead = _playerDead;
        opponentDead = _opponentDead;
    }
} State;

class Match : public QWidget
{
    Q_OBJECT

public:
    explicit Match(Side side, QString opponentName, MainWindow* mainwindow, QWidget *parent = nullptr);
    ~Match();


    void setupBoard();
    void setupBoard(State turn);
    void drawBoxes();
    void addDead(bool isPlayer);
    QString getPath(ChessPiece piece);
    void reset();

    QString opponentName;
    ChessSquare *collection[8][8];
    std::vector<std::pair<int, std::string>> moveList;
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
    QGridLayout *chessboard;
    std::vector<State> stateList;
    int loadedMove;

    void moves(ChessSquare* src, ChessSquare* dst);
    void writeLog(bool isWhite, ChessSquare* src, ChessSquare* dst); // General move
    void writeLog(bool isWhite, bool isLong); // Castling only
    void handleCastling(ChessSquare* src, ChessSquare* dst);
    void handleEnPassant(ChessSquare* src, ChessSquare* dst);
    void addBoxes();
};

#endif // MATCH_H
