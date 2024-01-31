/********************************************************************************
** Form generated from reading UI file 'play.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAY_H
#define UI_PLAY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_play
{
public:
    QFrame *playFrame;
    QTableWidget *playView;
    QLabel *label;
    QPushButton *btnBack;
    QPushButton *btnMM;
    QPushButton *btnInvite;
    QPushButton *btnRefresh;
    QLabel *lbNoMM;
    QFrame *frHome;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnPlay_2;
    QPushButton *btnHistory_2;
    QPushButton *btnOptions_2;
    QPushButton *btnQuit_2;
    QLabel *lbDim;
    QFrame *frInvite;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *lbNameInvite;
    QPushButton *btnYes;
    QPushButton *btnNo;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *play)
    {
        if (play->objectName().isEmpty())
            play->setObjectName("play");
        play->resize(1000, 750);
        playFrame = new QFrame(play);
        playFrame->setObjectName("playFrame");
        playFrame->setGeometry(QRect(125, 100, 750, 500));
        playFrame->setAutoFillBackground(false);
        playFrame->setStyleSheet(QString::fromUtf8("QFrame#playFrame {\n"
"background-color: rgb(46, 47, 48);\n"
"border: 8px solid orange; \n"
"}"));
        playFrame->setFrameShape(QFrame::StyledPanel);
        playFrame->setFrameShadow(QFrame::Raised);
        playView = new QTableWidget(playFrame);
        if (playView->columnCount() < 1)
            playView->setColumnCount(1);
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI Semibold")});
        font.setPointSize(16);
        font.setWeight(QFont::DemiBold);
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        font.setKerning(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        __qtablewidgetitem->setFont(font);
        __qtablewidgetitem->setBackground(QColor(78, 79, 80));
        playView->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (playView->rowCount() < 4)
            playView->setRowCount(4);
        QFont font1;
        font1.setPointSize(11);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font1);
        playView->setItem(0, 0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font1);
        playView->setItem(1, 0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font1);
        playView->setItem(2, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font1);
        playView->setItem(3, 0, __qtablewidgetitem4);
        playView->setObjectName("playView");
        playView->setGeometry(QRect(60, 100, 461, 300));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(playView->sizePolicy().hasHeightForWidth());
        playView->setSizePolicy(sizePolicy);
        playView->setBaseSize(QSize(0, 0));
        playView->setLayoutDirection(Qt::LeftToRight);
        playView->setAutoFillBackground(false);
        playView->setStyleSheet(QString::fromUtf8("QTableWidget { \n"
"background-color: #2e2f30;\n"
"gridline-color: white;\n"
"border: 2px solid #ffffff;\n"
"color: white\n"
"\n"
"}\n"
"QTableWidget::item {\n"
"  \n"
"}\n"
"QHeaderView::section {\n"
"gridline-color: white;\n"
"}\n"
""));
        playView->setFrameShape(QFrame::StyledPanel);
        playView->setFrameShadow(QFrame::Plain);
        playView->setLineWidth(2);
        playView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        playView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        playView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        playView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        playView->setSelectionMode(QAbstractItemView::NoSelection);
        playView->setIconSize(QSize(0, 0));
        playView->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        playView->setShowGrid(true);
        playView->setGridStyle(Qt::SolidLine);
        playView->setSortingEnabled(false);
        playView->setWordWrap(true);
        playView->setCornerButtonEnabled(true);
        playView->setRowCount(4);
        playView->setColumnCount(1);
        playView->horizontalHeader()->setStretchLastSection(true);
        playView->verticalHeader()->setVisible(false);
        playView->verticalHeader()->setCascadingSectionResizes(false);
        playView->verticalHeader()->setDefaultSectionSize(63);
        playView->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        playView->verticalHeader()->setStretchLastSection(true);
        label = new QLabel(playFrame);
        label->setObjectName("label");
        label->setGeometry(QRect(330, 10, 91, 80));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI Semibold")});
        font2.setPointSize(24);
        font2.setBold(true);
        label->setFont(font2);
        label->setStyleSheet(QString::fromUtf8("color: white\n"
""));
        btnBack = new QPushButton(playFrame);
        btnBack->setObjectName("btnBack");
        btnBack->setGeometry(QRect(350, 420, 51, 51));
        btnBack->setCursor(QCursor(Qt::PointingHandCursor));
        btnBack->setStyleSheet(QString::fromUtf8("QPushButton { \n"
"background-color: orange; border-radius: 25px; \n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/home/assets/arrow-left.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnBack->setIcon(icon);
        btnBack->setIconSize(QSize(30, 55));
        btnMM = new QPushButton(playFrame);
        btnMM->setObjectName("btnMM");
        btnMM->setGeometry(QRect(550, 330, 161, 71));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe UI")});
        font3.setPointSize(11);
        font3.setBold(true);
        btnMM->setFont(font3);
        btnMM->setCursor(QCursor(Qt::PointingHandCursor));
        btnMM->setStyleSheet(QString::fromUtf8("QPushButton { \n"
"background-color: #f59701;\n"
"border-radius: 25px; \n"
"color: white;\n"
"}"));
        btnMM->setIconSize(QSize(30, 55));
        btnInvite = new QPushButton(playFrame);
        btnInvite->setObjectName("btnInvite");
        btnInvite->setGeometry(QRect(550, 220, 161, 71));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Segoe UI")});
        font4.setPointSize(15);
        font4.setBold(true);
        btnInvite->setFont(font4);
        btnInvite->setCursor(QCursor(Qt::PointingHandCursor));
        btnInvite->setStyleSheet(QString::fromUtf8("QPushButton { \n"
"background-color: #f59701;\n"
"border-radius: 25px; \n"
"color: white;\n"
"}"));
        btnInvite->setIconSize(QSize(30, 55));
        btnRefresh = new QPushButton(playFrame);
        btnRefresh->setObjectName("btnRefresh");
        btnRefresh->setGeometry(QRect(550, 100, 161, 71));
        btnRefresh->setFont(font4);
        btnRefresh->setCursor(QCursor(Qt::PointingHandCursor));
        btnRefresh->setStyleSheet(QString::fromUtf8("QPushButton { \n"
"background-color: #f59701;\n"
"border-radius: 25px; \n"
"color: white;\n"
"}"));
        btnRefresh->setIconSize(QSize(30, 55));
        lbNoMM = new QLabel(playFrame);
        lbNoMM->setObjectName("lbNoMM");
        lbNoMM->setGeometry(QRect(572, 410, 116, 14));
        QFont font5;
        font5.setBold(true);
        lbNoMM->setFont(font5);
        lbNoMM->setStyleSheet(QString::fromUtf8("color:white;"));
        frHome = new QFrame(play);
        frHome->setObjectName("frHome");
        frHome->setGeometry(QRect(0, 0, 1000, 750));
        frHome->setMinimumSize(QSize(1000, 750));
        frHome->setMaximumSize(QSize(1000, 750));
        frHome->setStyleSheet(QString::fromUtf8("QFrame#frHome{background-image: url(:/home/assets/home.jpg)}\n"
"QPushButton {border: none; \n"
"text-align: left;\n"
"	font: 33pt \"Ubuntu\";\n"
"color: white;\n"
"\n"
"}"));
        frHome->setFrameShape(QFrame::StyledPanel);
        frHome->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget = new QWidget(frHome);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(70, 320, 201, 351));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnPlay_2 = new QPushButton(verticalLayoutWidget);
        btnPlay_2->setObjectName("btnPlay_2");
        btnPlay_2->setMinimumSize(QSize(0, 50));
        btnPlay_2->setStyleSheet(QString::fromUtf8("border: none"));

        verticalLayout_2->addWidget(btnPlay_2);

        btnHistory_2 = new QPushButton(verticalLayoutWidget);
        btnHistory_2->setObjectName("btnHistory_2");

        verticalLayout_2->addWidget(btnHistory_2);

        btnOptions_2 = new QPushButton(verticalLayoutWidget);
        btnOptions_2->setObjectName("btnOptions_2");

        verticalLayout_2->addWidget(btnOptions_2);

        btnQuit_2 = new QPushButton(verticalLayoutWidget);
        btnQuit_2->setObjectName("btnQuit_2");

        verticalLayout_2->addWidget(btnQuit_2);

        lbDim = new QLabel(frHome);
        lbDim->setObjectName("lbDim");
        lbDim->setGeometry(QRect(0, 0, 1000, 750));
        lbDim->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0.7)"));
        frInvite = new QFrame(frHome);
        frInvite->setObjectName("frInvite");
        frInvite->setGeometry(QRect(570, 630, 400, 70));
        frInvite->setStyleSheet(QString::fromUtf8("QFrame{background-color: #F4DCC5;}\n"
"\n"
"QPushButton{ border: none; color:black;background-color:#EF9A09;border-radius:10px; font-size: 18px;\n"
"text-align: center\n"
"}\n"
"\n"
"QPushButton:hover{background-color:#d98100}\n"
"\n"
"QLabel {border:none; color:black}"));
        frInvite->setFrameShape(QFrame::StyledPanel);
        frInvite->setFrameShadow(QFrame::Raised);
        layoutWidget = new QWidget(frInvite);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 0, 401, 71));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lbNameInvite = new QLabel(layoutWidget);
        lbNameInvite->setObjectName("lbNameInvite");
        lbNameInvite->setMinimumSize(QSize(100, 0));
        lbNameInvite->setBaseSize(QSize(100, 0));

        horizontalLayout->addWidget(lbNameInvite);

        btnYes = new QPushButton(layoutWidget);
        btnYes->setObjectName("btnYes");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnYes->sizePolicy().hasHeightForWidth());
        btnYes->setSizePolicy(sizePolicy1);
        btnYes->setMaximumSize(QSize(75, 21));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Ubuntu")});
        font6.setBold(false);
        font6.setItalic(false);
        btnYes->setFont(font6);

        horizontalLayout->addWidget(btnYes);

        btnNo = new QPushButton(layoutWidget);
        btnNo->setObjectName("btnNo");
        btnNo->setMaximumSize(QSize(75, 21));

        horizontalLayout->addWidget(btnNo);

        horizontalSpacer = new QSpacerItem(5, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        frHome->raise();
        playFrame->raise();

        retranslateUi(play);

        QMetaObject::connectSlotsByName(play);
    } // setupUi

    void retranslateUi(QWidget *play)
    {
        play->setWindowTitle(QCoreApplication::translate("play", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = playView->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("play", "Online Players", nullptr));

        const bool __sortingEnabled = playView->isSortingEnabled();
        playView->setSortingEnabled(false);
        playView->setSortingEnabled(__sortingEnabled);

        label->setText(QCoreApplication::translate("play", "PLAY", nullptr));
        btnBack->setText(QString());
        btnMM->setText(QCoreApplication::translate("play", "RANDOM\n"
"MATCHMAKING", nullptr));
        btnInvite->setText(QCoreApplication::translate("play", "INVITE", nullptr));
        btnRefresh->setText(QCoreApplication::translate("play", "REFRESH", nullptr));
        lbNoMM->setText(QCoreApplication::translate("play", "No match found!", nullptr));
        btnPlay_2->setText(QCoreApplication::translate("play", "Play", nullptr));
        btnHistory_2->setText(QCoreApplication::translate("play", "History", nullptr));
        btnOptions_2->setText(QCoreApplication::translate("play", "Options", nullptr));
        btnQuit_2->setText(QCoreApplication::translate("play", "Logout", nullptr));
        lbDim->setText(QString());
        lbNameInvite->setText(QCoreApplication::translate("play", "TextLabel", nullptr));
        btnYes->setText(QCoreApplication::translate("play", "Yes", nullptr));
        btnNo->setText(QCoreApplication::translate("play", "No", nullptr));
    } // retranslateUi

};

namespace Ui {
    class play: public Ui_play {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAY_H
