/********************************************************************************
** Form generated from reading UI file 'history.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORY_H
#define UI_HISTORY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_history
{
public:
    QFrame *historyFrame;
    QTableWidget *historyView;
    QLabel *label;
    QPushButton *btnBack;
    QFrame *frHome;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnPlay_2;
    QPushButton *btnHistory_2;
    QPushButton *btnOptions_2;
    QPushButton *btnQuit_2;
    QLabel *lbDim;

    void setupUi(QWidget *history)
    {
        if (history->objectName().isEmpty())
            history->setObjectName("history");
        history->setWindowModality(Qt::NonModal);
        history->setEnabled(true);
        history->resize(1000, 750);
        history->setContextMenuPolicy(Qt::DefaultContextMenu);
        history->setAutoFillBackground(false);
        history->setStyleSheet(QString::fromUtf8(""));
        historyFrame = new QFrame(history);
        historyFrame->setObjectName("historyFrame");
        historyFrame->setGeometry(QRect(125, 125, 750, 500));
        historyFrame->setAutoFillBackground(false);
        historyFrame->setStyleSheet(QString::fromUtf8("QFrame#historyFrame {\n"
"	background-color: rgb(46, 47, 48);\n"
" border: 8px solid orange; \n"
"}"));
        historyFrame->setFrameShape(QFrame::StyledPanel);
        historyFrame->setFrameShadow(QFrame::Raised);
        historyView = new QTableWidget(historyFrame);
        if (historyView->columnCount() < 3)
            historyView->setColumnCount(3);
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI Semibold")});
        font.setPointSize(16);
        font.setBold(false);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        __qtablewidgetitem->setBackground(QColor(78, 79, 80));
        historyView->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI Semibold")});
        font1.setPointSize(16);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font1);
        __qtablewidgetitem1->setBackground(QColor(78, 79, 80));
        historyView->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font1);
        __qtablewidgetitem2->setBackground(QColor(78, 79, 80));
        historyView->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (historyView->rowCount() < 4)
            historyView->setRowCount(4);
        QFont font2;
        font2.setPointSize(11);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font2);
        historyView->setItem(0, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font2);
        historyView->setItem(0, 1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font2);
        historyView->setItem(0, 2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font2);
        historyView->setItem(1, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font2);
        historyView->setItem(1, 1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font2);
        historyView->setItem(1, 2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font2);
        historyView->setItem(2, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font2);
        historyView->setItem(2, 1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFont(font2);
        historyView->setItem(2, 2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setFont(font2);
        historyView->setItem(3, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setFont(font2);
        historyView->setItem(3, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setFont(font2);
        historyView->setItem(3, 2, __qtablewidgetitem14);
        historyView->setObjectName("historyView");
        historyView->setGeometry(QRect(60, 100, 630, 300));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(historyView->sizePolicy().hasHeightForWidth());
        historyView->setSizePolicy(sizePolicy);
        historyView->setBaseSize(QSize(0, 0));
        historyView->setLayoutDirection(Qt::LeftToRight);
        historyView->setAutoFillBackground(false);
        historyView->setStyleSheet(QString::fromUtf8("QTableWidget { \n"
"background-color: #2e2f30;\n"
"gridline-color: #AB6C00;\n"
"border: 2px solid #AB6C00;\n"
"color: white\n"
"\n"
"}\n"
"QTableWidget::item {\n"
"  \n"
"}\n"
"QHeaderView::section {\n"
"gridline-color: white;\n"
"}\n"
"QHeaderView::section:horizontal {\n"
"    color:white;\n"
"}\n"
"QTableWidget::item:selected {\n"
"    background-color: #F4DCC5; \n"
"    color: black; \n"
"}\n"
"\n"
"QTableWidget::item:focus {\n"
"    background-color: #F4DCC5;  \n"
"    color: black; \n"
"}\n"
"QTableWidget::item:selected:focus {\n"
"    background-color: #F4DCC5;  \n"
"    color: black; \n"
"}\n"
""));
        historyView->setFrameShape(QFrame::StyledPanel);
        historyView->setFrameShadow(QFrame::Plain);
        historyView->setLineWidth(2);
        historyView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        historyView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        historyView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        historyView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        historyView->setAlternatingRowColors(false);
        historyView->setSelectionMode(QAbstractItemView::NoSelection);
        historyView->setIconSize(QSize(0, 0));
        historyView->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        historyView->setShowGrid(true);
        historyView->setGridStyle(Qt::SolidLine);
        historyView->setWordWrap(true);
        historyView->setCornerButtonEnabled(true);
        historyView->setRowCount(4);
        historyView->setColumnCount(3);
        historyView->horizontalHeader()->setVisible(true);
        historyView->horizontalHeader()->setCascadingSectionResizes(false);
        historyView->horizontalHeader()->setMinimumSectionSize(40);
        historyView->horizontalHeader()->setDefaultSectionSize(206);
        historyView->horizontalHeader()->setHighlightSections(false);
        historyView->horizontalHeader()->setStretchLastSection(true);
        historyView->verticalHeader()->setVisible(false);
        historyView->verticalHeader()->setCascadingSectionResizes(false);
        historyView->verticalHeader()->setDefaultSectionSize(63);
        historyView->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        historyView->verticalHeader()->setStretchLastSection(true);
        label = new QLabel(historyFrame);
        label->setObjectName("label");
        label->setGeometry(QRect(300, 10, 161, 80));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe UI Semibold")});
        font3.setPointSize(24);
        font3.setBold(true);
        label->setFont(font3);
        label->setStyleSheet(QString::fromUtf8("color: white\n"
""));
        btnBack = new QPushButton(historyFrame);
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
        frHome = new QFrame(history);
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
        frHome->raise();
        historyFrame->raise();

        retranslateUi(history);

        QMetaObject::connectSlotsByName(history);
    } // setupUi

    void retranslateUi(QWidget *history)
    {
        history->setWindowTitle(QCoreApplication::translate("history", "windowForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = historyView->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("history", "Opponent", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = historyView->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("history", "Result", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = historyView->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("history", "Played on", nullptr));

        const bool __sortingEnabled = historyView->isSortingEnabled();
        historyView->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem3 = historyView->item(0, 0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("history", "Khoa", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = historyView->item(0, 1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("history", "Lose", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = historyView->item(0, 2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("history", "Thursday", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = historyView->item(1, 0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("history", "Tue", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = historyView->item(1, 1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("history", "Win", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = historyView->item(1, 2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("history", "Friday", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = historyView->item(2, 0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("history", "Quan", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = historyView->item(2, 1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("history", "Lose", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = historyView->item(2, 2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("history", "Sunday", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = historyView->item(3, 0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("history", "Chien", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = historyView->item(3, 1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("history", "Win", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = historyView->item(3, 2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("history", "Monday", nullptr));
        historyView->setSortingEnabled(__sortingEnabled);

        label->setText(QCoreApplication::translate("history", "HISTORY", nullptr));
        btnBack->setText(QString());
        btnPlay_2->setText(QCoreApplication::translate("history", "Play", nullptr));
        btnHistory_2->setText(QCoreApplication::translate("history", "History", nullptr));
        btnOptions_2->setText(QCoreApplication::translate("history", "Options", nullptr));
        btnQuit_2->setText(QCoreApplication::translate("history", "Quit", nullptr));
        lbDim->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class history: public Ui_history {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORY_H
