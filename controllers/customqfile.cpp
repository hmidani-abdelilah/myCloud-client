#include "customqfile.h"

CustomQFile::CustomQFile(QString nameFile) : QFile(nameFile)
{
    _sizeUpload = 0;
    _constRefreshSpeed = 1000; // 2000 miliseconde
    _averageUploadSize = 0;
    _rangeUploadSpeed = 0;
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

void CustomQFile::setOctetsSentToServer(int nbOctet) {
    _sizeUpload += nbOctet;
    _averageUploadSize += nbOctet;

    if (this->elapsed() > _constRefreshSpeed) {
        _rangeUploadSpeed = (_averageUploadSize / 1000) / (this->elapsed() / 1000);
        _averageUploadSize = 0;
        this->start();
    }
}
