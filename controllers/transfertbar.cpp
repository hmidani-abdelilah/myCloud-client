#include "transfertbar.h"
#include "globalinfo.h"
#include <QPushButton>
#include <QSpacerItem>
#include <QStyleOption>
#include <QPainter>

TransfertBar::TransfertBar(CustomQFile *file) : QWidget()
{
    QSpacerItem* spacerName = new QSpacerItem(10, 0);
    QSpacerItem* spacerSize = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored);
    QSpacerItem* spacerSizeTransfered = new QSpacerItem(0, 0);
    QSpacerItem* spacerProgressBar = new QSpacerItem(0, 0);
    QSpacerItem* spacerSpeed = new QSpacerItem(10, 0);
    QSpacerItem* spacerTime = new QSpacerItem(10, 0);
    QSpacerItem* spacerStatus = new QSpacerItem(10, 0);
    QSpacerItem* spacerBtnDelete =  new QSpacerItem(6, 0);

    _layout = new QHBoxLayout();
    _file = file;
    _transferedSize = new QLabelCustom("0");
    _name = new QLabelCustom("");
    _progressBar = new QProgressBar();
    _btnDelete = new QLabelCustom(":/logo/downloadDelete", 12, 12);
    _iconStatus = new QLabelCustom(":/logo/downloadFinish", 16, 16);
    _speedLabel = new QLabelCustom("0 Mo/s");
    _size = new QLabelCustom("0");
    _labelTime = new QLabelCustom("");
    _statusLabel = new QLabelCustom("");

    setStatus();

    _time = new QTime();
    _sizeTransfered = 0;

    connect(_btnDelete, &QLabelCustom::clicked, this, &TransfertBar::slotClickOnDelete);

    this->setMaximumHeight(40);
    this->setContentsMargins(0, 0, 0, 0);

    this->setCursor(Qt::PointingHandCursor);

    _iconStatus->setAttribute( Qt::WA_TransparentForMouseEvents );

    _labelTime->setAttribute( Qt::WA_TransparentForMouseEvents );

    _statusLabel->setAttribute( Qt::WA_TransparentForMouseEvents );

    _progressBar->setRange(0, 100);
    _progressBar->setValue(file->getProgression());
    _progressBar->setMinimumSize(100, 17);
    _progressBar->setMaximumSize(100, 17);
    _progressBar->setStyleSheet("QProgressBar {border: 1px solid grey; border-radius: 2px; background-color: #FFFFFF; font-size:11"
                                "px;} QProgressBar::chunk {background-color: #7fabda;}");
    _progressBar->setAlignment(Qt::AlignCenter);
    _progressBar->setTextVisible(true);
    _progressBar->setAttribute( Qt::WA_TransparentForMouseEvents );

    _speedLabel->setMinimumWidth(100);
    _speedLabel->setAlignment(Qt::AlignRight);
    _speedLabel->setAttribute( Qt::WA_TransparentForMouseEvents );

    _size->setStyleSheet("padding-left:10px; padding-right:10px;");
    _size->setAlignment(Qt::AlignRight);
    _size->setMinimumWidth(100);
    _size->setAttribute( Qt::WA_TransparentForMouseEvents );

    _transferedSize->setAlignment(Qt::AlignRight);
    _transferedSize->setMinimumWidth(100);
    _transferedSize->setAttribute( Qt::WA_TransparentForMouseEvents );

    _name->setMaximumSize(400, 200);
    _name->setAttribute( Qt::WA_TransparentForMouseEvents );

    setName(_file->getNameFile());
    setSize(_file->getSize());
    setTime();

    _layout->addWidget(_iconStatus);
    _layout->addSpacerItem(spacerName);
    _layout->addWidget(_name);
    _layout->addSpacerItem(spacerSize);
    _layout->addWidget(_size);
    _layout->addSpacerItem(spacerProgressBar);
    _layout->addWidget(_transferedSize);
    _layout->addSpacerItem(spacerSizeTransfered);
    _layout->addWidget(_speedLabel);
    _layout->addSpacerItem(spacerSpeed);
    _layout->addWidget(_progressBar);
    _layout->addSpacerItem(spacerStatus);
    _layout->addWidget(_labelTime);
    _layout->addSpacerItem(spacerTime);
    _layout->addWidget(_statusLabel); // faire un fonction qui va sert la couleur et le statue. Fait peu etre un enum pour le status
    _layout->addSpacerItem(spacerBtnDelete);
    _layout->addWidget(_btnDelete);

    _layout->setAlignment(Qt::AlignTop);

    setLayout(_layout);
}

void TransfertBar::updateElement() {
    setPourcentage();
    setSpeed();
    setTransferedSize();
    setStatus();
    setTime();
}

void TransfertBar::setName(QString name) {
    QFontMetrics metrics(_name->font());
    QString elidedText = metrics.elidedText(name, Qt::ElideMiddle, _name->width(), Qt::TextWordWrap);
    _name->setText(elidedText);
}

void TransfertBar::setPourcentage() {
    _progressBar->setValue(_file->getProgression());
}

void TransfertBar::setTransferedSize() { // mettre cette fonction dans une classe helper ou autre ( CustomFIle )
    quint64 size = _file->getTransferedSize();

    _sizeTransfered = size;
    if (size < 1000000)
        _transferedSize->setText(QString::number((float)size / 1000) + " Ko");
    else if (size < 1000000000)
        _transferedSize->setText(QString::number((float)size / 1000000) + "Mo");
    else
        _transferedSize->setText(QString::number((float)size / 1000000000) + "Go");
}

void TransfertBar::setSpeed() { // set speed with syntax ( ie: 2 mo/s)
    float speed = _file->getUploadSpeed();
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
    int secondToWait = 0;
    if (!_file->isFinish() && _speed > 0)
        secondToWait = qRound(((float)(_file->getSize() - _sizeTransfered)) / (_speed * 1000));

    _time->setHMS(0, 0, secondToWait);
    qDebug(_time->toString().toStdString().c_str());
    _labelTime->setText(_time->toString());
}

void TransfertBar::setStatus() {
    _statusLabel->setText(CustomQFile::convertStatusToString(_file->getStatus()));

    switch (_file->getStatus()) {
    case CustomQFile::Status::FINISH: {
        _iconStatus->changeImageColor("1BB71E");
        break;
    }
    case CustomQFile::Status::PAUSE: {
        _iconStatus->changeImageColor("FFD400");
        break;
    }
    case CustomQFile::Status::EN_COURS: {
        _iconStatus->changeImageColor("329ED1");
        break;
    }
    case CustomQFile::Status::DELETE: {
        break;

    }
    case CustomQFile::Status::ERROR_CLIENT_PATH: {
        _iconStatus->changeImageColor("F45342");
        break;
    }
    }
}

void TransfertBar::changeStatusOfFile(CustomQFile::Status status) {
    _file->setStatus(status);
    _statusLabel->setText(CustomQFile::convertStatusToString(status));
}

void TransfertBar::paintEvent(QPaintEvent *) {
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void TransfertBar::hasBeenSelected(bool value) {
    if (value == true) {
        this->setStyleSheet("background-color:#" + Color::GlobalInfo::lightBlueSelection + ";");
    }
    else {
        this->setStyleSheet("background-color:#FFFFFF;");
    }
}

void TransfertBar::slotClickOnDelete() {
    emit clickOnDelete(this);
}

QLabelCustom* TransfertBar::getBtnDelete() {
    return _btnDelete;
}

quint64 TransfertBar::getId() {
    return _file->getId();
}

CustomQFile::Status TransfertBar::getStatus()
{
    return _file->getStatus();
}

void TransfertBar::mousePressEvent(QMouseEvent*)
{
    emit clicked(_file->getId());
}
