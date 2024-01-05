#include "home.h"
#include "ui_home.h"
#include "../message/message.h"

Home::Home(MainWindow *mainwindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Home), mainwindow(mainwindow)
{
    ui->setupUi(this);

    // Display the login screen
    ui->frLogin->setVisible(true);
    ui->lbDim->setVisible(true);
    ui->btnPlay->setEnabled(false);
    ui->btnHistory->setEnabled(false);
    ui->btnOptions->setEnabled(false);
    ui->btnQuit->setEnabled(false);

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

void Home::on_btnQuit_clicked()
{
    exit(0);
}


void Home::on_btnHistory_clicked()
{
    ui->lbDim->setVisible(true);
    ui->frLogin->setVisible(true);
    ui->btnPlay->setEnabled(false);
    ui->btnHistory->setEnabled(false);
    ui->btnOptions->setEnabled(false);
    ui->btnQuit->setEnabled(false);
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

    UserMessage* msg = new UserMessage(LOGIN, userName.toStdString(), passWord.toStdString());
    Message *rcv = mainwindow->sendMessage(mainwindow->connfd, msg);

    switch (rcv->type) {
    case LOGIN_SUCCESSFUL:
        mainwindow->user = username; // Set the username for this session
        // Remove the login layer
        ui->lbDim->setVisible(false);
        ui->frLogin->setVisible(false);
        ui->btnPlay->setEnabled(true);
        ui->btnHistory->setEnabled(true);
        ui->btnOptions->setEnabled(true);
        ui->btnQuit->setEnabled(true);
        break;

    case LOGIN_FAIL:
        ui->lbNoti->setText("Wrong username or password. Try again.")
    }
}

// REGISTER_USERNAME_EXISTED,
//     REGISTER_PASSWORD_FAIL,
//     REGISTER_SUCCESSFUL,
//     LOGIN_FAIL,
//     USER_BLOCKED,
//     USER_LOGGED_IN,
//     LOGIN_SUCCESSFUL,
void Home::on_btnRegister_clicked()
{
    // Get credentials from QLineEdit
    QString userName = ui->txtUsername->text();
    QString passWord = ui->txtPassword->text();

    UserMessage* msg = new UserMessage(REGISTER, userName.toStdString(), passWord.toStdString());
    mainwindow->sendMessage(mainwindow->connfd, msg);
}

