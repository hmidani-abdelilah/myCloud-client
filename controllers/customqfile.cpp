#include "UploadElement.h"

UploadElement::UploadElement(QString pathFile) : QFile(pathFile)
{
    _sizeTransfered = 0;
    _constRefreshSpeed = 1000; // 1000 miliseconde
    _averageTransfertSize = 0;
    _rangeTransfertSpeed = 0;
    _status = Status::NONE;

    _transfertTypeRef.insert("UPLOAD", TransfertType::UPLOAD);
    _transfertTypeRef.insert("DOWNLOAD", TransfertType::DOWNLOAD);
    _transfertTypeRef.insert("UNDEFINED", TransfertType::UNDEFINED);

    _transfertType = TransfertType::UNDEFINED;
}

UploadElement::UploadElement(QString pathFile, QString name, QString pathClient, QString pathServer, QString status, quint64 size, quint64 id, quint64 octetAlreadyTransfert, QString transfertType) : QFile(pathFile)
{
    _size = size;
    _id = id;
    _name = name;
    _pathServer = pathServer;
    _pathClient = pathClient;

    _sizeTransfered = octetAlreadyTransfert;
    _averageTransfertSize = octetAlreadyTransfert;

    _constRefreshSpeed = 1000; // 1000 miliseconde
    _rangeTransfertSpeed = 0;
    _status = Status::NONE;
    _transfertType = _transfertTypeRef[transfertType];

    if (isFinish()) { // If all data are on the server
        _status = Status::FINISH;
    }
    else {
        if (!this->open(QIODevice::ReadOnly)) { // Try to open client file
            _status = Status::ERROR_CLIENT_PATH;
        }
        else {
            _status = UploadElement::convertStringToStatus(status);
            this->read(octetAlreadyTransfert);
            this->start();
        }
    }
}

float UploadElement::getTransfertSpeed()
{
    return _rangeTransfertSpeed;
}

int UploadElement::getProgression()
{
    if (_sizeTransfered > _size) // Probleme a resourdre, setOctetsTransfered(int nbOctet) <- nbOctet = valeur en dur
        _sizeTransfered = _size;
    return (float)_sizeTransfered / (float)_size * 100;
}

bool UploadElement::isFinish() {
    return _sizeTransfered >= _size;
}

UploadElement::TransfertType UploadElement::type()
{
    return _transfertType;
}

void UploadElement::setOctetsTransfered(int nbOctet)
{
    _sizeTransfered += nbOctet;
    _averageTransfertSize += nbOctet;

    if (this->isFinish())
        setStatus(Status::FINISH);

    if (this->elapsed() > _constRefreshSpeed) {
        _rangeTransfertSpeed = (_averageTransfertSize / 1000) / (this->elapsed() / 1000);
        _averageTransfertSize = 0;
        this->restart();
    }
}

void UploadElement::setStatus(InfoElement::Status status)
{
    if (status == _status)
        return;
    _status = status;

    emit statusHasChanged(_id);
}

void UploadElement::setPathServer(QString pathServer)
{
    _pathServer = pathServer;
}

void UploadElement::setPathClient(QString pathClient)
{
    _pathClient = pathClient;
}

QString UploadElement::convertStatusToString(InfoElement::Status status) // static
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

InfoElement::Status UploadElement::convertStringToStatus(QString status) //static
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
