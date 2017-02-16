#include "pathrequest.h"

PathRequest::PathRequest() : ServiceRequest()
{
    _listRoute.insert(Contents, &PathRequest::signalContent);
    _listRoute.insert(TreeRepository, &PathRequest::signalTreeRepository);
    _listRoute.insert(StatsRepository, &PathRequest::signalStatsRepository);
}

QString PathRequest::getRoute(int route, QMap<QString, QString> params) {
    Q_UNUSED(params);
    switch (route) {
    case Contents:
        return "/path/contents";
        break;
    case TreeRepository:
        return "/path/treeRepository";
        break;
    case StatsRepository:
        return "/path/statsRepository";
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
