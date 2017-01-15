#include "userrequest.h"

UserRequest::UserRequest() : ServiceRequest()
{
    _listRoute.insert(Connection, &UserRequest::signalConnected);
}

QString UserRequest::getRoute(int route, QMap<QString, QString> params) {
    switch (route) {
    case Connection:
        return "/user/login";
        break;
    case Test:
        return "/user";
        break;
    default:
        break;
    }
}

void UserRequest::emitSignalResponseReady(QNetworkReply *reply) {
    PtrSignalUser signal = _listRoute.value(static_cast<User>(reply->property("routeId").toInt()));
    emit (this->*(signal))(reply);
    delete reply;
}
