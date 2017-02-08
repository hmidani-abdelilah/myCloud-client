#include "httperror.h"

HttpError::HttpError(QNetworkReply *reply)
{
    _reply = reply;
}

QString HttpError::error()
{
    QString msg = "[ERROR HTTP " + QString::number(_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()) + "] : " + _reply->readAll();
    return msg;
}
