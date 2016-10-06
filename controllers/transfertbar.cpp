#include "transfertbar.h"
#include <QPushButton>
#include <QSpacerItem>

TransfertBar::TransfertBar(CustomQFile *file) : QHBoxLayout()
{
    QSpacerItem* spacerName = new QSpacerItem(10, 0);
    QSpacerItem* spacerSize = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored);
    QSpacerItem* spacerSizeTransfered = new QSpacerItem(0, 0);
    QSpacerItem* spacerProgressBar = new QSpacerItem(0, 0);
    QSpacerItem* spacerSpeed = new QSpacerItem(10, 0);
    QSpacerItem* spacerTime = new QSpacerItem(10, 0);
    QSpacerItem* spacerStatus = new QSpacerItem(10, 0);
    QSpacerItem* spacerBtnDelete =  new QSpacerItem(6, 0);

    _file = file;
    _transferedSize = new QLabelCustom("0");
    _name = new QLabelCustom("");
    _progressBar = new QProgressBar();
    _btnDelete = new QLabelCustom(":/logo/downloadDelete", 12, 12);
    _iconStatus = new QLabelCustom(":/logo/downloadFinish", 16, 16);
    _speedLabel = new QLabelCustom("0 Mo/s");
    _size = new QLabelCustom("0");
    _labelTime = new QLabelCustom("");
    setStatus(EN_COURS);
    _time = new QTime();

    _sizeTransfered = 0;

    this->setContentsMargins(0, 0, 0, 0);
    _progressBar->setRange(0, 100);
    _progressBar->setValue(0);
    _progressBar->setMinimumSize(100, 17);
    _progressBar->setMaximumSize(100, 17);
    _progressBar->setStyleSheet("QProgressBar {border: 1px solid grey; border-radius: 2px; background-color: #FFFFFF; font-size:11"
                                "px;} QProgressBar::chunk {background-color: #7fabda;}");
    _progressBar->setAlignment(Qt::AlignCenter);
    _progressBar->setTextVisible(true);

    _speedLabel->setMinimumWidth(100);
    _speedLabel->setAlignment(Qt::AlignRight);
    _size->setStyleSheet("padding-left:10px; padding-right:10px;");

    _size->setAlignment(Qt::AlignRight);
    _size->setMinimumWidth(100);

    _transferedSize->setAlignment(Qt::AlignRight);
    _transferedSize->setMinimumWidth(100);

    _name->setMaximumSize(400, 200);

    setName(_file->getNameFile());
    setSize(_file->getSize());
    setTime();

    this->addWidget(_iconStatus);
    this->addSpacerItem(spacerName);
    this->addWidget(_name);
    this->addSpacerItem(spacerSize);
    this->addWidget(_size);
    this->addSpacerItem(spacerProgressBar);
    this->addWidget(_transferedSize);
    this->addSpacerItem(spacerSizeTransfered);
    this->addWidget(_speedLabel);
    this->addSpacerItem(spacerSpeed);
    this->addWidget(_progressBar);
    this->addSpacerItem(spacerStatus);
    this->addWidget(_labelTime);
    this->addSpacerItem(spacerTime);
    this->addWidget(_statusLabel); // faire un fonction qui va sert la couleur et le statue. Fait peu etre un enum pour le status
    this->addSpacerItem(spacerBtnDelete);
    this->addWidget(_btnDelete);
}

void TransfertBar::updateElement() {
    setPourcentage(_file->getProgression());
    setSpeed(_file->getUploadSpeed());
    setTransferedSize(_file->getTransferedSize());
    setTime();
}

void TransfertBar::setName(QString name) {
    QFontMetrics metrics(_name->font());
    QString elidedText = metrics.elidedText(name, Qt::ElideMiddle, _name->width(), Qt::TextWordWrap);
    _name->setText(elidedText);
}

void TransfertBar::setPourcentage(int value) {
    _progressBar->setValue(value);
}

void TransfertBar::setTransferedSize(quint64 size) { // mettre cette fonction dans une classe helper ou autre ( CustomFIle )
    _sizeTransfered = size;
    if (size < 1000000)
        _transferedSize->setText(QString::number((float)size / 1000) + " Ko");
    else if (size < 1000000000)
        _transferedSize->setText(QString::number((float)size / 1000000) + "Mo");
    else
        _transferedSize->setText(QString::number((float)size / 1000000000) + "Go");
}

void TransfertBar::setSpeed(float speed) { // set speed with syntax ( ie: 2 mo/s)
    _speed = speed;
    if (speed < 1000) {
        _speedLabel->setText(QString::number(speed) + " Ko/s");
    }
    else
        _speedLabel->setText(QString::number(speed / 1000) + " Mo/s");
}

void TransfertBar::setSize(quint64 size) { // size octet in qint64
    if (size < 1000000)
        _size->setText(QString::number((float)size / 1000) + " Ko");
    else if (size < 1000000000)
        _size->setText(QString::number((float)size / 1000000) + "Mo");
    else
        _size->setText(QString::number((float)size / 1000000000) + "Go");
}

void TransfertBar::setTime() {
    _time->setHMS(0, 0, qRound(((float)(_file->getSize() - _sizeTransfered)) / (_speed * 1000)));
   _labelTime->setText(_time->toString());
}

void TransfertBar::setStatus(Status status) {
    _status = status;
    switch (_status) {
    case EN_COURS:
        _statusLabel = new QLabelCustom("En cours");
        break;
    case PAUSE:
        _statusLabel = new QLabelCustom("Pause");
        break;
    case STOP:
        _statusLabel = new QLabelCustom("Stop");
        break;
    }

}

