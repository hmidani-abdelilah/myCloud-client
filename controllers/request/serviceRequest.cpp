#include "serviceRequest.h"
#include <QNetworkConfigurationManager>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QNetworkRequest>
#include <QMap>
#include "httperror.h"

#include "globalinfo.h"

ServiceRequest::ServiceRequest() : QNetworkAccessManager()
{
    _host = "127.0.0.1:3000";
    _prefixRoute = "/api";
    _userAgent = "MyCloud/1.0 (Mac; Qt)";

    _params = new QMap<QString, QString>();

    _typeEnumList.insert(GET, "get");
    _typeEnumList.insert(POST, "post");
    _typeEnumList.insert(DELETE, "delete");
    _typeEnumList.insert(PUT, "put");

    connect(this, &ServiceRequest::finished, this, &ServiceRequest::getCookieKey);
    connect(this, &ServiceRequest::finished, this, &ServiceRequest::emitSignalResponseReady);
}

void ServiceRequest::setParams(QMap<QString, QString> *params) { // surement a degager _params
    _params = params;
}

void ServiceRequest::setParam(QString key, QString value) {
    _params->insert(key, value);
}

void ServiceRequest::getCookieKey(QNetworkReply * reply) {
    QList<QPair<QByteArray, QByteArray>> list = reply->rawHeaderPairs();
    QList<QPair<QByteArray, QByteArray>>::iterator it;

    for (it = list.begin() ; list.end() != it ; it++) {
        if ((*it).first == "set-cookie") {
            Server::GlobalInfo::sid = (*it).second;
            break;
        }
    }
}

void ServiceRequest::slotSslErrors(QList<QSslError>) {
    qDebug("ERROR : SSL");
}

QNetworkReply* ServiceRequest::request(Type type, int request, RouteParams prms) { // mettre l'enum au lieu du int
    QString route = getRoute(request, prms.params());
    if (route.length() <= 0) {
        qDebug("[ERROR] : BAD REQUEST");
        return NULL;
    }

    QString strRequest = "http://" + _host + _prefixRoute + route + prms.query();
    qDebug() << "REQUEST : [" << _typeEnumList[type] << "] " << strRequest.toStdString().c_str();

    QNetworkRequest networkRequest = QNetworkRequest(QUrl(strRequest));
    networkRequest.setRawHeader("User-Agent", _userAgent);
    networkRequest.setRawHeader("Cookie", Server::GlobalInfo::sid);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,  "application/x-www-form-urlencoded");

    QNetworkReply *reply;

    switch (type) {
    case POST:
        reply = this->post(networkRequest, prms.body());
        break;
    case GET:
        reply = this->get(networkRequest);
        break;
    case DELETE:
        reply = this->deleteResource(networkRequest);
        break;
    case PUT:
        reply = this->put(networkRequest, prms.body());
        break;
    default:
        qDebug("Type request is incorect");
        break;
    }

    if (reply == NULL) {
        qDebug("[ERROR] : BAD REQUEST");
    }

    reply->setProperty("routeId", request);
    reply->setProperty("verb", _typeEnumList[type]);
    connect(reply, &QNetworkReply::sslErrors, this, &ServiceRequest::slotSslErrors);
    return reply;
}

QNetworkReply* ServiceRequest::requestFile(Type type, int request, QByteArray body, QByteArray boundary, QString pathServer, qint64 totalSize) { // mettre l'enum au lieu du int
    QString route = getRoute(request, QMap<QString, QString>());
    if (route.length() <= 0) {
        qDebug("[ERROR] : BAD REQUEST");
        return NULL;
    }

    QString strRequest = "http://" + _host + _prefixRoute + route;
    //qDebug() << "REQUEST : [" << _typeEnumList[type] << "] " << strRequest.toStdString().c_str();

    QNetworkRequest networkRequest = QNetworkRequest(QUrl(strRequest));

    networkRequest.setRawHeader( "User-Agent" , _userAgent );
    networkRequest.setRawHeader("Cookie", Server::GlobalInfo::sid);
    networkRequest.setRawHeader("Content-Type","multipart/form-data; boundary=" + boundary);
    networkRequest.setRawHeader("path-server", QByteArray(pathServer.toStdString().c_str()));
    networkRequest.setRawHeader("total-size", QByteArray(QString::number(totalSize).toStdString().c_str()));
    networkRequest.setHeader(QNetworkRequest::ContentLengthHeader, body.size());

    QNetworkReply *reply;

    switch (type) {
    case POST:
        reply = this->post(networkRequest, body);
        break;
    default:
        return NULL;
        break;
    }

    reply->setProperty("routeId", request);
    reply->setProperty("verb", _typeEnumList[type]);
    connect(reply, &QNetworkReply::sslErrors, this, &ServiceRequest::slotSslErrors);
    return reply;
}
