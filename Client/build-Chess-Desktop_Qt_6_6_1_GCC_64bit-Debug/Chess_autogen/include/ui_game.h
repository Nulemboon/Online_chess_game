/********************************************************************************
** Form generated from reading UI file 'game.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_H
#define UI_GAME_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game
{
public:
    QFrame *frame;
    QFrame *frChessBoard;
    QLabel *lbOpponentName;
    QLabel *lbPlayerName;
    QFrame *frCapturedO;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *hboxOpponent;
    QFrame *frCapturedP;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *hboxPlayer;
    QFrame *frame_2;
    QPushButton *btnDraw;
    QPushButton *btnResign;
    QTableWidget *tableWidget;
    QFrame *frConfirm;
    QLabel *lbCfTitle;
    QPushButton *btnYes;
    QPushButton *btnNo;
    QFrame *frPromote;
    QPushButton *btnPrQueen;
    QPushButton *btnPrBishop;
    QPushButton *btnPrRook;
    QPushButton *btnPrKnight;
    QLabel *lbDim;
    QFrame *frResult;
    QLabel *lbResult;
    QLabel *lbResultsub;
    QLabel *lbResultPlayer;
    QLabel *lbResultOpponent;
    QLabel *label_4;
    QPushButton *btnBack;

    void setupUi(QWidget *game)
    {
        if (game->objectName().isEmpty())
            game->setObjectName("game");
        game->resize(1000, 750);
        frame = new QFrame(game);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 1000, 750));
        frame->setStyleSheet(QString::fromUtf8("QFrame#frame {background-color: #302E2B}\n"
"QLabel {color: white;}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frChessBoard = new QFrame(frame);
        frChessBoard->setObjectName("frChessBoard");
        frChessBoard->setGeometry(QRect(75, 94, 560, 560));
        frChessBoard->setFrameShape(QFrame::StyledPanel);
        frChessBoard->setFrameShadow(QFrame::Raised);
        lbOpponentName = new QLabel(frame);
        lbOpponentName->setObjectName("lbOpponentName");
        lbOpponentName->setGeometry(QRect(75, 25, 500, 22));
        QFont font;
        font.setPointSize(16);
        lbOpponentName->setFont(font);
        lbPlayerName = new QLabel(frame);
        lbPlayerName->setObjectName("lbPlayerName");
        lbPlayerName->setGeometry(QRect(75, 663, 500, 22));
        lbPlayerName->setFont(font);
        frCapturedO = new QFrame(frame);
        frCapturedO->setObjectName("frCapturedO");
        frCapturedO->setGeometry(QRect(75, 54, 560, 30));
        frCapturedO->setStyleSheet(QString::fromUtf8("background-color: #F4DCC5;"));
        frCapturedO->setFrameShape(QFrame::StyledPanel);
        frCapturedO->setFrameShadow(QFrame::Raised);
        horizontalLayoutWidget = new QWidget(frCapturedO);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 561, 31));
        hboxOpponent = new QHBoxLayout(horizontalLayoutWidget);
        hboxOpponent->setObjectName("hboxOpponent");
        hboxOpponent->setContentsMargins(0, 0, 0, 0);
        frCapturedP = new QFrame(frame);
        frCapturedP->setObjectName("frCapturedP");
        frCapturedP->setGeometry(QRect(75, 687, 560, 30));
        frCapturedP->setStyleSheet(QString::fromUtf8("background-color: #F4DCC5;"));
        frCapturedP->setFrameShape(QFrame::StyledPanel);
        frCapturedP->setFrameShadow(QFrame::Raised);
        horizontalLayoutWidget_2 = new QWidget(frCapturedP);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(0, 0, 561, 31));
        hboxPlayer = new QHBoxLayout(horizontalLayoutWidget_2);
        hboxPlayer->setObjectName("hboxPlayer");
        hboxPlayer->setContentsMargins(0, 0, 0, 0);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(700, 94, 225, 560));
        frame_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"color: black;\n"
"background-color: #EF9A09;\n"
"}"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        btnDraw = new QPushButton(frame_2);
        btnDraw->setObjectName("btnDraw");
        btnDraw->setGeometry(QRect(0, 520, 113, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Ubuntu")});
        font1.setPointSize(12);
        btnDraw->setFont(font1);
        btnResign = new QPushButton(frame_2);
        btnResign->setObjectName("btnResign");
        btnResign->setGeometry(QRect(113, 520, 112, 41));
        btnResign->setFont(font1);
        tableWidget = new QTableWidget(frame_2);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QFont font2;
        font2.setPointSize(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font2);
        __qtablewidgetitem->setBackground(QColor(0, 0, 0, 0));
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font2);
        __qtablewidgetitem1->setBackground(QColor(0, 0, 0, 0));
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font2);
        __qtablewidgetitem2->setBackground(QColor(0, 0, 0, 0));
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 225, 500));
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget {background-color: rgba(0,0,0,0);\n"
"color:white;}\n"
"QHeaderView::section {\n"
"background-color: #302E2B;\n"
"color: white}"));
        frConfirm = new QFrame(frame);
        frConfirm->setObjectName("frConfirm");
        frConfirm->setGeometry(QRect(350, 225, 300, 200));
        frConfirm->setStyleSheet(QString::fromUtf8("QFrame{background-color: #F4DCC5;\n"
" border: 8px solid orange; }\n"
"\n"
"QPushButton{ border: none; color:black;background-color:#EF9A09;border-radius:10px\n"
"}\n"
"\n"
"QPushButton:hover{background-color:#d98100}"));
        frConfirm->setFrameShape(QFrame::StyledPanel);
        frConfirm->setFrameShadow(QFrame::Raised);
        lbCfTitle = new QLabel(frConfirm);
        lbCfTitle->setObjectName("lbCfTitle");
        lbCfTitle->setGeometry(QRect(30, 45, 240, 50));
        QFont font3;
        font3.setPointSize(13);
        lbCfTitle->setFont(font3);
        lbCfTitle->setStyleSheet(QString::fromUtf8("border:none; color: black"));
        lbCfTitle->setAlignment(Qt::AlignCenter);
        btnYes = new QPushButton(frConfirm);
        btnYes->setObjectName("btnYes");
        btnYes->setGeometry(QRect(50, 140, 80, 30));
        btnYes->setFont(font2);
        btnNo = new QPushButton(frConfirm);
        btnNo->setObjectName("btnNo");
        btnNo->setGeometry(QRect(170, 140, 80, 30));
        QFont font4;
        font4.setPointSize(12);
        btnNo->setFont(font4);
        frPromote = new QFrame(frame);
        frPromote->setObjectName("frPromote");
        frPromote->setGeometry(QRect(635, 34, 240, 60));
        frPromote->setStyleSheet(QString::fromUtf8("QPushButton{background-color:#F4DCC5;}\n"
""));
        frPromote->setFrameShape(QFrame::StyledPanel);
        frPromote->setFrameShadow(QFrame::Raised);
        btnPrQueen = new QPushButton(frPromote);
        btnPrQueen->setObjectName("btnPrQueen");
        btnPrQueen->setGeometry(QRect(0, 0, 60, 60));
        btnPrBishop = new QPushButton(frPromote);
        btnPrBishop->setObjectName("btnPrBishop");
        btnPrBishop->setGeometry(QRect(120, 0, 60, 60));
        btnPrRook = new QPushButton(frPromote);
        btnPrRook->setObjectName("btnPrRook");
        btnPrRook->setGeometry(QRect(60, 0, 60, 60));
        btnPrKnight = new QPushButton(frPromote);
        btnPrKnight->setObjectName("btnPrKnight");
        btnPrKnight->setGeometry(QRect(180, 0, 60, 60));
        lbDim = new QLabel(frame);
        lbDim->setObjectName("lbDim");
        lbDim->setGeometry(QRect(0, 0, 1000, 750));
        lbDim->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0.7);"));
        frResult = new QFrame(frame);
        frResult->setObjectName("frResult");
        frResult->setGeometry(QRect(300, 75, 400, 600));
        frResult->setStyleSheet(QString::fromUtf8("QFrame{background-color: #F4DCC5;\n"
" border: 8px solid orange; }\n"
"\n"
"QPushButton{ border: none; color:black;background-color:#EF9A09;border-radius:10px\n"
"}\n"
"\n"
"QPushButton:hover{background-color:#d98100}\n"
"\n"
"QLabel {border:none; color:black}"));
        frResult->setFrameShape(QFrame::StyledPanel);
        frResult->setFrameShadow(QFrame::Raised);
        lbResult = new QLabel(frResult);
        lbResult->setObjectName("lbResult");
        lbResult->setGeometry(QRect(75, 70, 250, 100));
        QFont font5;
        font5.setPointSize(49);
        lbResult->setFont(font5);
        lbResult->setStyleSheet(QString::fromUtf8("border: none; color: black"));
        lbResult->setAlignment(Qt::AlignCenter);
        lbResultsub = new QLabel(frResult);
        lbResultsub->setObjectName("lbResultsub");
        lbResultsub->setGeometry(QRect(75, 170, 250, 20));
        lbResultsub->setFont(font4);
        lbResultsub->setStyleSheet(QString::fromUtf8("border:none;color:black"));
        lbResultsub->setAlignment(Qt::AlignCenter);
        lbResultPlayer = new QLabel(frResult);
        lbResultPlayer->setObjectName("lbResultPlayer");
        lbResultPlayer->setGeometry(QRect(70, 300, 275, 14));
        lbResultPlayer->setFont(font2);
        lbResultOpponent = new QLabel(frResult);
        lbResultOpponent->setObjectName("lbResultOpponent");
        lbResultOpponent->setGeometry(QRect(70, 410, 275, 14));
        lbResultOpponent->setFont(font2);
        lbResultOpponent->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(frResult);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(170, 350, 57, 14));
        QFont font6;
        font6.setPointSize(11);
        font6.setBold(true);
        label_4->setFont(font6);
        label_4->setAlignment(Qt::AlignCenter);
        btnBack = new QPushButton(frResult);
        btnBack->setObjectName("btnBack");
        btnBack->setGeometry(QRect(174, 510, 51, 51));
        btnBack->setCursor(QCursor(Qt::PointingHandCursor));
        btnBack->setStyleSheet(QString::fromUtf8("QPushButton { \n"
"background-color: orange; border-radius: 25px; \n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/home/assets/arrow-left.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnBack->setIcon(icon);
        btnBack->setIconSize(QSize(30, 55));
        frPromote->raise();
        frChessBoard->raise();
        lbOpponentName->raise();
        lbPlayerName->raise();
        frCapturedO->raise();
        frCapturedP->raise();
        frame_2->raise();
        lbDim->raise();
        frConfirm->raise();
        frResult->raise();

        retranslateUi(game);

        QMetaObject::connectSlotsByName(game);
    } // setupUi

    void retranslateUi(QWidget *game)
    {
        game->setWindowTitle(QCoreApplication::translate("game", "Form", nullptr));
        lbOpponentName->setText(QCoreApplication::translate("game", "Opponent", nullptr));
        lbPlayerName->setText(QCoreApplication::translate("game", "You", nullptr));
        btnDraw->setText(QCoreApplication::translate("game", "Offer Draw", nullptr));
        btnResign->setText(QCoreApplication::translate("game", "Resign", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("game", "Turn", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("game", "White", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("game", "Black", nullptr));
        lbCfTitle->setText(QCoreApplication::translate("game", "Are you sure to offer draw?", nullptr));
        btnYes->setText(QCoreApplication::translate("game", "Confirm", nullptr));
        btnNo->setText(QCoreApplication::translate("game", "Cancel", nullptr));
        btnPrQueen->setText(QString());
        btnPrBishop->setText(QString());
        btnPrRook->setText(QString());
        btnPrKnight->setText(QString());
        lbDim->setText(QString());
        lbResult->setText(QCoreApplication::translate("game", "WIN", nullptr));
        lbResultsub->setText(QCoreApplication::translate("game", "By resign", nullptr));
        lbResultPlayer->setText(QCoreApplication::translate("game", "TextLabel", nullptr));
        lbResultOpponent->setText(QCoreApplication::translate("game", "TextLabel", nullptr));
        label_4->setText(QCoreApplication::translate("game", "VS", nullptr));
        btnBack->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class game: public Ui_game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
