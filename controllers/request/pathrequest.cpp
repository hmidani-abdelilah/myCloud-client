#include "pathrequest.h"

PathRequest::PathRequest() : ServiceRequest()
{
    _listRoute.insert(Contents, &PathRequest::signalContent);
    _listRoute.insert(RepositoryTree, &PathRequest::signalRepositoryTree);
}

QString PathRequest::getRoute(int route, QMap<QString, QString> params) {
    Q_UNUSED(params);
    switch (route) {
    case Contents:
        return "/path/contents";
        break;
    case RepositoryTree:
        return "/path/repositoryTree";
        break;
    default:
        return "";
        break;
    }
}

void PathRequest::emitSignalResponseReady(QNetworkReply *reply) {
    PtrSignalPath signal = _listRoute.value(static_cast<Path>(reply->property("routeId").toInt()));
    emit (this->*(signal))(reply);
    delete reply;
}
