#include "element.h"
#include "ui_element.h"
#include "globalinfo.h"
#include "mimedatafile.h"
#include "filemanager.h"

#include <QAction>
#include <QPainter>
#include <QStyleOption>
#include <QList>
#include <QUrl>
#include <QFileDialog>

Element::Element(QString name, quint64 size, quint64 transferedSize, QString pathServer, QString pathClient, TypeElement typeElement, Status status, QWidget *parent) :
    QWidget(parent),
    StatsElement(name, size, transferedSize, pathServer, pathClient, typeElement, status),
    ui(new Ui::Element)
{
    ui->setupUi(this);
    ui->verticalLayout->setSpacing(2);
    ui->_title->setWordWrap(true);
    ui->_title->setAlignment(Qt::AlignCenter);

    _isSelected = false;

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

    QAction *downloadInA = new QAction("Telecharger vers ...");
    connect(downloadInA, &QAction::triggered, this, &Element::actionDownloadIn);

    _menu.addAction(deleteA);
    _menu.addAction(downloadA);
    _menu.addAction(downloadInA);
}

void Element::dropEvent( QDropEvent *event ) {
    qDebug("EVENT EVENT EVENT");
}

void Element::dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent) {
    qDebug("DROP MINE DATA");
}

void Element::dragEnterEvent(QDragEnterEvent *event) {
     qDebug("Drag enter Event");
     event->acceptProposedAction();
}

void Element::dragMoveEvent(QDragMoveEvent *event) {
    event->acceptProposedAction();
}

void Element::actionDelete(bool b) {
    qDebug("delete");
}

void Element::actionDownload(bool b) {
    qDebug("download");
}

void Element::actionDownloadIn(bool b) {
     //FileManager *fileManager = FileManager::getInstanceFileM();
     //fileManager->downloadFile(_path + "/" + _title, _size);
}

void Element::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        _dragStartPosition = event->pos();

        if (_isSelected == false)
            emit selected(this->getDataElement());
            setSelected(true);
    }
}

void Element::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
    }
}

DataElement Element::getDataElement() {
    DataElement dataElem;

    dataElem.image = _image;
    dataElem.name = _name;
    dataElem.path = _pathServer;
    dataElem.size = _sizeServer;

    return dataElem;
}

void Element::targetChangedSlot(QObject *newTarget) {
    qDebug("TARGET CHANGED");
    for (int i = 0 ; i < newTarget->dynamicPropertyNames().length() ; i++) {
        qDebug(newTarget->dynamicPropertyNames().at(i).toStdString().c_str());
    }
}

void Element::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - _dragStartPosition).manhattanLength()
         < QApplication::startDragDistance())
        return;

    emit isDragged();
}

void Element::dragLeaveEvent(QDragLeaveEvent *event)
{
    qDebug("TEST TEST TEST");
}

void Element::mouseDoubleClickEvent ( QMouseEvent * ) {
    emit hasBeenDoubleClicked(_name);
}

void Element::setTitle(QString str) {
//    ui->_title->setWordWrap(true);
    QFontMetrics metrics(ui->_title->font());
    ui->_title->setFixedSize(112, 40);

    QString elidedText = metrics.elidedText(str, Qt::ElideMiddle, ui->_title->width() * 2, Qt::TextWordWrap);

    ui->_title->setText(elidedText);
    ui->_title->setWordWrap(true);
}

void Element::setIcon(QPixmap picture) { // CUSTOM UNE CLASS ET FAIRE UN TRUC GENERIC, CE TRUC EST UTILISE PLUSIEUR FOIS
    int w = ui->_icon->width();
    int h = ui->_icon->height();

    _image = picture.scaled(w,h,Qt::KeepAspectRatio);

    ui->_icon->setMinimumSize(_image.width(), ui->_icon->height());
    ui->_icon->setPixmap(_image);
}

void Element::menuRequested(const QPoint & pos) {
    _menu.popup(mapToGlobal(pos));
}

void Element::setSelected(bool value) {
    if (value == true) {
        _isSelected = true;
        this->setStyleSheet("background-color:#" + Color::GlobalInfo::lightBlueSelection + "; border-radius:2px;");
    }
    else {
        _isSelected = false;
        this->setStyleSheet("");
    }
}

void Element::paintEvent(QPaintEvent *pe) {
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
