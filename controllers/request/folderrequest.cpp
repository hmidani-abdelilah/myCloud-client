#include "folderrequest.h"

FolderRequest::FolderRequest() : ServiceRequest()
{
    _listRoute.insert(Create, &FolderRequest::signalCreate);
}

QString FolderRequest::getRoute(int route, QMap<QString, QString> params) {
    switch (route) {
    case Create:
        return "/folder";
        break;
    default:
        break;
    }
}

void FolderRequest::emitSignalResponseReady(QNetworkReply *reply) {
    PtrSignalFolder signal = _listRoute.value(static_cast<Folder>(reply->property("routeId").toInt()));
    emit (this->*(signal))(reply);
}
