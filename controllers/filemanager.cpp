#include "filemanager.h"
#include "credentailstable.h"
#include "jsonmanager.h"
#include "uploadelement.h"
#include "downloadelement.h"
#include "httperror.h"
#include "jsonerror.h"
#include "statselement.h"

#include <QTextEncoder>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QTextStream>

FileManager *FileManager::_instanceFileManager = 0;

FileManager::FileManager(QObject *parent) : QObject(parent)
{
    _fileRequest = new FileRequest();
    _historicRequest = new HistoricRequest();
    _folderRequest = new FolderRequest();

    _socketManager = SocketManager::getInstanceSocketM();
    _boundary = "-----------------------------7d935033608e2";
    _fileList = new QMap<qint64, InfoElement *>();
    _bufferSize = 16334;

    timer = new QTime();
    timer->start();

    _messageBoxCreateFolder = new MessageBoxNaming ("Name of the folder", "Create");

    connect(_fileRequest, &FileRequest::signalUpload, this, &FileManager::responseSendFileDataToServer);
    connect(_fileRequest, &FileRequest::signalDownload, this, &FileManager::responseDownloadFileDataFromServer);
    connect(_fileRequest, &FileRequest::signalFile, this, &FileManager::responseFile);
    connect(_historicRequest, &HistoricRequest::signalHistoric, this, &FileManager::responseHistoric);
    connect(_historicRequest, &HistoricRequest::signalHistoricById, this, &FileManager::responseHistoricByIdUpdate);
    connect(_folderRequest, &FolderRequest::signalCreate, this, &FileManager::responseFolderCreate);
    connect(_fileRequest, &FileRequest::signalRename, this, &FileManager::responseRename);
    _historicRequest->request(HistoricRequest::GET, HistoricRequest::DefaultHistoric);
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

void FileManager::setNewFile(QString name, QString pathClient, QString pathServer, QString status, qint64 size, qint64 id, QString type, qint64 octetAlreadyTransfert) {
    InfoElement *file;

    if (type == QString("DOWNLOAD"))
        file = new DownloadElement(QString (pathClient + "/" + name), name, pathClient, pathServer, StatsElement::convertStringToStatus(status), size, id, StatsElement::TypeElement::FILE);
    else if (type == QString("UPLOAD"))
        file = new UploadElement(QString (pathClient + "/" + name), name, pathClient, pathServer, StatsElement::convertStringToStatus(status), size, id, octetAlreadyTransfert, StatsElement::TypeElement::FILE);
    else {
        qDebug("[ERROR] : type incorect"); // TODO lancer une exeption
        return;
    }

    connect(file, &InfoElement::statusHasChanged, this, &FileManager::statusFileChanged);

    _fileList->insert(id, file);
    emit startUploadFile(id); // use only for add file in transferPage

    if (file->status() != InfoElement::FINISH)
        statusFileChanged(id);
}

void FileManager::getlistTransfertOnServer(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

    JsonManager json(reply);
    QMap<QString, QVariant> map;

    int size = json.length();
    for (int i = 0 ; i < size ; i++) {
        map = json.toArray(i)->getJson();

        this->setNewFile(map["name"].toString(),
                map["pathDevice"].toString(),
                map["pathServer"].toString(),
                map["status"].toString(),
                map["size"].toLongLong(),
                map["id"].toLongLong(),
                map["type"].toString(),
                map["actualSize"].toLongLong());
    }

}

void FileManager::sendFile(QUrl urlFile, QString location) {
    QFileInfo file(urlFile.path());
    RouteParams prms;

    prms.addValueToBody("size", QString::number(file.size()));
    prms.addValueToBody("name", urlFile.fileName());
    prms.addValueToBody("status", UploadElement::convertStatusToString(InfoElement::Status::EN_COURS));
    prms.addValueToBody("pathServer", location);
    prms.addValueToBody("pathDevice", urlFile.path().remove(urlFile.path().length() - urlFile.fileName().length() - 1, urlFile.fileName().length() + 1));
    prms.addValueToBody("type", "UPLOAD");
    _fileRequest->request(FileRequest::POST, FileRequest::DefaultFile, prms);
}

void FileManager::downloadFile(QString pathFile, QString pathDevice, qint64 size) {
    QUrl urlPathFile(pathFile);
    QUrl urlPathDevice(pathDevice);
    RouteParams prms;

    prms.addQueryItem("size", QString::number(size));
    prms.addQueryItem("name", urlPathFile.fileName());
    prms.addQueryItem("status", UploadElement::convertStatusToString(InfoElement::Status::EN_COURS));
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
        QMap<QString, QVariant> file = jsonFile.getJson();
        QMessageBox msgBox;

        msgBox.setText(file["msg"].toString());
        msgBox.setInformativeText("Do you want to replace this file ?");
        msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Yes: {
            RouteParams prms;
            prms.addQueryItem("pathServer", file["pathServer"].toString());
            prms.addQueryItem("name", file["name"].toString());
            QNetworkReply *replyRequest = _fileRequest->request(FileRequest::DELETE, FileRequest::DefaultFile, prms);
            replyRequest->setProperty("pathDevice", file["pathDevice"]);
            replyRequest->setProperty("replaceFile", "active");
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

    QMap<QString, QVariant> file = jsonFile.getJson();

    if (file.contains("idDeleted")) {
        emit fileDeletedInHistoric((file["idDeleted"]).toULongLong());
    }

    this->setNewFile(file["name"].toString(),
            file["pathDevice"].toString(),
            file["pathServer"].toString(),
            file["status"].toString(),
            file["size"].toLongLong(),
            file["id"].toLongLong(),
            file["type"].toString());
}

void FileManager::responseInitializeForDownload(QNetworkReply *reply) {
    JsonManager json(reply);
    QMap<QString, QVariant> fileCreate;

    fileCreate = json.getJson();

    // delete TransfertBar link with historic file destroy
    if (fileCreate.contains("idDeleted")) {
        emit fileDeletedInHistoric((fileCreate["idDeleted"]).toULongLong());
    }

    this->setNewFile(fileCreate["name"].toString(),
            fileCreate["pathDevice"].toString(),
            fileCreate["pathServer"].toString(),
            fileCreate["status"].toString(),
            fileCreate["size"].toLongLong(),
            fileCreate["id"].toLongLong(),
            fileCreate["type"].toString());
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
        else if (reply->property("deleteFile").toString() == "active")
            responseDeleteFile(reply);
        else if (reply->property("deleteFileAndRename").toString() == "active") {
            moveElementTo(reply->property("oldPath").toString(), reply->property("newPath").toString());
        }
    }
}

void FileManager::responseDeleteFile(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

    qDebug("DELETE TRANSFERT FILE");
}

InfoElement *FileManager::getFile(qint64 id) {
    return  _fileList->value(id);
}

void FileManager::sendFileDataToServer(qint64 id) {
    InfoElement *file = _fileList->value(id);

    if (file->isOpen()) {
        if (!file->atEnd()) {
            QByteArray data;

            data = file->read(_bufferSize);

            QByteArray body = "\r\n--" + _boundary + "\r\n";
            body += "Content-Disposition: form-data; name=\"" + QString::number(file->id()) +  "\"; filename=\"" + file->name() + "\"\r\n";
            body += "Content-Type: application/octet-stream\r\n\r\n";
            body += data;
            body += "\r\n--" + _boundary + "--\r\n";

            _fileRequest->requestFile(FileRequest::POST, FileRequest::Upload, body, _boundary, file->pathServer(), file->size());
            data.clear();
        }
        else {
            qDebug("Finish read file");
        }
    }
    else {
        qDebug() << file->errorString();
    }
}

void FileManager::downloadFileDataFromServer(qint64 id) {
    DownloadElement *file = dynamic_cast<DownloadElement *>(_fileList->value(id));
    RouteParams prms;

    prms.addQueryItem("pathFile", (file->pathServer().length() > 0 ? file->pathServer() + "/" : "") + file->name());

    int newBufferSize = file->sizeServer() - file->size();
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
    //qDebug("file->size() : %d - file->sizeServer() : %d", file->size(), file->sizeServer());

    _fileList->value((QString::number(id)).toULongLong())->actualizeElementBySizeTranfered(dataFile.length());

    switch (_fileList->value((QString::number(id)).toULongLong())->status()) {
    case InfoElement::Status::EN_COURS: {
        downloadFileDataFromServer(id);
        break;
    }
    case InfoElement::Status::FINISH: {
        file->close();
        break;
    }
    default:
        break;
    }
}

void FileManager::responseSendFileDataToServer(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

    JsonManager jsonFile(reply);
    QMap<QString, QVariant> file = jsonFile.getJson();
    dynamic_cast<UploadElement *>(_fileList->value(file["id"].toLongLong()))->setOctetsTransfered(_bufferSize);
    _fileList->value(file["id"].toLongLong())->actualizeElementBySizeTranfered(_bufferSize);

    InfoElement *elem = this->getFile(file["id"].toLongLong());

    switch (_fileList->value(file["id"].toLongLong())->status()) {
    case InfoElement::Status::EN_COURS:
        this->sendFileDataToServer(file["id"].toLongLong());
        break;
    case InfoElement::Status::FINISH:
        emit fileSended(elem->stats());
        break;
    case InfoElement::Status::DELETE:
        emit fileSended(elem->stats());
        break;
    default:
        break;
    }
}

void FileManager::deleteFile(qint64 id) {
    delete _fileList->value(id);
    _fileList->remove(id);
}

void FileManager::responseReplaceFile(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);
    JsonManager json(reply);
    QMap<QString, QVariant> file = json.getJson();

    StatsElement::Stats stats(file["name"].toString(), file["pathServer"].toString());

    emit fileReplaced(stats);
    sendFile(reply->property("pathDevice").toString() + "/" + file["name"].toString(), file["pathServer"].toString());
}

void FileManager::responseHistoric(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

    if (reply->property("verb") == "get") {
        JsonManager json(reply);
        int size = json.length();
        for (int i = 0 ; i < size ; i++) {
            QMap<QString, QVariant> map;
            map = json.toArray(i)->getJson();

            this->setNewFile(map["name"].toString(),
                    map["pathDevice"].toString(),
                    map["pathServer"].toString(),
                    map["status"].toString(),
                    map["size"].toLongLong(),
                    map["id"].toLongLong(),
                    map["type"].toString(),
                    map["actualSize"].toLongLong());
            json.initialize();
        }
    }
}

void FileManager::responseHistoricDelete(QNetworkReply *reply) {
    JsonManager json(reply);
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

    QMap<QString, QVariant> file = json.getJson();
    emit fileDeletedInHistoric(file["id"].toLongLong());
}

void FileManager::responseHistoricByIdUpdate(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

    if (reply->property("verb") == "delete") {
        responseHistoricDelete(reply);
    }
}

void FileManager::createFolder(QString path) {
    _messageBoxCreateFolder->exec();

    RouteParams prms;

    prms.addValueToBody("pathServer", path);
    prms.addValueToBody("name", _messageBoxCreateFolder->text());

    _folderRequest->request(FolderRequest::POST, FolderRequest::Folder::Create, prms);
}

void FileManager::responseFolderCreate(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);
    emit folderCreated(reply->readAll());
}

void FileManager::moveElementTo(QString oldPath, QString newPath) {
    RouteParams prms;

    prms.addValueToBody("oldPath", oldPath);
    prms.addValueToBody("newPath", newPath);
    _fileRequest->request(FileRequest::Type::PUT, FileRequest::Rename, prms);
}

void FileManager::responseRename(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

    JsonManager json(reply);

    QMap<QString, QVariant> file = json.getJson();
    QFileInfo oldFileInfo(file["oldPath"].toString());
    QFileInfo newFileInfo(file["newPath"].toString());

    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 202) // file already exist
    {
        QMessageBox msgBox;

        msgBox.setText(file["msg"].toString());
        msgBox.setInformativeText("Do you want to replace this file ?");
        msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Yes: {
            RouteParams prms;
            prms.addQueryItem("pathServer", (newFileInfo.path() == "." ? "" : newFileInfo.path()));
            prms.addQueryItem("name", newFileInfo.fileName());
            QNetworkReply *replyRequest = _fileRequest->request(FileRequest::DELETE, FileRequest::DefaultFile, prms);
            replyRequest->setProperty("deleteFileAndRename", "active");
            replyRequest->setProperty("oldPath", file["oldPath"]);
            replyRequest->setProperty("newPath", file["newPath"]);
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

    StatsElement::Stats statsOldfFile(oldFileInfo.fileName(), (oldFileInfo.path() == "." ? "" : oldFileInfo.path()));
    StatsElement::Stats statsNewfFile(newFileInfo.fileName(), (newFileInfo.path() == "." ? "" : newFileInfo.path()));

    emit fileReplaced(statsOldfFile);
    emit fileSended(statsNewfFile);
}

void FileManager::statusFileChanged(qint64 id) {
    InfoElement *file = _fileList->value(id);

    if (file == NULL)
        return;

    RouteParams prms;
    prms.setParam("id", QString::number(id));

    switch (file->status()) {
    case InfoElement::Status::EN_COURS: {
        file->start();
        if (file->type() == InfoElement::TransfertType::UPLOAD)
            this->sendFileDataToServer(id);
        else if (file->type() == InfoElement::TransfertType::DOWNLOAD)
            this->downloadFileDataFromServer(id);

        prms.addValueToBody("status", InfoElement::convertStatusToString(InfoElement::EN_COURS));
        _historicRequest->request(HistoricRequest::PUT, HistoricRequest::HistoricById, prms);
        break;
    }
    case InfoElement::Status::PAUSE: {
        prms.addValueToBody("status", InfoElement::convertStatusToString(InfoElement::PAUSE));
        _historicRequest->request(HistoricRequest::PUT, HistoricRequest::HistoricById, prms);
        break;
    }
    case InfoElement::Status::FINISH: {
        prms.addValueToBody("status", InfoElement::convertStatusToString(InfoElement::FINISH));
        _historicRequest->request(HistoricRequest::PUT, HistoricRequest::HistoricById, prms);

        file->elapsed();
        file->close();
        break;
    }
    case InfoElement::Status::DELETE: {
        RouteParams prms;
        prms.setParam("id", QString::number(id));
        _historicRequest->request(HistoricRequest::DELETE, HistoricRequest::HistoricById, prms);
        if (file->type() == InfoElement::UPLOAD && file->getSizeTransfering() < file->sizeServer()) {
            RouteParams prmsDeleteFile;
            prmsDeleteFile.addQueryItem("pathServer", file->pathServer());
            prmsDeleteFile.addQueryItem("name", file->name());
            QNetworkReply *reply = _fileRequest->request(FileRequest::DELETE, FileRequest::DefaultFile, prmsDeleteFile);
            reply->setProperty("deleteFile", "active");
        }
        if (file->type() == InfoElement::DOWNLOAD && file->getSizeTransfering() < file->sizeServer()) {
            file->remove();
        }
        // TODO DELETE LE FICHIER SUR L'ORDI SI IL EST INCOMPLET ( DOWNLOAD )
        break;
    }
    default:
        break;
    }
}
