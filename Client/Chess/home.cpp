#include "home.h"
#include "ui_home.h"
#include "../message/message.h"
#include "history.h"

Home::Home(MainWindow *mainwindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Home), mainwindow(mainwindow)
{
    ui->setupUi(this);

    // Display the login screen
    ui->frLogin->setVisible(true);
    ui->lbDim->setVisible(true);
    ui->btnRegister->setVisible(false);
    ui->btnToLogin->setVisible(false);
    ui->btnQuit->setVisible(false);
    ui->btnPlay->setEnabled(false);
    ui->btnHistory->setEnabled(false);
    ui->btnOptions->setEnabled(false);
    ui->btnLogout->setEnabled(false);

    ui->txtPassword->setEchoMode(QLineEdit::Password);


    // Set placeholder text for the credentials text
    connect(ui->txtUsername, &QLineEdit::textChanged, this, &Home::onUsernameTextChanged);
    connect(ui->txtPassword, &QLineEdit::textChanged, this, &Home::onPasswordTextChanged);

    // Load the image from the resource file
    QPixmap logoPixmap(":/home/assets/logo.png");

    // Set the scaled contents property on the QPixmap
    logoPixmap = logoPixmap.scaled(ui->lbLogo->size(), Qt::KeepAspectRatio);

    // Set the pixmap to the QLabel
    ui->lbLogo->setPixmap(logoPixmap);

}

Home::~Home()
{
    delete ui;
}

void Home::on_btnHistory_clicked()
{
    // Setup History scene
    mainwindow->switchScene(HISTORYS);
    history* screen = qobject_cast<history*>(mainwindow->stackedWidget->currentWidget());
    screen->getHistoryData();

}

void Home::onUsernameTextChanged(const QString &text)
{
    if (!text.isEmpty()) {
        ui->lbUsername->setVisible(false);
    } else {
        ui->lbUsername->setVisible(true);
    }
}

void Home::onPasswordTextChanged(const QString &text)
{
    if (!text.isEmpty()) {
        ui->lbPassword->setVisible(false);
    } else {
        ui->lbPassword->setVisible(true);
    }
}


void Home::on_btnLogin_clicked()
{
    // Get credentials from QLineEdit
    QString userName = ui->txtUsername->text();
    QString passWord = ui->txtPassword->text();

    if (userName == "" || passWord == "") {
        ui->lbNoti->setText("Enter your account information.");
        return;
    }

    UserMessage* msg = new UserMessage(LOGIN, userName.toStdString(), passWord.toStdString());
    mainwindow->sendMessage(msg);
}

void Home::on_btnRegister_clicked()
{
    // Get credentials from QLineEdit
    QString userName = ui->txtUsername->text();
    QString passWord = ui->txtPassword->text();

    if (userName == "" || passWord == "") {
        ui->lbNoti->setText("Enter your account information.");
        return;
    }

    // Prepare and send message to server
    UserMessage* msg = new UserMessage(REGISTER, userName.toStdString(), passWord.toStdString());
    mainwindow->sendMessage(msg);
}

void Home::on_btnLogout_clicked()
{
    Message* msg = new Message(LOGOUT);
    mainwindow->sendMessage(msg);

    ui->lbDim->setVisible(true);
    ui->frLogin->setVisible(true);
    mainwindow->user = NULL;
}


void Home::on_btnToRegister_clicked()
{
    ui->btnLogin->setVisible(false);
    ui->btnToRegister->setVisible(false);
    ui->label_2->setText("Already have an account?");
    ui->btnRegister->setVisible(true);
    ui->btnToLogin->setVisible(true);
    ui->lbNoti->setText("");
}



void Home::on_btnQuit_clicked()
{

}


void Home::on_btnToLogin_clicked()
{
    ui->btnLogin->setVisible(true);
    ui->btnToRegister->setVisible(true);
    ui->label_2->setText("New? Sign up right now!");
    ui->btnRegister->setVisible(false);
    ui->btnToLogin->setVisible(false);
    ui->lbNoti->setText("");
}


void Home::on_btnPlay_clicked()
{
    mainwindow->switchScene(PLAYS);
    play* screen = qobject_cast<play*>(mainwindow->stackedWidget->currentWidget());
    screen->getPlayData();
}

