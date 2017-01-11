#include "filemanager.h"
#include "credentailstable.h"
#include "jsonmanager.h"
#include "uploadelement.h"
#include "downloadelement.h"
#include "httperror.h"
#include "jsonerror.h"

#include <QTextEncoder>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QTextStream>

// TODO LE SEND FILE ET L'UPLOAD FILE TAPE SUR DES REQUETE COMPLETEMENT DIFFERENTE cela entraine le delete d'historique d'un coté et pas de l'autre.
// L'historique pour le sendFile est create dans le create .... WTF

FileManager *FileManager::_instanceFileManager = 0;

FileManager::FileManager(QObject *parent) : QObject(parent)
{
    _fileRequest = new FileRequest();

    _socketManager = SocketManager::getInstanceSocketM();
    _boundary = "-----------------------------7d935033608e2";
    _fileList = new QMap<quint64, InfoElement *>();
    _bufferSize = 16334;

    timer = new QTime();
    timer->start();

    connect(_fileRequest, &FileRequest::signalUpload, this, &FileManager::responseSendFileDataToServer);
    connect(_fileRequest, &FileRequest::signalDownload, this, &FileManager::responseDownloadFileDataFromServer);
    connect(_fileRequest, &FileRequest::signalFile, this, &FileManager::responseFile);
    connect(_fileRequest, &FileRequest::signalHistoric, this, &FileManager::responseHistoric);
    _fileRequest->request(FileRequest::GET, FileRequest::Historic);
}

FileManager *FileManager::getInstanceFileM()
{
    if (!_instanceFileManager) {
        _instanceFileManager = new FileManager();
    }
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

void FileManager::setNewFile(QString name, QString pathClient, QString pathServer, QString status, quint64 size, quint64 id, QString type, quint64 octetAlreadyTransfert) {
    InfoElement *file;

    qDebug(type.toStdString().c_str());
    if (type == "DOWNLOAD")
        file = new DownloadElement(QString (pathClient + "/" + name), name, pathClient, pathServer, status, size, id);
    else if (type == "UPLOAD")
        file = new UploadElement(QString (pathClient + "/" + name), name, pathClient, pathServer, status, size, id, octetAlreadyTransfert);
    else
        qDebug("[ERROR] : type incorect"); // TODO lancer une exeption

    connect(file, &InfoElement::statusHasChanged, this, &FileManager::statusFileChanged);

    _fileList->insert(id, file);
    emit startUploadFile(id); // use only for add file in transferPage

    statusFileChanged(id);
}

void FileManager::getlistTransfertOnServer(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

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
                map["type"],
                ((QString)(map["actualSize"])).toULongLong());
        json.initialize();
    }
}

void FileManager::sendFile(QString pathFile, QString location) {
    qDebug(pathFile.toStdString().c_str());
    QUrl url(pathFile);
    QFileInfo file(url.path());
    RouteParams prms;

    qDebug("[SEND FILE FUNCTION]");
    qDebug(pathFile.toStdString().c_str());

    prms.addValueToBody("size", QString::number(file.size()));
    prms.addValueToBody("name", url.fileName());
    prms.addValueToBody("status", UploadElement::convertStatusToString(UploadElement::Status::EN_COURS));
    prms.addValueToBody("pathServer", location);
    prms.addValueToBody("pathDevice", url.path().remove(url.path().length() - url.fileName().length() - 1, url.fileName().length() + 1));

    _fileRequest->request(FileRequest::POST, FileRequest::DefaultFile, prms);
}

void FileManager::downloadFile(QString pathFile, QString pathDevice, quint64 size) {
    QUrl urlPathFile(pathFile);
    QUrl urlPathDevice(pathDevice);
    //    QFileInfo file(url.path());
    RouteParams prms;

    qDebug("[DOWNLOAD FILE FUNCTION]");
    prms.addQueryItem("size", QString::number(size));
    prms.addQueryItem("name", urlPathFile.fileName());
    prms.addQueryItem("status", UploadElement::convertStatusToString(UploadElement::Status::EN_COURS));
    prms.addQueryItem("pathServer", urlPathFile.path().remove(urlPathFile.path().length() - urlPathFile.fileName().length() - 1, urlPathFile.fileName().length() + 1));
    prms.addQueryItem("pathDevice", urlPathDevice.path());
    prms.addQueryItem("type", "DOWNLOAD");
    _fileRequest->request(FileRequest::GET, FileRequest::DefaultFile, prms);
}

void FileManager::responseInitializeForUpload(QNetworkReply *reply) {

    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);
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
            RouteParams prms;
            prms.addQueryItem("pathServer", file["pathServer"]);
            prms.addQueryItem("name", file["name"]);
            QNetworkReply *reply = _fileRequest->request(FileRequest::DELETE, FileRequest::DefaultFile, prms);
            reply->setProperty("pathDevice", file["pathDevice"]);
            reply->setProperty("replaceFile", "active");
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

    if (file["idDeleted"].length() > 0) {
        emit fileDeletedInHistoric((file["idDeleted"]).toULongLong());
    }

    this->setNewFile(file["name"],
            file["pathDevice"],
            file["pathServer"],
            file["status"],
            ((QString)file["size"]).toULongLong(),
            ((QString)file["id"]).toULongLong(),
            file["type"]);
}

void FileManager::responseInitializeForDownload(QNetworkReply *reply) {
    JsonManager json(reply);
    QMap<QString, QString> fileCreate;

    fileCreate = json.getJson();

    // delete TransfertBar link with historic file destroy
    if (fileCreate["idDeleted"].length() > 0) {
        emit fileDeletedInHistoric((fileCreate["idDeleted"]).toULongLong());
    }

    this->setNewFile(fileCreate["name"],
            fileCreate["pathDevice"],
            fileCreate["pathServer"],
            fileCreate["status"],
            ((QString)(fileCreate["size"])).toULongLong(),
            ((QString)(fileCreate["id"])).toULongLong(),
            fileCreate["type"]);
}

void FileManager::responseFile(QNetworkReply *reply) {
    if (reply->property("verb") == "post") {
        responseInitializeForUpload(reply);
    }
    else if (reply->property("verb") == "get") {
        responseInitializeForDownload(reply);
    }
    else if (reply->property("verb") == "delete") {
        if (reply->property("replaceFile").toString() == "active")
            responseReplaceFile(reply);
        else if (reply->property("deleteTransferingFile").toString() == "active")
            responseDeleteTransferingFile(reply);
    }
}

void FileManager::responseDeleteTransferingFile(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);
    qDebug("DELETE TRANSFERT FILE");
}

InfoElement *FileManager::getFile(quint64 id) {
    //qDebug("test : %llu", id);
    return  _fileList->value(id);
}

void FileManager::sendFileDataToServer(quint64 id) {
    InfoElement *file = _fileList->value(id);

    if (file->isOpen()) {
        if (!file->atEnd()) {
            QByteArray data;

            data = file->read(_bufferSize);

            QByteArray body = "\r\n--" + _boundary + "\r\n";
            body += "Content-Disposition: form-data; name=\"" + QString::number(file->getId()) +  "\"; filename=\"" + file->getNameFile() + "\"\r\n";
            body += "Content-Type: application/octet-stream\r\n\r\n";
            body += data;
            body += "\r\n--" + _boundary + "--\r\n";

            _fileRequest->requestFile(FileRequest::POST, FileRequest::Upload, body, _boundary);
        }
        else {
            qDebug("Finish read file");
        }
    }
    else {
        qDebug("Open file - ReadOnly");
        if (!file->open(QIODevice::ReadOnly))
        {
            qDebug() << file->errorString();
            return ;
        }
        this->sendFileDataToServer(id);
    }
}

void FileManager::downloadFileDataFromServer(quint64 id) {
    qDebug() << "DOWNLOAD FILE DATA FROM SERVER";
    DownloadElement *file = dynamic_cast<DownloadElement *>(_fileList->value(id));
    RouteParams prms;

    prms.addQueryItem("pathFile", (file->getPathServer().length() > 0 ? file->getPathServer() + "/" : "") + file->getNameFile());

    int newBufferSize = file->getSize() - file->size();
    if (newBufferSize < _bufferSize)
        prms.addQueryItem("bufferSize", QString::number(newBufferSize));
    else
        prms.addQueryItem("bufferSize", QString::number(_bufferSize));

    prms.addQueryItem("position", QString::number(file->size()));
    prms.addQueryItem("id", QString::number(id));

    if (file->isOpen()) {
        QNetworkReply *reply = _fileRequest->request(FileRequest::GET, FileRequest::Download, prms);
        reply->setProperty("id", id);
    }
    else {
        qDebug("[ERROR] : File not open for download");
    }
}

void FileManager::responseDownloadFileDataFromServer(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

    int id = reply->property("id").toInt();
    DownloadElement *file = dynamic_cast<DownloadElement *>(_fileList->value(id));
    QByteArray dataFile = reply->readAll();
    file->write(dataFile);
    _fileList->value((QString::number(id)).toULongLong())->actualizeElementBySizeTranfered(dataFile.length());
    qDebug("size file %s -> %d", file->getNameFile().toStdString().c_str(), file->size());
    if (file->size() < file->getSize()) {
        downloadFileDataFromServer(id);
    }
    else {
        file->close();
        emit fileSended();
    }
}

void FileManager::responseSendFileDataToServer(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

    JsonManager jsonFile(reply);
    QMap<QString, QString> file = jsonFile.getJson();
    dynamic_cast<UploadElement *>(_fileList->value((file["id"]).toULongLong()))->setOctetsTransfered(_bufferSize);
    _fileList->value((file["id"]).toULongLong())->actualizeElementBySizeTranfered(_bufferSize);
    switch (_fileList->value((file["id"]).toULongLong())->getStatus()) {
    case UploadElement::Status::EN_COURS:
        this->sendFileDataToServer((file["id"]).toULongLong());
        break;
    case UploadElement::Status::FINISH:
        emit fileSended();
        break;
    case UploadElement::Status::DELETE:
        emit fileSended();
        break;
    default:
        break;
    }
}

void FileManager::deleteFile(quint64 id) {
    delete _fileList->value(id);
    _fileList->remove(id);
}

void FileManager::responseReplaceFile(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);
    JsonManager json(reply);
    QMap<QString, QString> file = json.getJson();
    sendFile(reply->property("pathDevice").toString() + "/" + file["name"], file["pathServer"]);
}

void FileManager::bytesWritten(qint64 bytes) {
    qDebug(QString::number(bytes).toStdString().c_str());
}

void FileManager::responseHistoric(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

    if (reply->property("verb") == "get") {
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
                    map["type"],
                    ((QString)(map["actualSize"])).toULongLong());
            json.initialize();
        }
    }

     else if (reply->property("verb") == "delete") {
        responseHistoricDelete(reply);
    }
}

void FileManager::responseHistoricDelete(QNetworkReply *reply) {
    JsonManager json(reply);
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

    QMap<QString, QString> file = json.getJson();
    emit fileDeletedInHistoric((file["id"]).toULongLong());
}

void FileManager::statusFileChanged(quint64 id) {
    InfoElement *file = _fileList->value(id);

    if (file == NULL)
        return;
    qDebug("%d", file->getStatus());
    switch (file->getStatus()) {
    case UploadElement::Status::EN_COURS: {
        file->start();
        if (file->type() == InfoElement::TransfertType::UPLOAD)
            this->sendFileDataToServer(id);
        else if (file->type() == InfoElement::TransfertType::DOWNLOAD)
            this->downloadFileDataFromServer(id);
        break;
    }
    case UploadElement::Status::FINISH:
        // send to server etat finish
        file->elapsed();
        break;
    case UploadElement::Status::DELETE: {
        RouteParams prms;
        prms.addQueryItem("name", file->getNameFile());
        prms.addQueryItem("pathServer", file->getPathServer());
        _fileRequest->request(FileRequest::DELETE, FileRequest::Historic, prms);
        if (file->getSizeTransfering() < file->getSize()) {
            RouteParams prmsDeleteFile;
            prmsDeleteFile.addQueryItem("pathServer", file->getPathServer());
            prmsDeleteFile.addQueryItem("name", file->getNameFile());
            QNetworkReply *reply = _fileRequest->request(FileRequest::DELETE, FileRequest::DefaultFile, prmsDeleteFile);
            reply->setProperty("deleteTransferingFile", "active");
        }
        break;
    }
    default:
        break;
    }
}
