#include "headers/info_elements/downloadelement.h"
#include <QFileInfo>

DownloadElement::DownloadElement(QString pathFile, QString name, QString pathClient, QString pathServer, QString status, quint64 size, quint64 id) :
    InfoElement(pathFile, name, pathClient, pathServer, status, size, id)
{
    _transfertType = TransfertType::DOWNLOAD;
    // si le fichier est deja dans le dossier tmp ne pas le telecharger

    if (isFinish()) { // If all data has been send
        _status = Status::FINISH;
    }

    QString stringToEncrypt = pathServer + pathClient + name;
    _key = QString(QCryptographicHash::hash((stringToEncrypt.toUtf8()),QCryptographicHash::Md5).toHex());

    this->setFileName(pathClient + "/" + name);
    if (!this->open(QIODevice::WriteOnly | QIODevice::Append)) { // TODO ne pas ouvrir si finish ??
        qDebug("[ERROR] : open download file");
        return;
    }
}

int DownloadElement::getProgression()
{
    return (float)this->size() / (float)_size * 100;
}

bool DownloadElement::isFinish() {
    return this->size() >= _size;
}

quint64 DownloadElement::getSizeTransfering() {
    return this->size();
}
