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
#include "lineEditCustom.h"

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

    ui->signBtn->setStyleSheet("background-color:#" + Color::GlobalInfo::lightBlue + ";border: none; margin-left:13px; margin-right:13px; color: black; text-decoration: none;");

    _subscribePopPup = new SubscribePopup(this);
    connect(this->ui->createAccountBtn, &QPushButton::clicked, _subscribePopPup, &SubscribePopup::show);

    /* CONFIGURATION LOGO */

    QPixmap pic = Image::fromSvgToPixmap(QSize(70, 40), ":/logo/cloudLogo");

    int w = ui->logo->width();
    int h = ui->logo->height();
    ui->logo->setPixmap(pic.scaled(w,h,Qt::KeepAspectRatio));
    ui->logo->setFocusPolicy(Qt::StrongFocus);

    /* CONFIGURATION ERROR MESSAGE */

    ui->errorMsg->setStyleSheet("QLabel { color : #cc0000; }");
    ui->errorMsg->setAlignment(Qt::AlignCenter);
    ui->errorMsg->setText("");

    /* CONFIGURATION INPUT */

   // int pos = ui->widgetConnectionLayout->indexOf(ui->emailInput); // a supprimer
   // ui->emailInput->hide();

//    //delete item;
//    ui->widgetConnectionLayout->insertWidget(pos, new LineEditCustom(this));

//    ui->emailInput->setStyleSheet(StyleSheet::GlobalInfo::input);

//    ui->emailInput->setMinimumHeight(35);
//    ui->emailInput->setFocusPolicy(Qt::StrongFocus);
//    ui->emailInput->setAttribute(Qt::WA_MacShowFocusRect, 0);
//    ui->passwordInput->setStyleSheet(StyleSheet::GlobalInfo::input);
//    ui->passwordInput->setMinimumHeight(35);
//    ui->passwordInput->setFocusPolicy(Qt::StrongFocus);
//    ui->passwordInput->setAttribute(Qt::WA_MacShowFocusRect, 0);
//    ui->signBtn->setFocusPolicy(Qt::StrongFocus);
//    ui->signBtn->setAttribute(Qt::WA_MacShowFocusRect, 0);

    _userRequest = new UserRequest();

    connect(_userRequest, &UserRequest::signalConnected, this, &Login::getDataConnexion);
    connect(ui->signBtn, &QPushButton::clicked, this, &Login::clickBtnSignIn);
}

Login::~Login()
{
    delete ui;
}

void Login::clearForm() {
    ui->emailInput->setText("");
    ui->passwordInput->setText("");
}

void Login::clickBtnSignIn() {
    RouteParams prms;
    prms.addValueToBody("email", ui->emailInput->text());
    prms.addValueToBody("password", ui->passwordInput->text());
    _userRequest->request(UserRequest::POST, UserRequest::Connection, prms);
}

void Login::getDataConnexion(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        ui->errorMsg->setText("");
        emit connexionSuccess(reply);
    }
    else if (reply->error() == QNetworkReply::AuthenticationRequiredError)
        ui->errorMsg->setText(reply->readAll());
    else {
        if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 0)
            ui->errorMsg->setText("MyCloud server down");
      throw HttpError(reply);
    }
}
