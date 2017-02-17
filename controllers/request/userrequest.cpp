#include "userrequest.h"

UserRequest::UserRequest() : ServiceRequest()
{
    _listRoute.insert(Connection, &UserRequest::signalConnected);
    _listRoute.insert(LogOut, &UserRequest::signalLogOut);
    _listRoute.insert(Subscribe, &UserRequest::signalSubscribe);
    _listRoute.insert(ProfilPicture, &UserRequest::signalProfilPicture);
}

QString UserRequest::getRoute(int route, QMap<QString, QString> params) {
    Q_UNUSED(params);
    switch (route) {
    case Connection:
        return "/user/login";
        break;
    case LogOut:
        return "/user/logout";
        break;
    case Subscribe:
        return "/user/subscribe";
        break;
    case ProfilPicture:
        return "/user/uploadProfilPicture";
        break;
    default:
        return "";
        break;
    }
}

void UserRequest::emitSignalResponseReady(QNetworkReply *reply) {
    PtrSignalUser signal = _listRoute.value(static_cast<User>(reply->property("routeId").toInt()));
    emit (this->*(signal))(reply);
    delete reply;
}
