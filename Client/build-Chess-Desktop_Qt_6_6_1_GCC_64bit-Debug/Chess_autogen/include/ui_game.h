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
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
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
    QFrame *frCapturedP;
    QFrame *frame_2;
    QPushButton *btnDraw;
    QPushButton *btnResign;
    QTableWidget *tableWidget;

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
        frCapturedO->setFrameShape(QFrame::StyledPanel);
        frCapturedO->setFrameShadow(QFrame::Raised);
        frCapturedP = new QFrame(frame);
        frCapturedP->setObjectName("frCapturedP");
        frCapturedP->setGeometry(QRect(75, 687, 560, 30));
        frCapturedP->setFrameShape(QFrame::StyledPanel);
        frCapturedP->setFrameShadow(QFrame::Raised);
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
        btnDraw->setGeometry(QRect(0, 520, 108, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Ubuntu")});
        font1.setPointSize(12);
        btnDraw->setFont(font1);
        btnResign = new QPushButton(frame_2);
        btnResign->setObjectName("btnResign");
        btnResign->setGeometry(QRect(117, 520, 108, 41));
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

        retranslateUi(game);

        QMetaObject::connectSlotsByName(game);
    } // setupUi

    void retranslateUi(QWidget *game)
    {
        game->setWindowTitle(QCoreApplication::translate("game", "Form", nullptr));
        lbOpponentName->setText(QCoreApplication::translate("game", "Opponent", nullptr));
        lbPlayerName->setText(QCoreApplication::translate("game", "Player", nullptr));
        btnDraw->setText(QCoreApplication::translate("game", "Offer Draw", nullptr));
        btnResign->setText(QCoreApplication::translate("game", "Resign", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("game", "Turn", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("game", "White", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("game", "Black", nullptr));
    } // retranslateUi

};

namespace Ui {
    class game: public Ui_game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
