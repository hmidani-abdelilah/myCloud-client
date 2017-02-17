#ifndef SUBSCRIBEPOPUP_H
#define SUBSCRIBEPOPUP_H

#include "lineEditCustom.h"
#include "qlabelcustom.h"
#include "userrequest.h"

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>

class SubscribePopup : public QDialog
{
public:
    SubscribePopup(QWidget *parent = 0);

private:
    LineEditCustom      *_email;
    LineEditCustom      *_password1;
    LineEditCustom      *_password2;
    LineEditCustom      *_firstName;
    LineEditCustom      *_lastName;
    QLabelCustom        *_picture;
    UserRequest         *_userRequest;
    QString             _nameProfilPicture;
    QLabel              *_titleLabel;
    QString             _pathProfilPicture;
    QLabel              *_errorLabel;
    QPushButton         *_subscribe;
    QPushButton         *_btnUploadProfilPicture;

protected slots:
    void addPicture();

private slots:
    void subscribe();
    void slotSubscribe(QNetworkReply *reply);
    void reInitialiseForm();
};

#endif // SUBSCRIBEPOPUP_H
