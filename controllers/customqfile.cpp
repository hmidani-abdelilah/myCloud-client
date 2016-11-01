#include "customqfile.h"

CustomQFile::CustomQFile(QString pathFile) : QFile(pathFile)
{
    _sizeUpload = 0;
    _constRefreshSpeed = 1000; // 1000 miliseconde
    _averageUploadSize = 0;
    _rangeUploadSpeed = 0;
    _status = Status::NONE;
}

CustomQFile::CustomQFile(QString pathFile, QString name, QString pathClient, QString pathServer, QString status, quint64 size, quint64 id, quint64 octetAlreadyTransfert) : QFile(pathFile)
{
    _size = size;
    _id = id;
    _name = name;
    _pathServer = pathServer;
    _pathClient = pathClient;

    _sizeUpload = octetAlreadyTransfert;
    _averageUploadSize = octetAlreadyTransfert;

    _constRefreshSpeed = 1000; // 1000 miliseconde
    _rangeUploadSpeed = 0;
    _status = Status::NONE;

    if (isFinish()) { // If all data are on the server
        _status = Status::FINISH;
    }
    else {
        if (!this->open(QIODevice::ReadOnly)) { // Try to open client file
            _status = Status::ERROR_CLIENT_PATH;
        }
        else {
            _status = CustomQFile::convertStringToStatus(status);
            this->read(octetAlreadyTransfert);
            this->start();
        }
    }
}

float CustomQFile::getUploadSpeed()
{
    return _rangeUploadSpeed;
}

int CustomQFile::getProgression()
{
    if (_sizeUpload > _size) // Probleme a resourdre, setOctetsSentToServer(int nbOctet) <- nbOctet = valeur en dur
        _sizeUpload = _size;
    return (float)_sizeUpload / (float)_size * 100;
}

bool CustomQFile::isFinish() {
    return _sizeUpload >= _size;
}

void CustomQFile::setOctetsSentToServer(int nbOctet) {
    _sizeUpload += nbOctet;
    _averageUploadSize += nbOctet;

    if (this->isFinish())
        setStatus(Status::FINISH);

    if (this->elapsed() > _constRefreshSpeed) {
        _rangeUploadSpeed = (_averageUploadSize / 1000) / (this->elapsed() / 1000);
        _averageUploadSize = 0;
        this->restart();
    }
}

void CustomQFile::setStatus(CustomQFile::Status status) {
    if (status == _status)
        return;
    _status = status;

    emit statusHasChanged(_id);
}

void CustomQFile::setPathServer(QString pathServer) {
    _pathServer = pathServer;
}

void CustomQFile::setPathClient(QString pathClient)
{
    _pathClient = pathClient;
}

QString CustomQFile::convertStatusToString(CustomQFile::Status status) // static
{
    switch (status) {
    case EN_COURS:
        return "En cours";
        break;
    case PAUSE:
        return "Pause";
        break;
    case DELETE:
        return "Delete";
        break;
    case FINISH:
        return "Finish";
        break;
    case ERROR_CLIENT_PATH:
        return "Error path client";
        break;
    default:
        return "Error";
        break;
    }
}

CustomQFile::Status CustomQFile::convertStringToStatus(QString status) //static
{
    if (status == "En cours")
        return Status::EN_COURS;
    else if (status == "Pause")
        return Status::PAUSE;
    else if (status == "Delete")
        return Status::DELETE;
    else if (status == "Finish")
        return Status::FINISH;
    else if (status == "Error path client")
        return Status::ERROR_CLIENT_PATH;
    else
        return Status::ERROR;
}
