#include "infoelement.h"

InfoElement::InfoElement(QString pathFile, QString name, QString pathClient, QString pathServer, QString status, quint64 size, quint64 id)  : QFile(pathFile)
{
    _size = size;
    _id = id;
    _name = name;
    _pathServer = pathServer;
    _pathClient = pathClient;
    _status = InfoElement::convertStringToStatus(status);

    //_sizeTransfered = octetAlreadyTransfered;
    //_averageTransfertSize = octetAlreadyTransfered;

    _constRefreshSpeed = 1000;

    _rangeTransfertSpeed = 0;
    _transfertType = TransfertType::UNDEFINED;
}

float InfoElement::getTransfertSpeed()
{
    return _rangeTransfertSpeed;
}

void InfoElement::actualizeElementBySizeTranfered(int nbOctet) {
    _averageTransfertSize += nbOctet;

    if (this->isFinish())
        setStatus(Status::FINISH);

    if (this->elapsed() > _constRefreshSpeed) {
        _rangeTransfertSpeed = (_averageTransfertSize / 1000) / (this->elapsed() / 1000);
        _averageTransfertSize = 0;
        this->restart();
    }
}

void InfoElement::setStatus(InfoElement::Status status)
{
    if (status == _status)
        return;
    _status = status;

    emit statusHasChanged(_id);
}

QString InfoElement::convertStatusToString(InfoElement::Status status) // static
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

InfoElement::Status InfoElement::convertStringToStatus(QString status) //static
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
