#ifndef SERVICEREQUEST_H
#define SERVICEREQUEST_H

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include "credentailstable.h"
#include <QFile>

class ServiceRequest : public QNetworkAccessManager {

public:
    enum Type {
        POST,
        GET,
        PUT,
        DELETE
    };

    ServiceRequest();
    ~ServiceRequest() {}
    void request(Type type, int request, QByteArray cdt = 0);
    void requestFile(Type type, int request, QByteArray cdt, QByteArray boundary);

    void setParams(QMap<QString, QString> *params);
    void setParam(QString key, QString value);
protected:
    QString _host;
    QString _prefixRoute;
    QVector<QString> _route;
    QByteArray _sid;
    QByteArray _userAgent;
    QMap<QString, QString> *_params;

    virtual QString getRoute(int route) = 0;

public slots:
    void slotError(QNetworkReply::NetworkError error);
    void slotSslErrors(QList<QSslError> error);
    void bytesWrittenSlot(qint64 bytes);
private slots:
    void signalRequest(QNetworkReply *reply);
};

#endif // SERVICEREQUEST_H
