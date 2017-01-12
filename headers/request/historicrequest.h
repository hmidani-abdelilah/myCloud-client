#ifndef HISTORICREQUEST_H
#define HISTORICREQUEST_H

#include "serviceRequest.h"

class HistoricRequest;
typedef void (HistoricRequest::*PtrSignalHistoric)(QNetworkReply *);

class HistoricRequest : public ServiceRequest
{
    Q_OBJECT
public:
    enum File {
        DefaultHistoric,
        HistoricById
    };

    HistoricRequest();

private:
    PtrSignalHistoric _ptrSignal;
    QMap<File, PtrSignalHistoric> _listRoute;

protected:
    QString getRoute(int route, QMap<QString, QString> params);

protected slots:
    virtual void emitSignalResponseReady(QNetworkReply *reply);

signals:
    void signalHistoric(QNetworkReply *reply);
    void signalHistoricById(QNetworkReply *reply);
};

#endif // HISTORICREQUEST_H
