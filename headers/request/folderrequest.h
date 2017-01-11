#ifndef FOLDERREQUEST_H
#define FOLDERREQUEST_H

#include "serviceRequest.h"

class FolderRequest;
typedef void (FolderRequest::*PtrSignalFolder)(QNetworkReply *);

class FolderRequest : public ServiceRequest
{
    Q_OBJECT
public:
    enum Folder {
        Create
    };

    FolderRequest();

private:
    PtrSignalFolder _ptrSignal;
    QMap<Folder, PtrSignalFolder> _listRoute;

protected:
    QString getRoute(int route, QMap<QString, QString> params);

protected slots:
    virtual void emitSignalResponseReady(QNetworkReply *reply);

signals:
    void signalCreate(QNetworkReply *reply);
};

#endif // FOLDERREQUEST_H
