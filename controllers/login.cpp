#include "login.h"
#include "ui_login.h"
#include "serviceRequest.h"
#include "image.h"

#include <QKeyEvent>
#include <QPushButton>
#include <Qt>
#include <QApplication>
#include <QPalette>
#include <QGraphicsItem>
#include <QUrl>
#include <QNetworkRequest>
#include "globalinfo.h"
#include "httperror.h"
#include <QSvgRenderer>
#include <QPainter>

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

    ui->signBtn->setStyleSheet("background-color:#" + Color::GlobalInfo::lightBlue + ";border: none; margin-left:20px; margin-right:20px; color: black; text-decoration: none;");
    QPixmap pic = Image::fromSvgToPixmap(QSize(70, 40), ":/logo/cloudLogo");
    //ui->logo->setScaledContents(true);

    int w = ui->logo->width();
    int h = ui->logo->height();
    ui->logo->setPixmap(pic.scaled(w,h,Qt::KeepAspectRatio));

    ui->errorMsg->setStyleSheet("QLabel { color : #cc0000; }");
    ui->errorMsg->setAlignment(Qt::AlignCenter);
    ui->errorMsg->setText("");

    _userRequest = new UserRequest();
    connect(_userRequest, &UserRequest::signalConnected, this, &Login::getDataConnexion);
   // connect(ui->emailInput, &LineEditCustom::returnPressed, this, &Login::clickBtnSignIn);
   // connect(ui->passwordInput, &LineEditCustom::returnPressed, this, &Login::clickBtnSignIn);
    connect(ui->signBtn, &QPushButton::clicked, this, &Login::clickBtnSignIn);
}

Login::~Login()
{
    delete ui;
}

void Login::clickBtnSignIn() {
    RouteParams prms;
    prms.addValueToBody("email", ui->emailInput->text());
    prms.addValueToBody("password", ui->passwordInput->text());
    _userRequest->request(UserRequest::POST, UserRequest::Connection, prms);
}

void Login::getDataConnexion(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
        emit connexionSuccess();
    else if (reply->error() == QNetworkReply::AuthenticationRequiredError)
        ui->errorMsg->setText(reply->readAll());
    else
      throw HttpError(reply);
}
