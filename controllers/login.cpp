#include "login.h"
#include "ui_login.h"
#include "serviceRequest.h"
#include "userrequest.h"

#include <QKeyEvent>
#include <QPushButton>
#include <Qt>
#include <QApplication>
#include <QPalette>
#include <QGraphicsItem>
#include <QUrl>
#include <QNetworkRequest>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    //initialiseGraphic
    QPalette pal = QPalette();
    pal.setColor(QPalette::WindowText, QColor("#FFFFFF"));

    ui->mainTitle->setAlignment(Qt::AlignCenter);
    ui->mainTitle->setPalette(pal);
    ui->desc->setAlignment(Qt::AlignCenter);
    ui->desc->setPalette(pal);

    QPixmap pic = QPixmap(":/logo/cloud.png");
    ui->logo->setScaledContents(true);
    ui->logo->setPixmap(pic);

    ui->errorMsg->setStyleSheet("QLabel { color : #cc0000; }");
    ui->errorMsg->setAlignment(Qt::AlignCenter);
    ui->errorMsg->setText("");

    connect(ui->emailInput, &LineEditCustom::returnPressed, this, &Login::clickBtnSignIn);
    connect(ui->passwordInput, &LineEditCustom::returnPressed, this, &Login::clickBtnSignIn);
    connect(ui->signBtn, SIGNAL(clicked()), this, SLOT(clickBtnSignIn()));
}

Login::~Login()
{
    delete ui;
}

void Login::clickBtnSignIn() {
    UserRequest *serviceUser = new UserRequest();

    connect(serviceUser, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(getDataConnexion(QNetworkReply*)));

    CredentailsTable cdt;
    cdt.addCredential("email", ui->emailInput->text());
    cdt.addCredential("password", ui->passwordInput->text());
    serviceUser->request(UserRequest::POST, UserRequest::Connection, cdt);
    //service->post(QNetworkRequest(QUrl("http://127.0.0.1:3000/api/user/login")), cdt);
}

void Login::getDataConnexion(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray asdf = reply->readAll();
        qDebug() << (QString("asdf %1").arg(asdf.length()));
        qDebug() << (QString(asdf));

        emit connexionSuccess();
    }
    else
    {
        ui->errorMsg->setText("Password or email invalid");
        qDebug("error request");
    }
    qDebug("replyFinished");
}
