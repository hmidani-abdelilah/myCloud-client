#ifndef USERREQUEST_H
#define USERREQUEST_H

#include "serviceRequest.h"

class UserRequest;
typedef void (UserRequest::*PtrSignalUser)(QNetworkReply *);

class UserRequest : public ServiceRequest
{
    Q_OBJECT
public:
    enum User {
        Connection,
        LogOut,
        Subscribe,
        ProfilPicture
    };


    UserRequest();

private:
    PtrSignalUser _ptrSignal;
    QMap<User, PtrSignalUser> _listRoute;

protected slots:
    virtual void emitSignalResponseReady(QNetworkReply *reply);

protected:
    QString getRoute(int route, QMap<QString, QString>);

signals:
    void signalConnected(QNetworkReply *reply);
    void signalLogOut(QNetworkReply *reply);
    void signalSubscribe(QNetworkReply *reply);
    void signalProfilPicture(QNetworkReply *reply);
};

#endif // USERREQUEST_H
