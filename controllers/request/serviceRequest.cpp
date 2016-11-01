#include "serviceRequest.h"
#include <QNetworkConfigurationManager>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QNetworkRequest>
#include <QMap>

#include "globalinfo.h"

ServiceRequest::ServiceRequest() : QNetworkAccessManager()
{
    _host = "127.0.0.1:3000";
    _prefixRoute = "/api";
    _userAgent = "MyCloud/1.0 (Mac; Qt)";

    _params = new QMap<QString, QString>();
    connect(this, &ServiceRequest::finished, this, &ServiceRequest::signalRequest);
}

void ServiceRequest::setParams(QMap<QString, QString> *params) {
    _params = params;
}

void ServiceRequest::setParam(QString key, QString value) {
    _params->insert(key, value);
}

void ServiceRequest::signalRequest(QNetworkReply * reply) {
    QList<QPair<QByteArray, QByteArray>> list = reply->rawHeaderPairs();
    QList<QPair<QByteArray, QByteArray>>::iterator it;

    for (it = list.begin() ; list.end() != it ; it++) {
        if ((*it).first == "set-cookie") {
            Server::GlobalInfo::sid = (*it).second;
        }
    }
}

void ServiceRequest::slotError(QNetworkReply::NetworkError error) {
    qDebug(QString(QString("ERROR numero : ") + QString::number(error)).toStdString().c_str());
    switch (error) {
    case QNetworkReply::ContentOperationNotPermittedError:
        qDebug("The operation requested on the remote content is not permitted");
        break;
    case QNetworkReply::ContentNotFoundError:
        qDebug("HTTP error 404");
        break;
    default:
        break;
    }
}

void ServiceRequest::slotSslErrors(QList<QSslError> error) {
    qDebug("ERROR : SSL");
}

void ServiceRequest::request(Type type, int request, QByteArray cdt) { // mettre l'enum au lieu du int
    QString strRequest = "REQUEST : http://" + _host + _prefixRoute + getRoute(request);
    QNetworkRequest networkRequest = QNetworkRequest(QUrl("http://" + _host + _prefixRoute + getRoute(request)));
    networkRequest.setRawHeader("User-Agent", _userAgent);
    networkRequest.setRawHeader("Cookie", Server::GlobalInfo::sid);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,  "application/x-www-form-urlencoded");

    switch (type) {
    case POST: {
        QNetworkReply *replyPost = this->post(networkRequest, cdt);
        connect(replyPost, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &ServiceRequest::slotError);
        connect(replyPost, &QNetworkReply::sslErrors, this, &ServiceRequest::slotSslErrors);
        break;
    }
    case GET: {
        if (cdt.length() > 0) {
            QString url = networkRequest.url().toString() + QString("?") + QString(cdt.toStdString().c_str());
            qDebug(url.toStdString().c_str());
            networkRequest.setUrl(url);
        }
        QNetworkReply *replyGet = this->get(networkRequest);
        connect(replyGet, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &ServiceRequest::slotError);
        connect(replyGet, &QNetworkReply::sslErrors, this, &ServiceRequest::slotSslErrors);
        break;
    }
    case DELETE: {
        QNetworkReply *replyDelete = this->deleteResource(networkRequest);
        connect(replyDelete, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &ServiceRequest::slotError);
        connect(replyDelete, &QNetworkReply::sslErrors, this, &ServiceRequest::slotSslErrors);
        break;
    }
    case PUT: {
        QNetworkReply *replyPut = this->put(networkRequest, cdt);
        connect(replyPut, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &ServiceRequest::slotError);
        connect(replyPut, &QNetworkReply::sslErrors, this, &ServiceRequest::slotSslErrors);
        break;
    }
    default:
        break;
    }
}

void ServiceRequest::requestFile(Type type, int request, QByteArray cdt, QByteArray boundary) { // mettre l'enum au lieu du int
    QString strRequest = "REQUEST FILE : http://" + _host + _prefixRoute + getRoute(request);
    QNetworkRequest networkRequest = QNetworkRequest(QUrl("http://" + _host + _prefixRoute + getRoute(request)));
    networkRequest.setRawHeader( "User-Agent" , _userAgent );
    networkRequest.setRawHeader("Cookie", Server::GlobalInfo::sid);
    networkRequest.setRawHeader("Content-Type","multipart/form-data; boundary=" + boundary);
    networkRequest.setHeader(QNetworkRequest::ContentLengthHeader,cdt.size());

    switch (type) {
    case POST: {
        QNetworkReply *replyPost = this->post(networkRequest, cdt);
        connect(replyPost, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &ServiceRequest::slotError);
        connect(replyPost, &QNetworkReply::sslErrors, this, &ServiceRequest::slotSslErrors);
        connect(replyPost, &QNetworkReply::bytesWritten, this, &ServiceRequest::bytesWrittenSlot);
        break;
    }
    default:
        break;
    }
}

void ServiceRequest::bytesWrittenSlot(qint64 bytes) {
    qDebug("LA SIZE");
    qDebug(QString::number(bytes).toStdString().c_str());
}

