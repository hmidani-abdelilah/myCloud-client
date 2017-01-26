#include "transfertbar.h"
#include "globalinfo.h"
#include "generator.h"

#include <QPushButton>
#include <QSpacerItem>
#include <QStyleOption>
#include <QPainter>

TransfertBar::TransfertBar(InfoElement *file) : QWidget()
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

    switch (file->type()) {
    case InfoElement::UPLOAD:
        _iconStatus = new QLabelCustom(":/logo/downloadFinish", 16, 16);
        break;
    case InfoElement::DOWNLOAD:
        _iconStatus = new QLabelCustom(":/logo/cloud_download", 16, 16);
        break;
    default:
        // TODO : Throw an exeption
        break;
    }

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

    setName(_file->name());
    setSize(_file->sizeServer());
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
    _transferedSize->setText(Generator::getFormatSize(size));
}

void TransfertBar::setSpeed() { // set speed with syntax ( ie: 2 mo/s)
    _speed = _file->getTransfertSpeed();

    if (_speed < 1000) {
        _speedLabel->setText(QString::number(_speed) + " Ko/s");
    }
    else
        _speedLabel->setText(QString::number(_speed / 1000) + " Mo/s");
}

void TransfertBar::setSize(quint64 size) {
    _size->setText(Generator::getFormatSize(size));
}

void TransfertBar::setTime() {
    int secondToWait = 0;
    if (!_file->isFinish() && _speed > 0)
        secondToWait = qRound(((float)(_file->sizeServer() - _sizeTransfered)) / (_speed * 1000));

    _time->setHMS(0, 0, secondToWait);
    _labelTime->setText(_time->toString());
}

void TransfertBar::setStatus() {
    _statusLabel->setText(InfoElement::convertStatusToString(_file->status()));

    switch (_file->status()) {
    case InfoElement::Status::FINISH: {
        _iconStatus->changeImageColor("1BB71E");
        break;
    }
    case InfoElement::Status::PAUSE: {
        _iconStatus->changeImageColor("FFD400");
        break;
    }
    case InfoElement::Status::EN_COURS: {
        _iconStatus->changeImageColor("329ED1");
        break;
    }
    case InfoElement::Status::DELETE: {
        break;

    }
    case InfoElement::Status::ERROR_CLIENT_PATH: {
        _iconStatus->changeImageColor("F45342");
        break;
    }
    }
}

void TransfertBar::changeStatusOfFile(InfoElement::Status status) {
    _file->setStatus(status);
    _statusLabel->setText(InfoElement::convertStatusToString(status));
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

quint64 TransfertBar::id() {
    return _file->id();
}

InfoElement::Status TransfertBar::status()
{
    return _file->status();
}

void TransfertBar::mousePressEvent(QMouseEvent*)
{
    emit clicked(_file->id());
}
