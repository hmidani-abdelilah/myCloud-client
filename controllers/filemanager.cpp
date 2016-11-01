#include "filemanager.h"
#include "credentailstable.h"
#include <QTextEncoder>
#include "jsonmanager.h"
#include "customqfile.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

FileManager *FileManager::_instanceFileManager = 0;

FileManager::FileManager(QObject *parent) : QObject(parent)
{
    _createFileRequest = new FileRequest();
    _fileRequest = new FileRequest();
    _fileRequestHictoric = new FileRequest();
    _deleteFile = new FileRequest();
    _deleteHistoricFile = new FileRequest();
    _replaceFile = new FileRequest();

    _socketManager = SocketManager::getInstanceSocketM();
    _boundary = "-----------------------------7d935033608e2";
    _listFile = new QMap<quint64, CustomQFile *>();
    _bufferSize = 16384;
    timer = new QTime();
    timer->start();
    connect(_createFileRequest, &ServiceRequest::finished, this, &FileManager::responseCreateFile);
    connect(_fileRequest, &ServiceRequest::finished, this, &FileManager::responseSendFileDataToServer);
    connect(_fileRequestHictoric, &ServiceRequest::finished, this, &FileManager::getlistTransfertOnServer);
    connect(_deleteFile, &ServiceRequest::finished, this, &FileManager::responseDeleteFile);
    connect(_replaceFile, &ServiceRequest::finished, this, &FileManager::responseReplaceFile);
    connect(_deleteHistoricFile, &ServiceRequest::finished, this, &FileManager::responseDeleteHistoricFile);

    _fileRequestHictoric->request(FileRequest::GET, FileRequest::Historic);
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

void FileManager::setNewFile(QString name, QString pathClient, QString pathServer, QString status, quint64 size, quint64 id, quint64 octetAlreadyTransfert) {
    QString pathFile(pathClient + "/" + name);

    CustomQFile *file = new CustomQFile(pathFile, name, pathClient, pathServer, status, size, id, octetAlreadyTransfert);
    connect(file, &CustomQFile::statusHasChanged, this, &FileManager::statusFileChanged);

    _listFile->insert(id, file);
    emit startUploadFile(id); // use only for add file in transferPage

    statusFileChanged(id);
}

void FileManager::getlistTransfertOnServer(QNetworkReply *reply) {
    JsonManager json(reply);

    int size = json.length();
    for (int i = 0 ; i < size ; i++) {
        QMap<QString, QString> map;
        map = json.toArray(i)->getJson();
        QMap<QString, QString>::iterator it;

        this->setNewFile(map["name"],
                map["pathDevice"],
                map["pathServer"],
                map["status"],
                ((QString)(map["size"])).toULongLong(),
                ((QString)(map["id"])).toULongLong(),
                ((QString)(map["actualSize"])).toULongLong());
        json.initialize();
    }
}

void FileManager::sendFile(QString pathFile, QString location) {
    QUrl url(pathFile);
    QFileInfo file(url.path());
    CredentailsTable cdt;

    qDebug("[FILE SEND]");
    qDebug(QString::number(file.size()).toStdString().c_str());
    qDebug(url.path().toStdString().c_str());
    cdt.addCredential("size", QString::number(file.size()));
    cdt.addCredential("name", url.fileName());
    cdt.addCredential("status", CustomQFile::convertStatusToString(CustomQFile::Status::EN_COURS));
    cdt.addCredential("pathServer", location);
    cdt.addCredential("pathDevice", url.path().remove(url.path().length() - url.fileName().length() - 1, url.fileName().length() + 1));

    _createFileRequest->request(FileRequest::POST, FileRequest::Create, cdt);
}

void FileManager::responseCreateFile(QNetworkReply *reply) {

    if (reply->error() != 0) {
        qDebug("Error : %d - server", reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt());
        return;
    }
    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 202) // file already exist
    {
        JsonManager jsonFile(reply);
        QMap<QString, QString> file = jsonFile.getJson();
        QMessageBox msgBox;

        msgBox.setText(file["msg"]);
        msgBox.setInformativeText("Do you want to replace this file ?");
        msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Yes: {
            CredentailsTable cdt;
            cdt.addCredential("pathServer", file["pathServer"]);
            cdt.addCredential("name", file["name"]);
            cdt.addCredential("pathDevice", file["pathDevice"]);
            _replaceFile->request(FileRequest::POST, FileRequest::DeleteFile, cdt);
            break;
        }
        case QMessageBox::Cancel: {
            // Don't Save was clicked
            break;
        }
        default: {
            // should never be reached
            break;
        }
        }
        return;
    }

    JsonManager jsonFile(reply);

    QMap<QString, QString> file = jsonFile.getJson();
    this->setNewFile(file["name"],
            file["pathDevice"],
            file["pathServer"],
            file["status"],
            ((QString)file["size"]).toULongLong(),
            ((QString)file["id"]).toULongLong());
}

CustomQFile* FileManager::getFile(quint64 id) {
    //qDebug("test : %llu", id);
    return  _listFile->value(id);
}

void FileManager::sendFileDataToServer(quint64 id) {
    CredentailsTable cdt;
    CustomQFile *file = _listFile->value(id);

    if (file->isOpen()) {
        if (!file->atEnd()) {
            QByteArray data;

            data = file->read(_bufferSize);

            QByteArray body = "\r\n--" + _boundary + "\r\n";
            body += "Content-Disposition: form-data; name=\"" + QString::number(file->getId()) +  "\"; filename=\"" + file->getNameFile() + "\"\r\n";
            body += "Content-Type: application/octet-stream\r\n\r\n";
            body += data;
            body += "\r\n--" + _boundary + "--\r\n";

            _fileRequest->requestFile(FileRequest::POST, FileRequest::Write, body, _boundary);
        }
        else {
            qDebug("Finish read file");
            emit fileSended();
        }
    }
    else {
        qDebug("Open file - ReadOnly");
        if (!file->open(QIODevice::ReadOnly))
        {
            qDebug() << file->errorString();
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

    JsonManager jsonFile(reply);
    QMap<QString, QString> file = jsonFile.getJson();
    _listFile->value((file["id"]).toULongLong())->setOctetsSentToServer(_bufferSize);

    switch (_listFile->value((file["id"]).toULongLong())->getStatus()) {
        case CustomQFile::Status::EN_COURS:
            this->sendFileDataToServer((file["id"]).toULongLong());
            break;
        case CustomQFile::Status::FINISH:
            emit fileSended();
            break;
        case CustomQFile::Status::DELETE:
            emit fileSended();
            break;
        default:
            break;
    }
}

void FileManager::responseDeleteFile(QNetworkReply *reply) {

}

void FileManager::responseDeleteHistoricFile(QNetworkReply *reply) {
    JsonManager json(reply);
    if (reply->error() != 0)
    {
        qDebug("Il y a eu une erreur lors de l'envoie sur le server %d", reply->error());
        return ;
    }

    QMap<QString, QString> file = json.getJson();
    emit fileDeletedInHistoric((file["id"]).toULongLong());
}

void FileManager::deleteFile(quint64 id) {
    delete _listFile->value(id);
    _listFile->remove(id);
}

void FileManager::responseReplaceFile(QNetworkReply *reply) {
    JsonManager json(reply);
    if (reply->error() != 0)
    {
        qDebug("Il y a eu une erreur lors de l'envoie sur le server %d", reply->error());
        return ;
    }

    QMap<QString, QString> file = json.getJson();
    sendFile(file["pathDevice"] + "/" + file["name"], file["pathServer"]);
}

void FileManager::bytesWritten(qint64 bytes) {
    qDebug(QString::number(bytes).toStdString().c_str());
}

void FileManager::statusFileChanged(quint64 id) {
    CustomQFile *file = _listFile->value(id);

    if (file == NULL)
        return;

    switch (file->getStatus()) {
    case CustomQFile::Status::EN_COURS:
        this->sendFileDataToServer(id);
        break;
    case CustomQFile::Status::FINISH:
        // send to server etat finish
        break;
    case CustomQFile::Status::DELETE: {
        CredentailsTable cdt;
        cdt.addCredential("name", file->getNameFile());
        cdt.addCredential("pathServer", file->getPathServer());
        _deleteHistoricFile->request(FileRequest::POST, FileRequest::File::Historic, cdt);
        break;
    }
    default:
        break;
    }
}
