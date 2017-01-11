#ifndef FILEREQUEST_H
#define FILEREQUEST_H

#include "serviceRequest.h"

class FileRequest;
typedef void (FileRequest::*PtrSignalFile)(QNetworkReply *);

class FileRequest : public ServiceRequest
{
    Q_OBJECT
public:
    enum File {
        Upload,
        Download,
        DefaultFile,
        Historic,
        Reduce
    };

    FileRequest();

private:
    PtrSignalFile _ptrSignal;
    QMap<File, PtrSignalFile> _listRoute;

protected:
    QString getRoute(int route, QMap<QString, QString> params);

protected slots:
    virtual void emitSignalResponseReady(QNetworkReply *reply);

signals:
    void signalUpload(QNetworkReply *reply);
    void signalFile(QNetworkReply *reply);
    void signalHistoric(QNetworkReply *reply);
    void signalReduce(QNetworkReply *reply);
    void signalDownload(QNetworkReply *reply);
};

#endif // FILEREQUEST_H
