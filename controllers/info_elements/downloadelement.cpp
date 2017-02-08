#include "downloadelement.h"
#include <QFileInfo>

DownloadElement::DownloadElement(QString pathFile, QString name, QString pathClient, QString pathServer, Status status, qint64 size, qint64 id, TypeElement typeElement) :
    InfoElement(pathFile, name, pathClient, pathServer, status, size, id, typeElement)
{
    _transfertType = TransfertType::DOWNLOAD;
    // si le fichier est deja dans le dossier tmp ne pas le telecharger

    if (isFinish()) { // If all data has been send
        _status = Status::FINISH;
    }

    this->setFileName(pathClient + "/" + name);
    if (!isFinish() && !this->open(QIODevice::WriteOnly | QIODevice::Append)) { // TODO ne pas ouvrir si finish ??
        qDebug("[ERROR] : open download file");
        return;
    }
}

int DownloadElement::getProgression()
{
    return (float)this->size() / (float)_sizeServer * 100;
}

bool DownloadElement::isFinish() {
    return this->size() >= _sizeServer;
}

qint64 DownloadElement::getSizeTransfering() {
    return this->size();
}
