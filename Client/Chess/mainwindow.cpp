#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "home.h"
#include "game.h"
#include "history.h"
#include "play.h"
#include "match.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stackedWidget = new QStackedWidget(this);
    connect(&client, &MyClient::messageReceived, this, &MainWindow::onMessageReceived);

    // Initiate scenes
    homeWid = new Home(this, this);
    historyWid = new history(this, this);
    matchWid = new Match(WHITE, "Opponent", this, this);
    playWid = new play(this, this);
    gameWid = new game(WHITE, "Opponent", this, this);

    // Add scenes to a stackedWidget
    stackedWidget->addWidget(homeWid);
    stackedWidget->addWidget(historyWid);
    stackedWidget->addWidget(matchWid);
    stackedWidget->addWidget(playWid);
    stackedWidget->addWidget(gameWid);

    // Set the central widget as the stacked widget
    setCentralWidget(stackedWidget);

    // Show the initial widget (home)
    stackedWidget->setCurrentIndex(HOMES);

    // homeWid->ui->lbDim->setVisible(false);
    // homeWid->ui->btnPlay->setEnabled(true);

    // MatchFoundMessage* rcv = new MatchFoundMessage(MATCH_FOUND, 1, "test", 100);
    // switchScene(GAMES);

    // gameWid->side = rcv->getColor() == 1 ? WHITE : BLACK;
    // gameWid->opponentName = QString::fromStdString(rcv->getName());
    // gameWid->reset();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMessage(Message *message) {
    client.sendMessage(QString::fromStdString(message->serialize()) + "\n\n", message->getLength() + 5);
    qDebug() << "Type: " << message->getType();
    qDebug() << "Length: " << message->getLength();
}

void MainWindow::switchScene(Scene sceneType) {
    stackedWidget->setCurrentIndex(sceneType);
}

void MainWindow::onMessageReceived(const QString &message)
{
    Message* rcv = new Message(message.toStdString());

    switch (rcv->getType()) {
    case HISTORY:
        handleHistory(rcv);
        break;

    case MATCH:
        handleMatch(rcv);
        break;

    case REGISTER_USERNAME_EXISTED:
        handleRegisterUsernameExisted(rcv);
        break;

    case REGISTER_PASSWORD_FAIL:
        handleRegisterPasswordFail(rcv);
        break;

    case REGISTER_SUCCESSFUL:
        handleRegisterSuccessful(rcv);
        break;

    case LOGIN_FAIL:
        handleLoginFail(rcv);
        break;

    case USER_BLOCKED:
        handleUserBlocked(rcv);
        break;

    case USER_LOGGED_IN:
        handleUserLoggedIn(rcv);
        break;

    case LOGIN_SUCCESSFUL:
        handleLoginSuccessful(rcv);
        break;

    case ONLINE_LIST:
        handleOnlineList(rcv);
        break;

    case MATCH_FOUND:
        handleMatchFound(rcv);
        break;

    case MATCHMAKING_TIMEOUT:
        handleMatchmakingTimeout(rcv);
        break;

    case MOVE_NOT_OK:
        handleMoveNotOk(rcv);
        break;

    case STALEMATE:
        handleStalemate(rcv);
        break;

    case THREE_FOLD:
        handleThreeFold(rcv);
        break;

    case FIFTY:
        handleFifty(rcv);
        break;

    case GAME_DRAW:
        handleGameDraw(rcv);
        break;

    case GAME_WIN:
        handleGameWin(rcv);
        break;

    case GAME_LOSE:
        handleGameLose(rcv);
        break;
    case ERROR:
        handleError(rcv);
        break;

    case MOVE:
        handleMove(rcv);
        break;

    case OK:
        handleOK(rcv);
        break;

    case INVITE:
        handleInvite(rcv);
        break;

    case IS_CHECK:
        handleIsCheck(rcv);
        break;

    case PROMOTE:
        handlePromote(rcv);
        break;

    case OFFER_DRAW:
        handleOfferDraw(rcv);
        break;

    default:
        break;
    }
}

void MainWindow::handleHistory(Message *msg) {
    HistoryMessage *msgH = new HistoryMessage(*msg);
    std::vector<std::map<std::string, std::string>> newHistory = msgH->getMatches();
    historyWid->matches.insert(historyWid->matches.end(), newHistory.begin(), newHistory.end());

    historyWid->fetchData(newHistory);
}

void MainWindow::handleMatch(Message *msg) {
    HistoryMessage *rcv = new HistoryMessage(*msg);

    // Parse move
    std::vector<std::pair<int, std::string>> test;
    std::string delimiter = ",";
    std::string token = "";
    size_t pos = 0;
    std::string s = rcv->getMatches()[0]["moves"];
    while ((pos = s.find(delimiter)) != std::string::npos) {
        if (s.length() <= 1) break;
        token = s.substr(0, pos);
        s.erase(0, pos + delimiter.length());

        if (token.length() == 4) {
            test.push_back(std::pair(std::stoi(token.substr(0, 2)), token.substr(2, 2)));
        } else {
            test.push_back(std::pair(std::stoi(token.substr(0, 2)), token.substr(2, 3)));
        }
    }


    // Switch scene to Match
    switchScene(MATCHS);

    std::map<std::string, std::string> match = historyWid->matches[historyWid->rowClicked];
    matchWid->reset();
    std::string sideO;
    int sideMatch = match["whiteID"] == user.toStdString() ? 0 : 1; // 0 for White, 1 for Black
    // QString nameO = sideMatch == 1 ? QString::fromStdString(match["blackID"]) : QString::fromStdString(match["whiteID"]);
    if (sideMatch == 0) {
        sideO = "blackID";
    } else {
        sideO = "whiteID";
    }

    matchWid->opponentName = QString::fromStdString(match[sideO]);
    matchWid->moveList.insert(matchWid->moveList.end(), test.begin(), test.end());
}

void MainWindow::handleRegisterUsernameExisted(Message *msg) {
    homeWid->ui->lbNoti->setText("Username already existed");
}

void MainWindow::handleRegisterPasswordFail(Message *msg) {
    return;
}

void MainWindow::handleRegisterSuccessful(Message *msg) {
    user = homeWid->ui->txtUsername->text(); // Set the username for this session
    // Remove the login layer
    homeWid->ui->lbDim->setVisible(false);
    homeWid->ui->frLogin->setVisible(false);
    homeWid->ui->btnPlay->setEnabled(true);
    homeWid->ui->btnHistory->setEnabled(true);
    homeWid->ui->btnOptions->setEnabled(true);
    homeWid->ui->btnLogout->setEnabled(true);
}

void MainWindow::handleLoginFail(Message *msg) {
    homeWid->ui->lbNoti->setText("Wrong username or password. Try again.");
}

void MainWindow::handleUserBlocked(Message *msg) {
    homeWid->ui->lbNoti->setText("Too many fail attempts. This account is blocked.");
}

void MainWindow::handleUserLoggedIn(Message *msg) {
    homeWid->ui->lbNoti->setText("This account is logged in another device.");
}

void MainWindow::handleLoginSuccessful(Message *msg) {
    user = homeWid->ui->txtUsername->text(); // Set the username for this session
    homeWid->ui->txtUsername->setText("");
    homeWid->ui->txtPassword->setText("");
    // Remove the login layer
    homeWid->ui->lbDim->setVisible(false);
    homeWid->ui->frLogin->setVisible(false);
    homeWid->ui->btnPlay->setEnabled(true);
    homeWid->ui->btnHistory->setEnabled(true);
    homeWid->ui->btnOptions->setEnabled(true);
    homeWid->ui->btnLogout->setEnabled(true);
}

void MainWindow::handleOnlineList(Message *msg) {

    ListMessage *rcv = new ListMessage(*msg);
    std::vector<std::pair<std::string, int>> newList = rcv->getList();
    playWid->list = newList;

    playWid->fetchData();
}

void MainWindow::handleMatchFound(Message *msg) {
    playWid->ui->btnInvite->setEnabled(true);
    playWid->ui->btnRefresh->setEnabled(true);
    playWid->ui->btnBack->setEnabled(true);
    playWid->ui->btnMM->setText("RANDOM\nMATCHMAKING");
    playWid->ui->btnMM->setEnabled(true);
    playWid->ui->playView->setRowCount(0);

    MatchFoundMessage* rcv = new MatchFoundMessage(*msg);
    // Setup game scene
    switchScene(GAMES);
    gameWid->side = rcv->getColor() == 1 ? WHITE : BLACK;
    gameWid->opponentName = QString::fromStdString(rcv->getName());
    gameWid->reset();

}

void MainWindow::handleMatchmakingTimeout(Message *msg) {
    // Enable all buttons
    playWid->ui->btnInvite->setEnabled(true);
    playWid->ui->btnRefresh->setEnabled(true);
    playWid->ui->btnBack->setEnabled(true);
    playWid->ui->btnMM->setText("RANDOM\nMATCHMAKING");
    playWid->ui->lbNoMM->setVisible(true);
    playWid->ui->btnYes->setEnabled(true);
    playWid->ui->btnNo->setEnabled(true);
    playWid->ui->btnMM->setEnabled(true);
}

void MainWindow::handleMoveNotOk(Message *msg) {
    gameWid->squareSelected.first = -1;
    gameWid->squareSelected.second = -1;
    return;
}

void MainWindow::handleStalemate(Message *msg) {
    gameWid->ui->lbDim->setVisible(true);
    gameWid->ui->frResult->setVisible(true);
    gameWid->ui->lbResult->setText("DRAW");
    gameWid->ui->lbResultsub->setText("By Stalemate");
    gameWid->ui->lbResultPlayer->setText(user);
    gameWid->ui->lbResultOpponent->setText(gameWid->opponentName);
}

void MainWindow::handleThreeFold(Message *msg) {
    gameWid->ui->lbDim->setVisible(true);
    gameWid->ui->frResult->setVisible(true);
    gameWid->ui->lbResult->setText("DRAW");
    gameWid->ui->lbResultsub->setText("By Three Fold");
    gameWid->ui->lbResultPlayer->setText(user);
    gameWid->ui->lbResultOpponent->setText(gameWid->opponentName);
}

void MainWindow::handleFifty(Message *msg) {
    gameWid->ui->lbDim->setVisible(true);
    gameWid->ui->frResult->setVisible(true);
    gameWid->ui->lbResult->setText("DRAW");
    gameWid->ui->lbResultsub->setText("By Fifty Rules");
    gameWid->ui->lbResultPlayer->setText(user);
    gameWid->ui->lbResultOpponent->setText(gameWid->opponentName);
}

void MainWindow::handleGameDraw(Message *msg) {
    gameWid->ui->lbDim->setVisible(true);
    gameWid->ui->frResult->setVisible(true);
    gameWid->ui->lbResult->setText("DRAW");
    gameWid->ui->lbResultsub->setText("By Offer Draw");
    gameWid->ui->lbResultPlayer->setText(user);
    gameWid->ui->lbResultOpponent->setText(gameWid->opponentName);
}

void MainWindow::handleGameWin(Message *msg) {
    gameWid->ui->lbDim->setVisible(true);
    gameWid->ui->frResult->setVisible(true);
    gameWid->ui->lbResult->setText("WIN");
    gameWid->ui->lbResultsub->setText("");
    gameWid->ui->lbResultPlayer->setText(user);
    gameWid->ui->lbResultOpponent->setText(gameWid->opponentName);
}

void MainWindow::handleGameLose(Message *msg) {
    gameWid->ui->lbDim->setVisible(true);
    gameWid->ui->frResult->setVisible(true);
    gameWid->ui->lbResult->setText("LOSE");
    gameWid->ui->lbResultsub->setText("");
    gameWid->ui->lbResultPlayer->setText(user);
    gameWid->ui->lbResultOpponent->setText(gameWid->opponentName);
}

void MainWindow::handleError(Message *msg) {
    ErrorMessage *rcv = new ErrorMessage(*msg);
    qDebug() << QString::fromStdString(rcv->getError());
    exit(1);
}

void MainWindow::handleMove(Message *msg) {
    MoveMessage *rcv = new MoveMessage(*msg);
    int sRow, sCol, dRow, dCol;
    sRow = rcv->getSource()[0] - '0'; sCol = rcv->getSource()[1] - '0';
    dRow = rcv->getDestination()[0] - '0'; dCol = rcv->getDestination()[1] - '0';

    ChessPiece pieceToMove = gameWid->collection[sRow][sCol]->getPiece();
    qDebug() << pieceToMove;

    // Check special move
    if (pieceToMove == KingB || pieceToMove == KingW) {
        if (std::abs(sCol - dCol) > 1) {
            // Handle Castling
            gameWid->handleCastling(gameWid->collection[sRow][sCol], gameWid->collection[dRow][dCol]);
        } else {
            gameWid->moves(gameWid->collection[sRow][sCol], gameWid->collection[dRow][dCol]);
        }
    } else if (pieceToMove == PawnB || pieceToMove == PawnW) {
        if ((pieceToMove == PawnW && dRow== 5) || (pieceToMove == PawnB && dRow== 2)) {
            if (std::abs(sCol - dCol) == 1 && gameWid->collection[dRow][dCol]->piece == NONE) {
                // Handle En Passant
                gameWid->handleEnPassant(gameWid->collection[sRow][sCol], gameWid->collection[dRow][dCol]);
            } else {
                gameWid->moves(gameWid->collection[sRow][sCol], gameWid->collection[dRow][dCol]);
            }
        } else {
            gameWid->moves(gameWid->collection[sRow][sCol], gameWid->collection[dRow][dCol]);
        }
    } else {
        gameWid->moves(gameWid->collection[sRow][sCol], gameWid->collection[dRow][dCol]);
    }

    gameWid->isTurn = true;
}

void MainWindow::handleOK(Message* msg) {

    ChessPiece pieceToMove = gameWid->collection[gameWid->squareSelected.first][gameWid->squareSelected.second]->piece;
    if (pieceToMove == KingB || pieceToMove == KingW) {
        if (std::abs(gameWid->squareSelected.second - gameWid->colClicked) > 1) {
            // Handle Castling
            gameWid->handleCastling(gameWid->collection[gameWid->squareSelected.first][gameWid->squareSelected.second], gameWid->collection[gameWid->rowClicked][gameWid->colClicked]);
        } else {
            gameWid->moves(gameWid->collection[gameWid->squareSelected.first][gameWid->squareSelected.second], gameWid->collection[gameWid->rowClicked][gameWid->colClicked]);
        }
    } else if (pieceToMove == PawnB || pieceToMove == PawnW) {
        if ((pieceToMove == PawnW && gameWid->rowClicked== 5) || (pieceToMove == PawnB && gameWid->rowClicked== 2)) {
            if (std::abs(gameWid->squareSelected.second - gameWid->colClicked) == 1 && gameWid->collection[gameWid->rowClicked][gameWid->colClicked]->getPiece() == NONE) {
                // Handle En Passant
                gameWid->handleEnPassant(gameWid->collection[gameWid->squareSelected.first][gameWid->squareSelected.second], gameWid->collection[gameWid->rowClicked][gameWid->colClicked]);
            } else {
                gameWid->moves(gameWid->collection[gameWid->squareSelected.first][gameWid->squareSelected.second], gameWid->collection[gameWid->rowClicked][gameWid->colClicked]);
            }
        } else {
            gameWid->moves(gameWid->collection[gameWid->squareSelected.first][gameWid->squareSelected.second], gameWid->collection[gameWid->rowClicked][gameWid->colClicked]);
        }
    } else {
        gameWid->moves(gameWid->collection[gameWid->squareSelected.first][gameWid->squareSelected.second], gameWid->collection[gameWid->rowClicked][gameWid->colClicked]);
    }
    gameWid->isTurn = false;

    if (gameWid->rowCheck != -1) {
        gameWid->collection[gameWid->rowCheck][gameWid->colCheck]->resetColor();
        gameWid->rowCheck = -1;
        gameWid->colCheck = -1;
    }

    gameWid->squareSelected.first = -1;
    gameWid->squareSelected.second = -1;
}

void MainWindow::handleInvite(Message *msg) {
    UserMessage* rcv = new UserMessage(*msg);

    std::string opponent = rcv->getUsername();
    int elo = std::stoi(rcv->getPassword());
    std::pair<std::string, int> oppo;
    oppo.first = opponent; oppo.second = elo;
    playWid->inviteList.push_back(oppo);

    if (playWid->inviteList.size() == 1) {
        playWid->ui->frInvite->setVisible(true);
        playWid->ui->lbNameInvite->setText(QString::fromStdString(playWid->inviteList.begin()->first) + " (" + QString::number(playWid->inviteList.begin()->second) + ")");
    } else {
        QGraphicsDropShadowEffect *g = new QGraphicsDropShadowEffect(this);
        QColor q(244, 220, 197, 200);
        g->setColor(q);
        playWid->ui->frInvite->setGraphicsEffect(g);
    }
}

void MainWindow::handleIsCheck(Message *msg) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (gameWid->collection[row][col]->getPiece() == (gameWid->side == WHITE? KingW : KingB)) {
                gameWid->collection[row][col]->setColor("#b83228");
                gameWid->rowCheck = row;
                gameWid->colCheck = col;
                return;
            }
        }
    }
}

void MainWindow::handlePromote(Message *msg) {
    if (msg->getLength() == 0) {
        gameWid->ui->frPromote->setVisible(true);

    } else {
        MoveMessage *rcv = new MoveMessage(*msg);
        int sRow, sCol, dRow, dCol;
        sRow = rcv->getSource()[0] - '0'; sCol = rcv->getSource()[1] - '0';
        dRow = rcv->getDestination()[0] - '0'; dCol = rcv->getDestination()[1] - '0';

        gameWid->moves(gameWid->collection[sRow][sCol], gameWid->collection[dRow][dCol]);

        switch (rcv->getDestination()[2]) {
        case 'Q':
            gameWid->collection[dRow][dCol]->placePiece(gameWid->side == BLACK ? QueenW : QueenB);
            break;

        case 'N':
            gameWid->collection[dRow][dCol]->placePiece(gameWid->side == BLACK  ? KnightW : KnightB);
            break;

        case 'R':
            gameWid->collection[dRow][dCol]->placePiece(gameWid->side == BLACK  ? RookW : RookB);
            break;

        case 'B':
            gameWid->collection[dRow][dCol]->placePiece(gameWid->side == BLACK  ? BishopW : BishopB);
            break;

        default:
            break;
        }

        gameWid->isTurn = true;
    }
}

void MainWindow::handleOfferDraw(Message *msg) {
    gameWid->frOffer2->setVisible(true);
}
