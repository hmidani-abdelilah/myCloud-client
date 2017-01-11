#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "managerelements.h"
#include "socketmanager.h"
#include "infoelement.h"
#include "filerequest.h"
#include <iostream>
#include <fstream>
#include <string>

#include <QObject>
#include <QTime>
#include <QWidget>
#include <QFileInfo>

class ManagerElements;

class FileManager : public QObject
{
    Q_OBJECT
public:
    static FileManager *_instanceFileManager;
    static FileManager *getInstanceFileM();
    void sendFile(QString pathFile, QString location);

    InfoElement *getFile(quint64 id);
    void deleteFile(quint64 id);
    void downloadFile(QString pathFile, QString pathDevice, quint64 size);

protected:
    void dragEnterEvent(QDragEnterEvent *event);

private slots:
    void bytesWritten(qint64 bytes);
    void responseSendFileDataToServer(QNetworkReply *reply);

    void statusFileChanged(quint64 id);
    void getlistTransfertOnServer(QNetworkReply *reply);

    void responseReplaceFile(QNetworkReply *reply);
    void responseHistoric(QNetworkReply *reply);

    void responseHistoricDelete(QNetworkReply *reply);
    void responseFile(QNetworkReply *reply);
    void responseDeleteTransferingFile(QNetworkReply *reply);
    void responseDownloadFileDataFromServer(QNetworkReply *reply);

signals:
    void startUploadFile(quint64);
    void fileSended();
    void fileDeletedInHistoric(quint64);

private:
    explicit FileManager(QObject *parent = 0);
    SocketManager *_socketManager;
    FileRequest *_fileRequest;
//    FileRequest *_createFileRequest;
//    FileRequest *_fileRequestHictoric;
//    FileRequest *_deleteFile;
//    FileRequest *_deleteHistoricFile;
//    FileRequest *_replaceFile;

    QString _pathSendFile;
    QString _locationFileServer;
    QString getNameFile(QString &path, bool extension = true);
    QString getPathFile(QFile &file);
    void sendFileDataToServer(quint64 id);
    std::ifstream *_file;
    std::ofstream _myfileTest;
    QDataStream *_in;
    QTextStream *_stream;
    QFile *_qfile;
    QFile *_qfileTest;
    QByteArray _boundary;
    QTime *timer;
    int     _bufferSize;
    QMap<quint64, InfoElement*> *_fileList;
    void setNewFile(QString name, QString pathClient, QString pathServer, QString status, quint64 size, quint64 id, QString type, quint64 octetAlreadyTransfert = 0);
    void downloadFileDataFromServer(quint64 id);

    void responseInitializeForUpload(QNetworkReply *reply);
    void responseInitializeForDownload(QNetworkReply *reply);
};

#endif // FILEMANAGER_H
