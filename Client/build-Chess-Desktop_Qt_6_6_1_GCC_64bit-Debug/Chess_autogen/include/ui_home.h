/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Home
{
public:
    QFrame *frHome;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnPlay;
    QPushButton *btnHistory;
    QPushButton *btnOptions;
    QPushButton *btnQuit;
    QFrame *frLogin;
    QPushButton *btnRegister;
    QLineEdit *txtUsername;
    QLineEdit *txtPassword;
    QLabel *lbUsername;
    QPushButton *btnLogin;
    QLabel *label_2;
    QLabel *lbLogo;
    QLabel *lbPassword;
    QLabel *lbDim;

    void setupUi(QWidget *Home)
    {
        if (Home->objectName().isEmpty())
            Home->setObjectName("Home");
        Home->resize(1000, 750);
        Home->setMinimumSize(QSize(1000, 750));
        Home->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {border: none; \n"
"text-align: left;\n"
"	font: 33pt \"Ubuntu\";\n"
"color: white;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"color: orange\n"
"}"));
        frHome = new QFrame(Home);
        frHome->setObjectName("frHome");
        frHome->setGeometry(QRect(0, 0, 1000, 750));
        frHome->setMinimumSize(QSize(1000, 750));
        frHome->setMaximumSize(QSize(1000, 750));
        frHome->setStyleSheet(QString::fromUtf8("QFrame#frHome{background-image: url(:/home/assets/home.jpg)}\n"
""));
        frHome->setFrameShape(QFrame::StyledPanel);
        frHome->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget = new QWidget(frHome);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(70, 320, 201, 351));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btnPlay = new QPushButton(verticalLayoutWidget);
        btnPlay->setObjectName("btnPlay");
        btnPlay->setMinimumSize(QSize(0, 50));
        btnPlay->setStyleSheet(QString::fromUtf8("border: none"));

        verticalLayout->addWidget(btnPlay);

        btnHistory = new QPushButton(verticalLayoutWidget);
        btnHistory->setObjectName("btnHistory");

        verticalLayout->addWidget(btnHistory);

        btnOptions = new QPushButton(verticalLayoutWidget);
        btnOptions->setObjectName("btnOptions");

        verticalLayout->addWidget(btnOptions);

        btnQuit = new QPushButton(verticalLayoutWidget);
        btnQuit->setObjectName("btnQuit");

        verticalLayout->addWidget(btnQuit);

        frLogin = new QFrame(frHome);
        frLogin->setObjectName("frLogin");
        frLogin->setGeometry(QRect(250, 125, 500, 500));
        frLogin->setMinimumSize(QSize(500, 500));
        frLogin->setStyleSheet(QString::fromUtf8("QFrame {background-color: #302E2B;\n"
"border: 10px solid #FFB12C;}\n"
"\n"
"QPushButton:hover {\n"
"text-decoration: none;\n"
"}"));
        frLogin->setFrameShape(QFrame::StyledPanel);
        frLogin->setFrameShadow(QFrame::Raised);
        btnRegister = new QPushButton(frLogin);
        btnRegister->setObjectName("btnRegister");
        btnRegister->setGeometry(QRect(292, 369, 163, 43));
        QFont font;
        font.setFamilies({QString::fromUtf8("Ubuntu")});
        font.setBold(true);
        font.setItalic(false);
        btnRegister->setFont(font);
        btnRegister->setStyleSheet(QString::fromUtf8("QPushButton{background-color: #EE4612;\n"
"text-align: center;\n"
"font-size: 16px;\n"
"font-weight: bold;}\n"
"\n"
"\n"
"QPushButton:hover{background-color: rgba(238, 70, 18, 0.7);color:white}"));
        txtUsername = new QLineEdit(frLogin);
        txtUsername->setObjectName("txtUsername");
        txtUsername->setGeometry(QRect(46, 155, 409, 46));
        QFont font1;
        font1.setPointSize(16);
        txtUsername->setFont(font1);
        txtUsername->setStyleSheet(QString::fromUtf8("border: none;\n"
"background-color: rgba(255,255,255,0.5);\n"
"color: black;s"));
        txtPassword = new QLineEdit(frLogin);
        txtPassword->setObjectName("txtPassword");
        txtPassword->setGeometry(QRect(46, 220, 409, 46));
        txtPassword->setFont(font1);
        txtPassword->setStyleSheet(QString::fromUtf8("border: none;\n"
"background-color: rgba(255,255,255,0.5);\n"
"color: black;"));
        lbUsername = new QLabel(frLogin);
        lbUsername->setObjectName("lbUsername");
        lbUsername->setGeometry(QRect(52, 155, 409, 46));
        lbUsername->setFont(font1);
        lbUsername->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"border:none;\n"
"color: black"));
        btnLogin = new QPushButton(frLogin);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setGeometry(QRect(46, 286, 409, 54));
        btnLogin->setStyleSheet(QString::fromUtf8("QPushButton{background-color: #F59701;\n"
"text-align: center;\n"
"font-size: 22px;\n"
"font-weight: bold;}\n"
"QPushButton:hover{background-color: rgba(238, 70, 18, 0.7); color:white}"));
        label_2 = new QLabel(frLogin);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(46, 377, 191, 34));
        QFont font2;
        font2.setPointSize(11);
        label_2->setFont(font2);
        label_2->setStyleSheet(QString::fromUtf8("border: none; color: white;"));
        lbLogo = new QLabel(frLogin);
        lbLogo->setObjectName("lbLogo");
        lbLogo->setGeometry(QRect(138, 18, 224, 108));
        lbLogo->setStyleSheet(QString::fromUtf8("border: none;"));
        lbPassword = new QLabel(frLogin);
        lbPassword->setObjectName("lbPassword");
        lbPassword->setGeometry(QRect(52, 220, 409, 46));
        lbPassword->setFont(font1);
        lbPassword->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"border:none;\n"
"color: black"));
        lbUsername->raise();
        lbPassword->raise();
        btnLogin->raise();
        label_2->raise();
        btnRegister->raise();
        lbLogo->raise();
        txtPassword->raise();
        txtUsername->raise();
        lbDim = new QLabel(frHome);
        lbDim->setObjectName("lbDim");
        lbDim->setGeometry(QRect(0, 0, 1000, 750));
        lbDim->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0.7)"));
        verticalLayoutWidget->raise();
        lbDim->raise();
        frLogin->raise();

        retranslateUi(Home);

        QMetaObject::connectSlotsByName(Home);
    } // setupUi

    void retranslateUi(QWidget *Home)
    {
        Home->setWindowTitle(QCoreApplication::translate("Home", "Form", nullptr));
        btnPlay->setText(QCoreApplication::translate("Home", "Play", nullptr));
        btnHistory->setText(QCoreApplication::translate("Home", "History", nullptr));
        btnOptions->setText(QCoreApplication::translate("Home", "Options", nullptr));
        btnQuit->setText(QCoreApplication::translate("Home", "Quit", nullptr));
        btnRegister->setText(QCoreApplication::translate("Home", "Register", nullptr));
        txtUsername->setText(QString());
        txtPassword->setText(QString());
        lbUsername->setText(QCoreApplication::translate("Home", "Username...", nullptr));
        btnLogin->setText(QCoreApplication::translate("Home", "Login", nullptr));
        label_2->setText(QCoreApplication::translate("Home", "New? Sign up right now!", nullptr));
        lbLogo->setText(QString());
        lbPassword->setText(QCoreApplication::translate("Home", "Password...", nullptr));
        lbDim->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Home: public Ui_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
