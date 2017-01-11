#ifndef PATHREQUEST_H
#define PATHREQUEST_H

#include "serviceRequest.h"

class PathRequest;
typedef void (PathRequest::*PtrSignalPath)(QNetworkReply *);

class PathRequest : public ServiceRequest
{
    Q_OBJECT
public:
    enum Path {
        Contents
    };


    PathRequest();

private:
    PtrSignalPath _ptrSignal;
    QMap<Path, PtrSignalPath> _listRoute;

protected slots:
    virtual void emitSignalResponseReady(QNetworkReply *reply);

protected:
    QString getRoute(int route, QMap<QString, QString> params);

signals:
    void signalContent(QNetworkReply *reply);
};

#endif // PATHREQUEST_H
