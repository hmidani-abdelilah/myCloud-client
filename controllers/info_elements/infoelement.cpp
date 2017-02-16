#include "infoelement.h"

InfoElement::InfoElement(QString pathFile, QString name, QString pathClient, QString pathServer, Status status, qint64 size, qint64 id, TypeElement typeElement)  :
    QFile(pathFile),
    StatsElement(name, size, 0, pathServer, pathClient, typeElement, status)
{
    _id = id;
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

    switch (status) {
    case InfoElement::Status::PAUSE:
        _rangeTransfertSpeed = 0;

        break;
    default:
        break;
    }

    _status = status;

    emit statusHasChanged(_id);
}
