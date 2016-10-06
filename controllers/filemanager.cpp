#include "filemanager.h"
#include "credentailstable.h"
#include <QTextEncoder>
#include "jsonmanager.h"
#include "customqfile.h"

FileManager *FileManager::_instanceFileManager = 0;

FileManager::FileManager(QObject *parent) : QObject(parent)
{
    _createFileRequest = new FileRequest();
    _fileRequest = new FileRequest();
    _socketManager = SocketManager::getInstanceSocketM();
    _boundary = "-----------------------------7d935033608e2";
    _listFile = new QMap<QString, CustomQFile *>();
    _bufferSize = 16384;
    timer = new QTime();
    timer->start();
    connect(_createFileRequest, &ServiceRequest::finished, this, &FileManager::responseCreateFile);
    connect(_fileRequest, &ServiceRequest::finished, this, &FileManager::responseSendFileDataToServer);
}

FileManager *FileManager::getInstanceFileM()
{
    if (!_instanceFileManager)
        _instanceFileManager = new FileManager();
    return _instanceFileManager;
}

QString FileManager::getPathFile(QFile &file) {
    QString path = file.fileName();
    while (path.length() > 0) {
        if (path[path.length() - 1] == '/')
        {
            path.remove(path.length() - 1, 1);
            return path;
        }
        path.remove(path.length() - 1, 1);
    }
    return path;
}

QString FileManager::getNameFile(QString &path, bool extension) {
    QStringList list = path.split("/");
    if (extension == false)
    {
        QString name = list[list.length() - 1];
        for (int i = name.length() ; i != 0 ; i--) {
            if (name[i] != '.')
                name.remove(i, 1);
            else {
                name.remove(i, 1);
                return name;
            }
        }
    }
    return list[list.length() - 1];
}

void FileManager::setNewFile(QString name, QString pathClient, QString status, quint64 size, QString id) {
    QString pathClientName(pathClient + "/" + name);

    CustomQFile *file = new CustomQFile(pathClientName);
    file->setStatus(status);
    file->setSize(size);
    file->setId(id);
    file->setNameFile(name);
    _listFile->insert(id, file);
}

void FileManager::sendFile(QString pathFile, QString location) {

    QUrl url(pathFile);
    QFileInfo file(url.path());
    CredentailsTable cdt;

    qDebug(url.path().toStdString().c_str());
    cdt.addCredential("size", QString::number(file.size()));
    cdt.addCredential("name", url.fileName());
    cdt.addCredential("status", "en cour");
    cdt.addCredential("pathServer", location);
    cdt.addCredential("pathDevice", url.path().remove(url.path().length() - url.fileName().length() - 1, url.fileName().length() + 1));
    _createFileRequest->request(FileRequest::POST, FileRequest::Create, cdt);
}

void FileManager::responseCreateFile(QNetworkReply *reply) {
    if (reply->error() != 0) {
        qDebug("Error : %d - server", reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt());
        return;
    }

    JsonManager json(reply);

    this->setNewFile(json["name"],
                     json["pathClient"],
                     json["status"],
                     ((QString)json["size"]).toULongLong(),
                     json["id"]);

    emit startUploadFile(json["id"]);
    this->sendFileDataToServer(json["id"]);
}

void FileManager::addManagerElement(ManagerElements *elem)
{
    _listManagerElement.append(elem);
}

CustomQFile* FileManager::getFile(QString id) {
    return  _listFile->value(id);
}

void FileManager::sendFileDataToServer(QString id) {
    CredentailsTable cdt;
    CustomQFile *file = _listFile->value(id);

    if (file->isOpen()) {
        if (!file->atEnd()) {
            QByteArray data;

            data = file->read(_bufferSize);

            QByteArray body = "\r\n--" + _boundary + "\r\n";
            body += "Content-Disposition: form-data; name=\"" + file->getId() +  "\"; filename=\"" + file->getNameFile() + "\"\r\n";
            body += "Content-Type: application/octet-stream\r\n\r\n";
            body += data;
            body += "\r\n--" + _boundary + "--\r\n";

            _fileRequest->requestFile(FileRequest::POST, FileRequest::Write, body, _boundary);
        }
        else {
            qDebug("Finish read file");
            sendDataFinish();
        }
    }
    else {
        qDebug("Open file - ReadOnly");
        if (!file->open(QIODevice::ReadOnly))
        {
            qDebug("Failed to open file to send");
            return ;
        }
        file->start();
        this->sendFileDataToServer(id);
    }
}

void FileManager::responseSendFileDataToServer(QNetworkReply *reply) {
    if (reply->error() != 0)
    {
        qDebug("Il y a eu une erreur lors de l'envoie sur le server %d", reply->error());
        return ;
    }

    JsonManager json(reply);
    _listFile->value(json["id"])->setOctetsSentToServer(16384);
    this->sendFileDataToServer(json["id"]);
}

void FileManager::bytesWritten(qint64 bytes) {
    //_socketManager->getWebSocket(SocketManager::Route::SENDFILE)->flush();
    qDebug(QString::number(bytes).toStdString().c_str());
}

void FileManager::sendDataFinish() {
    for (int i = 0 ; i < _listManagerElement.size() ; i++) {
        _listManagerElement.at(i)->refreshActualPage();
    }
}
