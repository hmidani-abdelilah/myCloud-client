#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "managerelements.h"
#include "socketmanager.h"
#include "infoelement.h"
#include "filerequest.h"
#include "historicrequest.h"
#include "messageboxnaming.h"
#include "folderrequest.h"

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
    void sendFile(QUrl urlFile, QString location);

    InfoElement *getFile(qint64 id);
    void deleteFile(qint64 id);
    void downloadFile(QString pathFile, QString pathDevice, qint64 size);
    void createFolder(QString path);
    void moveElementTo(QString oldPath, QString newPath);
    void deleteFileOnServer(QString path);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    MessageBoxNaming *_messageBoxCreateFolder;

private slots:
    void responseSendFileDataToServer(QNetworkReply *reply);

    void statusFileChanged(qint64 id);
    void getlistTransfertOnServer(QNetworkReply *reply);

    void responseReplaceFile(QNetworkReply *reply);
    void responseHistoric(QNetworkReply *reply);

    void responseHistoricDelete(QNetworkReply *reply);
    void responseFile(QNetworkReply *reply);
    void responseBasic(QNetworkReply *reply);
    void responseDownloadFileDataFromServer(QNetworkReply *reply);
    void responseHistoricByIdUpdate(QNetworkReply *reply);
    void responseFolderCreate(QNetworkReply *reply);
    void responseRename(QNetworkReply *reply);
    void responseDeleteFileOnServer(QNetworkReply *reply);

signals:
    void startUploadFile(qint64);
    void fileDeletedInHistoric(qint64);
    void fileSended(StatsElement::Stats);
    void fileDeleted(StatsElement::Stats);
    void folderCreated(QByteArray reply);

private:
    explicit FileManager(QObject *parent = 0);
    SocketManager *_socketManager;
    FileRequest *_fileRequest;
    FolderRequest *_folderRequest;
    HistoricRequest *_historicRequest;

    QString _pathSendFile;
    QString _locationFileServer;
    QString getNameFile(QString &path, bool extension = true);
    QString getPathFile(QFile &file);
    void sendFileDataToServer(qint64 id);
    std::ifstream *_file;
    std::ofstream _myfileTest;
    QDataStream *_in;
    QTextStream *_stream;
    QFile *_qfile;
    QFile *_qfileTest;
    QByteArray _boundary;
    QTime *timer;
    int     _bufferSize;
    QMap<qint64, InfoElement*> *_fileList;
    void setNewFile(QString name, QString pathClient, QString pathServer, QString status, qint64 size, qint64 id, QString type, qint64 octetAlreadyTransfert = 0);
    void downloadFileDataFromServer(qint64 id);

    void responseInitializeForUpload(QNetworkReply *reply);
    void responseInitializeForDownload(QNetworkReply *reply);
};

#endif // FILEMANAGER_H
