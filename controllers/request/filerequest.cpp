#include "filerequest.h"

FileRequest::FileRequest() : ServiceRequest()
{
    _listRoute.insert(Upload, &FileRequest::signalUpload);
    _listRoute.insert(Download, &FileRequest::signalDownload);
    _listRoute.insert(DefaultFile, &FileRequest::signalFile);
    _listRoute.insert(Historic, &FileRequest::signalHistoric);
    _listRoute.insert(Reduce, &FileRequest::signalReduce);
    _listRoute.insert(HistoricById, &FileRequest::signalHistoricById);
    _listRoute.insert(Rename, &FileRequest::signalRename);
}

QString FileRequest::getRoute(int route, QMap<QString, QString> params) {
    switch (route) {
    case Upload:
        return "/file/upload";
        break;
    case Download:
        return "/file/download";
        break;
    case DefaultFile:
        return "/file";
        break;
    case Historic:
        return "/historic";
        break;
    case HistoricById:
        return "/historic/" + params["id"];
        break;
    case Reduce:
        return "/file/reduce/" + params["name"];
        break;
    case Rename:
        return "/file/rename";
        break;
    default:
        return "";
        break;
    }
}

void FileRequest::emitSignalResponseReady(QNetworkReply *reply) {
    PtrSignalFile signal = _listRoute.value(static_cast<File>(reply->property("routeId").toInt()));
    emit (this->*(signal))(reply);
    delete reply;
}
