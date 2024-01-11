/********************************************************************************
** Form generated from reading UI file 'match.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATCH_H
#define UI_MATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Match
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
    QTableWidget *tableWidget;
    QPushButton *btnBack;
    QPushButton *btnExit;
    QPushButton *btnForward;

    void setupUi(QWidget *Match)
    {
        if (Match->objectName().isEmpty())
            Match->setObjectName("Match");
        Match->resize(1000, 750);
        frame = new QFrame(Match);
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
        tableWidget = new QTableWidget(frame_2);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QFont font1;
        font1.setPointSize(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font1);
        __qtablewidgetitem->setBackground(QColor(0, 0, 0, 0));
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font1);
        __qtablewidgetitem1->setBackground(QColor(0, 0, 0, 0));
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font1);
        __qtablewidgetitem2->setBackground(QColor(0, 0, 0, 0));
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 225, 500));
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget {background-color: rgba(0,0,0,0);\n"
"color:white;}\n"
"QHeaderView::section {\n"
"background-color: #302E2B;\n"
"color: white}"));
        btnBack = new QPushButton(frame_2);
        btnBack->setObjectName("btnBack");
        btnBack->setGeometry(QRect(0, 520, 75, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Ubuntu")});
        btnBack->setFont(font2);
        btnBack->setStyleSheet(QString::fromUtf8("QPushButton{background-image: url(:/assets/back-button.png);}\n"
"QPushButton:hover{background-color: #FBC061}"));
        btnExit = new QPushButton(frame_2);
        btnExit->setObjectName("btnExit");
        btnExit->setGeometry(QRect(150, 520, 75, 41));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Ubuntu")});
        font3.setPointSize(12);
        btnExit->setFont(font3);
        btnForward = new QPushButton(frame_2);
        btnForward->setObjectName("btnForward");
        btnForward->setGeometry(QRect(75, 520, 75, 41));
        btnForward->setFont(font2);
        btnForward->setStyleSheet(QString::fromUtf8("QPushButton{background-image: url(:/assets/forward-button.png);}\n"
"\n"
"QPushButton:hover{background-color: #FBC061}"));

        retranslateUi(Match);

        QMetaObject::connectSlotsByName(Match);
    } // setupUi

    void retranslateUi(QWidget *Match)
    {
        Match->setWindowTitle(QCoreApplication::translate("Match", "Form", nullptr));
        lbOpponentName->setText(QCoreApplication::translate("Match", "Opponent", nullptr));
        lbPlayerName->setText(QCoreApplication::translate("Match", "You", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Match", "Turn", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Match", "White", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Match", "Black", nullptr));
        btnBack->setText(QString());
        btnExit->setText(QCoreApplication::translate("Match", "Exit", nullptr));
        btnForward->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Match: public Ui_Match {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATCH_H
