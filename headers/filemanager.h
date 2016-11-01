#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QTime>

#include "managerelements.h"
#include "socketmanager.h"
#include "customqfile.h"
#include "filerequest.h"
#include <iostream>
#include <fstream>
#include <string>
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

    CustomQFile *getFile(quint64 id);
    void deleteFile(quint64 id);
protected:
    void dragEnterEvent(QDragEnterEvent *event);

private slots:
    void bytesWritten(qint64 bytes);
    void responseSendFileDataToServer(QNetworkReply *reply);
    void responseCreateFile(QNetworkReply *reply);

    void statusFileChanged(quint64 id);
    void getlistTransfertOnServer(QNetworkReply *reply);

    void responseDeleteFile(QNetworkReply *reply);
    void responseDeleteHistoricFile(QNetworkReply *reply);
    void responseReplaceFile(QNetworkReply *reply);
signals:
    void startUploadFile(quint64);
    void fileSended();
    void fileDeletedInHistoric(quint64);

private:
    explicit FileManager(QObject *parent = 0);
    SocketManager *_socketManager;
    FileRequest *_fileRequest;
    FileRequest *_createFileRequest;
    FileRequest *_fileRequestHictoric;
    FileRequest *_deleteFile;
    FileRequest *_deleteHistoricFile;
    FileRequest *_replaceFile;

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
    QMap<quint64, CustomQFile*> *_listFile;
    void setNewFile(QString name, QString pathClient, QString pathServer, QString status, quint64 size, quint64 id, quint64 octetAlreadyTransfert = 0);
};

#endif // FILEMANAGER_H
