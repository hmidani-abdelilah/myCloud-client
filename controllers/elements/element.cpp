#include "element.h"
#include "ui_element.h"
#include "filemanager.h"

#include <QAction>
#include <QPainter>
#include <QStyleOption>
#include <QList>
#include <QUrl>
#include <QFileDialog>
#include <QApplication>
#include <QPainter>
#include <QBitmap>

Element::Element(QString name, qint64 size, qint64 transferedSize, QString pathServer, QString pathClient, TypeElement typeElement, Status status, QWidget *parent) :
    QWidget(parent),
    StatsElement(name, size, transferedSize, pathServer, pathClient, typeElement, status),
    ui(new Ui::Element)
{
    ui->setupUi(this);
    ui->verticalLayout->setSpacing(2);
    ui->_title->setWordWrap(true);
    ui->_title->setAlignment(Qt::AlignCenter);

    _draggableMode = EMIT;
    _isSelected = false;
    _sizeIcon = QSize(60, 60);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setCursor(Qt::PointingHandCursor);
    connect(this, &Element::customContextMenuRequested, this, &Element::menuRequested);
    configureRightClick();
    setAcceptDrops(true);

    setTitle(name);
}

Element::Element(StatsElement::Stats stats, QWidget *parent) :
    QWidget(parent),
    StatsElement(),
    ui(new Ui::Element)
{
    ui->setupUi(this);
    ui->verticalLayout->setSpacing(2);

    setStats(stats);

    ui->_title->setWordWrap(true);
    ui->_title->setAlignment(Qt::AlignCenter);

    _isSelected = false;

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setCursor(Qt::PointingHandCursor);
    connect(this, &Element::customContextMenuRequested, this, &Element::menuRequested);
    configureRightClick();
    setAcceptDrops(true);

    setTitle(_name);
}

Element::~Element()
{
    delete ui;
}

void Element::configureRightClick() {
    QAction *deleteA = new QAction("Supprimer");
    connect(deleteA, &QAction::triggered, this, &Element::actionDelete);

    QAction *downloadA = new QAction("Telecharger");
    connect(downloadA, &QAction::triggered, this, &Element::actionDownload);

    _menu.addAction(deleteA);
    _menu.addAction(downloadA);
}

void Element::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}

void Element::dragMoveEvent(QDragMoveEvent *event) {
    event->acceptProposedAction();
}

void Element::actionDelete(bool) {
    emit isDeleted();
}

void Element::actionDownload(bool) {
    emit isDragged();
}

void Element::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        _dragStartPosition = event->pos();
        if (_isSelected == false) {
            emit selected(this->stats());
            setSelected(true);
        }
        else if (QApplication::keyboardModifiers() == Qt::ControlModifier  || QApplication::keyboardModifiers() == Qt::ShiftModifier) {
            setSelected(!_isSelected);
            if (_isSelected == true)
                emit selected(this->stats());
            else
                emit unselected(this->stats());
        }
    }
}

void Element::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
    }
}

void Element::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton) || QApplication::keyboardModifiers() != Qt::NoModifier)
        return;
    if (_draggableMode == DISABLE)
        return;
    if ((event->pos() - _dragStartPosition).manhattanLength()
            < QApplication::startDragDistance())
        return;

    switch (_draggableMode) {
    case NORMAL: {
//        QDrag *drag = new QDrag(this);
//        drag->setDragCursor(QPixmap(":/logo/cloud2"), Qt::MoveAction);
//        QMimeData *mimeData = new QMimeData;
//        QString pathServer = "";
//        drag->setPixmap(_image);
//        if (this->_pathServer.length() > 0) {
//            pathServer = this->pathServer() + "/";
//        }
//        mimeData->setData("text/plain", QByteArray(QString(pathServer + this->_name).toStdString().c_str()));
//        drag->setMimeData(mimeData);
//        drag->exec(Qt::MoveAction);
        break;
    }
    default:
        break;
    }
    emit isDragged();
}

void Element::mouseDoubleClickEvent ( QMouseEvent * ) {
    emit hasBeenDoubleClicked(_name);
}

void Element::setTitle(QString str) {
    QFontMetrics metrics(ui->_title->font());
    ui->_title->setFixedSize(112, 40);

    QString elidedText = metrics.elidedText(str, Qt::ElideMiddle, ui->_title->width() * 2, Qt::TextWordWrap);

    ui->_title->setText(elidedText);
    ui->_title->setWordWrap(true);
}

void Element::setIcon(QPixmap picture) { // CUSTOM UNE CLASS ET FAIRE UN TRUC GENERIC, CE TRUC EST UTILISE PLUSIEUR FOIS
    _image = picture.scaled(_sizeIcon, Qt::KeepAspectRatio);

    ui->containerIcon->setFixedSize(_image.width() + 8, _image.height() + 8);
    ui->_icon->setPixmap(_image);
}

void Element::menuRequested(const QPoint & pos) {
    _menu.popup(mapToGlobal(pos));
}

void Element::setSelected(bool value) {
    if (value == true) {
        _isSelected = true;
        this->setStyleSheet("background-color:#" + Color::GlobalInfo::lightBlueSelection + "; border-radius:2px");
    }
    else {
        _isSelected = false;
        this->setStyleSheet("");
    }
}

void Element::paintEvent(QPaintEvent *) {
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
