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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_history
{
public:
    QFrame *historyFrame;
    QTableWidget *historyView;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QWidget *history)
    {
        if (history->objectName().isEmpty())
            history->setObjectName("history");
        history->setEnabled(true);
        history->resize(1000, 750);
        history->setWindowOpacity(1.000000000000000);
        history->setAutoFillBackground(false);
        history->setStyleSheet(QString::fromUtf8("QWidget#history {\n"
"\n"
"	background-image: url(:/home/assets/home.jpg);\n"
"}"));
        historyFrame = new QFrame(history);
        historyFrame->setObjectName("historyFrame");
        historyFrame->setGeometry(QRect(125, 125, 750, 500));
        historyFrame->setAutoFillBackground(false);
        historyFrame->setStyleSheet(QString::fromUtf8("QFrame#historyFrame {\n"
"	background-color: rgb(46, 47, 48);\n"
" border: 10px solid orange; \n"
"}"));
        historyFrame->setFrameShape(QFrame::StyledPanel);
        historyFrame->setFrameShadow(QFrame::Raised);
        historyView = new QTableWidget(historyFrame);
        if (historyView->columnCount() < 3)
            historyView->setColumnCount(3);
        QFont font;
        font.setPointSize(15);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        historyView->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        historyView->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        historyView->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (historyView->rowCount() < 4)
            historyView->setRowCount(4);
        historyView->setObjectName("historyView");
        historyView->setGeometry(QRect(55, 100, 641, 301));
        historyView->setLayoutDirection(Qt::LeftToRight);
        historyView->setAutoFillBackground(false);
        historyView->setStyleSheet(QString::fromUtf8("QTableWidget { \n"
"background-color: #2e2f30;\n"
"gridline-color: white\n"
"}"));
        historyView->setFrameShape(QFrame::Panel);
        historyView->setFrameShadow(QFrame::Plain);
        historyView->setLineWidth(2);
        historyView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        historyView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        historyView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        historyView->setAutoScrollMargin(16);
        historyView->setIconSize(QSize(0, 0));
        historyView->setShowGrid(true);
        historyView->setWordWrap(true);
        historyView->setRowCount(4);
        historyView->setColumnCount(3);
        historyView->horizontalHeader()->setVisible(true);
        historyView->horizontalHeader()->setMinimumSectionSize(100);
        historyView->horizontalHeader()->setDefaultSectionSize(100);
        historyView->horizontalHeader()->setHighlightSections(true);
        historyView->horizontalHeader()->setStretchLastSection(true);
        historyView->verticalHeader()->setVisible(false);
        historyView->verticalHeader()->setDefaultSectionSize(64);
        historyView->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        historyView->verticalHeader()->setStretchLastSection(true);
        label = new QLabel(historyFrame);
        label->setObjectName("label");
        label->setGeometry(QRect(290, 10, 175, 80));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(33);
        label->setFont(font1);
        pushButton = new QPushButton(historyFrame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(350, 420, 51, 51));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton { \n"
"background-color: orange; border-radius: 25px; \n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/home/assets/arrow-left.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(30, 55));

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
        label->setText(QCoreApplication::translate("history", "History", nullptr));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class history: public Ui_history {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORY_H
