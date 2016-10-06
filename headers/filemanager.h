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
    void addManagerElement(ManagerElements *elem);

    CustomQFile *getFile(QString id);
protected:
    void dragEnterEvent(QDragEnterEvent *event);

private slots:
    void bytesWritten(qint64 bytes);
    void responseSendFileDataToServer(QNetworkReply *reply);
    void responseCreateFile(QNetworkReply *reply);

signals:
    void startUploadFile(QString);

private:
    explicit FileManager(QObject *parent = 0);
    SocketManager *_socketManager;
    FileRequest *_fileRequest;
    FileRequest *_createFileRequest;
    QString _pathSendFile;
    QString _locationFileServer;
    QString getNameFile(QString &path, bool extension = true);
    QString getPathFile(QFile &file);
    void sendFileDataToServer(QString id);
    std::ifstream *_file;
    std::ofstream _myfileTest;
    QDataStream *_in;
    QTextStream *_stream;
    QFile *_qfile;
    QFile *_qfileTest;
    QByteArray _boundary;
    QTime *timer;
    int     _bufferSize;
    QMap<QString, CustomQFile*> *_listFile;
    QList<ManagerElements *> _listManagerElement;
    void setNewFile(QString name, QString pathClient, QString status, quint64 size, QString id);
    virtual void sendDataFinish();
};

#endif // FILEMANAGER_H
