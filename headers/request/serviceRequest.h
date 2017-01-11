#ifndef SERVICEREQUEST_H
#define SERVICEREQUEST_H

#include "credentailstable.h"
#include "routeparams.h"

#include <QObject>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QFile>

class ServiceRequest : public QNetworkAccessManager {
    Q_OBJECT

public:
    enum Type {
        POST,
        GET,
        PUT,
        DELETE
    };

    ServiceRequest();
    ~ServiceRequest() {}
    QNetworkReply *request(Type type, int request, RouteParams prms = RouteParams());
    void requestFile(Type type, int request, QByteArray body, QByteArray boundary);
    void setParams(QMap<QString, QString> *params);
    void setParam(QString key, QString value);

protected:
    QString _host;
    QString _prefixRoute;
    QVector<QString> _route;
    QByteArray _sid;
    QByteArray _userAgent;
    QMap<QString, QString> *_params;
    QMap<Type, QString> _typeEnumList;
    virtual QString getRoute(int route, QMap<QString, QString> params) = 0;

public slots:
    void slotSslErrors(QList<QSslError> error);

protected slots:
    virtual void emitSignalResponseReady(QNetworkReply *reply) = 0;

private slots:
    void getCookieKey(QNetworkReply *reply);
};


#endif // SERVICEREQUEST_H
