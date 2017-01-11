#include "pathrequest.h"

PathRequest::PathRequest() : ServiceRequest()
{
    _listRoute.insert(Contents, &PathRequest::signalContent);
}

QString PathRequest::getRoute(int route, QMap<QString, QString> params) {
    switch (route) {
    case Contents:
        return "/path/contents";
        break;
    default:
        break;
    }
}

void PathRequest::emitSignalResponseReady(QNetworkReply *reply) {
    PtrSignalPath signal = _listRoute.value(static_cast<Path>(reply->property("routeId").toInt()));
    emit (this->*(signal))(reply);
}
