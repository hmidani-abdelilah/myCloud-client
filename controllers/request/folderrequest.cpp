#include "folderrequest.h"

FolderRequest::FolderRequest() : ServiceRequest()
{
    _listRoute.insert(Create, &FolderRequest::signalCreate);
}

QString FolderRequest::getRoute(int route, QMap<QString, QString> params) {
    Q_UNUSED(params)
    switch (route) {
    case Create:
        return "/folder";
        break;
    default:
        return "";
        break;
    }
}

void FolderRequest::emitSignalResponseReady(QNetworkReply *reply) {
    PtrSignalFolder signal = _listRoute.value(static_cast<Folder>(reply->property("routeId").toInt()));
    emit (this->*(signal))(reply);
    delete reply;
}
