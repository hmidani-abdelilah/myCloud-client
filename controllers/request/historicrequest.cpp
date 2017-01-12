#include "historicrequest.h"

HistoricRequest::HistoricRequest() : ServiceRequest()
{
    _listRoute.insert(DefaultHistoric, &HistoricRequest::signalHistoric);
    _listRoute.insert(HistoricById, &HistoricRequest::signalHistoricById);
}

QString HistoricRequest::getRoute(int route, QMap<QString, QString> params) {
    switch (route) {
    case DefaultHistoric:
        return "/historic";
        break;
    case HistoricById:
        return "/historic/" + params["id"];
        break;
    default:
        break;
    }
}

void HistoricRequest::emitSignalResponseReady(QNetworkReply *reply) {
    PtrSignalHistoric signal = _listRoute.value(static_cast<File>(reply->property("routeId").toInt()));
    emit (this->*(signal))(reply);
}
