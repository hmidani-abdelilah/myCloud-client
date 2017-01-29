#include "statselement.h"

StatsElement::StatsElement(QString name, quint64 size, quint64 transferedSize, QString pathServer, QString pathClient, TypeElement type, Status status)
{
    setStats(name, size, transferedSize, pathServer, pathClient, type, status);
}

StatsElement::Stats StatsElement::stats() {
    return Stats(_name,
                 _sizeServer,
                 _transferedSize,
                 _pathServer,
                 _pathClient,
                 _typeElement,
                 _status);
}

bool StatsElement::isInitialize() {
    if (_name == ""
            && _sizeServer == 0
            && _transferedSize == 0
            && _pathServer == "undefined"
            && _pathClient == "undefined"
            && _typeElement == TypeElement::UNDEFINED
            && _status == Status::NONE) {
        return false;
    }
    return true;
}

bool StatsElement::setStats(Stats stats) {
    if (isInitialize())
        return false;

    setStats(stats.name,
             stats.size,
             stats.transferedSize,
             stats.pathServer,
             stats.pathClient,
             stats.typeElement,
             stats.status);
    return true;
}

void StatsElement::setStats(QString name, quint64 size, quint64 transferedSize, QString pathServer, QString pathClient, TypeElement typeElement, Status status) {
    _name = name;
    _sizeServer = size;
    _transferedSize = transferedSize;
    _pathServer = pathServer;
    _pathClient = pathClient;
    _typeElement = typeElement;
    _status = status;
}

QString StatsElement::convertStatusToString(StatsElement::Status status) // static
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

StatsElement::Status StatsElement::convertStringToStatus(QString status) //static
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
