#include "headers/subscribepopup.h"
#include "globalinfo.h"
#include "factoryfont.h"
#include "routeparams.h"
#include "httperror.h"

#include <QFileDialog>
#include <QToolButton>
#include <QPushButton>
#include <QStandardPaths>
#include <QNetworkReply>
#include <QCryptographicHash>

SubscribePopup::SubscribePopup(QWidget *parent) : QDialog(parent)
{
    this->setStyleSheet("background-color:#" + Color::GlobalInfo::backgroundLoginView + ";");

    _userRequest = new UserRequest();

    QVBoxLayout *vLayout = new QVBoxLayout();
    QHBoxLayout *hLayout = new QHBoxLayout();
    QHBoxLayout *hLayoutPersonalInformation = new QHBoxLayout();
    QHBoxLayout *hLayoutPicture = new QHBoxLayout();
    _subscribe = new QPushButton("Subscribe");

    _btnUploadProfilPicture = new QPushButton();
    _btnUploadProfilPicture->setIcon(QIcon(":/logo/picture"));
    _btnUploadProfilPicture->setIconSize(QSize(16, 16));
    _btnUploadProfilPicture->setFixedSize(25, 25);
    _btnUploadProfilPicture->setStyleSheet("background-color:#" + Color::GlobalInfo::lightBlue + "; border: none; color: black; text-decoration: none;");

    connect(_subscribe, &QPushButton::clicked, this, &SubscribePopup::subscribe);
    connect(_userRequest, &UserRequest::signalSubscribe, this, &SubscribePopup::slotSubscribe);
    connect(this, &SubscribePopup::finished, this, &SubscribePopup::reInitialiseForm);

    _email = new LineEditCustom();
    _password1 = new LineEditCustom();
    _password2 = new LineEditCustom();
    _picture = new QLabelCustom();
    _errorLabel = new QLabel();
    _firstName = new LineEditCustom();
    _lastName = new LineEditCustom();

    _firstName->setPlaceholderText("First Name");
    _lastName->setPlaceholderText("Last Name");
    _email->setPlaceholderText("Email");
    _password1->setPlaceholderText("Password");
    _password2->setPlaceholderText("Password");

    _firstName->setContentsMargins(13, 0, 0, 0);
    _lastName->setContentsMargins(0, 0, 13, 0);
    _password1->setContentsMargins(13, 0, 0, 0);
    _password2->setContentsMargins(0, 0, 13, 0);
    _picture->setContentsMargins(13, 0, 0, 0);
    hLayoutPicture->setContentsMargins(13, 0, 13, 0);

    _titleLabel = new QLabel("Create your account");
    _titleLabel->setContentsMargins(0, 10, 0, 20);
    _titleLabel->setFocusPolicy(Qt::StrongFocus);
    _titleLabel->setAlignment(Qt::AlignCenter);

    _titleLabel->setFont(FactoryFont(Font::GlobalInfo::name).size(16).letterSpacing(105).styleName("Normal").weight(450).gen());
    _subscribe->setFont(FactoryFont(Font::GlobalInfo::name).size(14).letterSpacing(105).styleName("Normal").weight(450).gen());

    _titleLabel->setStyleSheet("color:#FFFFFF;");
    _errorLabel->setStyleSheet("color:#FF0000");

    _subscribe->setStyleSheet("background-color:#" + Color::GlobalInfo::lightBlue + ";border: none; margin-left:13px; margin-right:13px; color: black; text-decoration: none;");
    _subscribe->setMinimumHeight(40);

    hLayout->addWidget(_password1);
    hLayout->addWidget(_password2);

    hLayoutPersonalInformation->addWidget(_firstName);
    hLayoutPersonalInformation->addWidget(_lastName);

    connect(_btnUploadProfilPicture, &QPushButton::clicked, this, &SubscribePopup::addPicture);

    hLayoutPicture->addWidget(_picture);
    hLayoutPicture->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));
    hLayoutPicture->addWidget(_btnUploadProfilPicture);

    vLayout->addWidget(_titleLabel);
    vLayout->addLayout(hLayoutPersonalInformation);
    vLayout->addWidget(_email);
    vLayout->addLayout(hLayout);
    vLayout->addLayout(hLayoutPicture);
    vLayout->addWidget(_errorLabel);
    vLayout->addWidget(_subscribe);
    vLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    setLayout(vLayout);
}

void SubscribePopup::addPicture() {
    QString fileName = QFileDialog::getOpenFileName(0,
        "Open Image", "/", "Image Files (*.png *.jpg *.jpeg)");

    if (fileName.length() > 0) {
        _pathProfilPicture = fileName;
        QPixmap pixmap = QPixmap(fileName);
        _picture->createBtnImg(pixmap, 80, 80);
    }

}

void SubscribePopup::subscribe() {
    if (_password1->text() != _password2->text()) {
        _errorLabel->setText("Password incorrect");
        return;
    }

    _errorLabel->setText("");

    RouteParams prms;
    QFileInfo fileInfo(_pathProfilPicture);

    _nameProfilPicture = _email->text() + "_" + fileInfo.fileName();
    prms.addValueToBody("email", _email->text());
    prms.addValueToBody("password", _password1->text());
    prms.addValueToBody("firstName", _firstName->text());
    prms.addValueToBody("lastName", _lastName->text());
    if (_pathProfilPicture.length() > 0)
        prms.addValueToBody("pathProfilPicture", _nameProfilPicture);
    _userRequest->request(UserRequest::POST, UserRequest::Subscribe, prms);
}

void SubscribePopup::reInitialiseForm() {
    this->setMinimumSize(0, 0);
    _email->show();
    _password1->show();
    _password2->show();
    _picture->show();
    _errorLabel->show();
    _firstName->show();
    _lastName->show();
    _picture->show();
    _subscribe->show();
    _btnUploadProfilPicture->show();

    _email->setText("");
    _password1->setText("");
    _password2->setText("");
    _picture->setPixmap(QPixmap());
    _errorLabel->setText("");
    _firstName->setText("");
    _lastName->setText("");
    _picture->show();
}

void SubscribePopup::slotSubscribe(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

    this->setFixedSize(300, 80);
    _email->hide();
    _password1->hide();
    _password2->hide();
    _picture->hide();
    _errorLabel->hide();
    _firstName->hide();
    _lastName->hide();
    _picture->hide();
    _subscribe->hide();
    _btnUploadProfilPicture->hide();
    _titleLabel->setText("ACCOUNT CREATED");

    if (_pathProfilPicture.length() <= 0)
        return;
    QFile file(_pathProfilPicture);

    if (!file.open(QIODevice::ReadOnly))
        qDebug("[ERREUR] : Open file fail");

    QByteArray bArray = "\r\n-------------------------------7d935033608e2\r\n";
    bArray += "Content-Disposition: form-data; name=\"empty\"; filename=\"" + _nameProfilPicture.toLocal8Bit() + "\"\r\n";
    bArray += "Content-Type: application/octet-stream\r\n\r\n";
    bArray += file.readAll();
    bArray += "\r\n-------------------------------7d935033608e2--\r\n";

    _userRequest->requestFile(UserRequest::POST, UserRequest::ProfilPicture, bArray, "-----------------------------7d935033608e2");
}
