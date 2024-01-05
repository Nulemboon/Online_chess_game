/********************************************************************************
** Form generated from reading UI file 'chesssquare.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHESSSQUARE_H
#define UI_CHESSSQUARE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ChessSquare
{
public:
    QFrame *frame;
    QLabel *lbPiece;

    void setupUi(QFrame *ChessSquare)
    {
        if (ChessSquare->objectName().isEmpty())
            ChessSquare->setObjectName("ChessSquare");
        ChessSquare->resize(70, 70);
        frame = new QFrame(ChessSquare);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 70, 70));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        lbPiece = new QLabel(frame);
        lbPiece->setObjectName("lbPiece");
        lbPiece->setGeometry(QRect(10, 10, 50, 50));

        retranslateUi(ChessSquare);

        QMetaObject::connectSlotsByName(ChessSquare);
    } // setupUi

    void retranslateUi(QFrame *ChessSquare)
    {
        ChessSquare->setWindowTitle(QCoreApplication::translate("ChessSquare", "Frame", nullptr));
        lbPiece->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChessSquare: public Ui_ChessSquare {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESSSQUARE_H
