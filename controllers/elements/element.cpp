#include "element.h"
#include "ui_element.h"
#include "globalinfo.h"
#include <QAction>

Element::Element(QString title, QPixmap icon, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Element)
{
    ui->setupUi(this);
    ui->verticalLayout->setSpacing(2);
    _title = title;

    ui->_title->setWordWrap(true);
    ui->_title->setAlignment(Qt::AlignCenter);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setCursor(Qt::PointingHandCursor);

    connect(this, &Element::customContextMenuRequested, this, &Element::menuRequested);
    configureRightClick();

    setIcon(icon);
    setTitle(title);

}

Element::~Element()
{
    delete ui;
}

void Element::configureRightClick() {
    QAction *deleteA = new QAction("Supprimer");
    connect(deleteA, &QAction::triggered, this, &Element::actionDelete);
    _menu.addAction(deleteA);
}

void Element::actionDelete(bool b) {
    qDebug("delete");
}

void Element::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        _dragStartPosition = event->pos();
}

void Element::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - _dragStartPosition).manhattanLength()
         < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    mimeData->setText("test");
    drag->setMimeData(mimeData);
    drag->setPixmap(_image);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
}

void Element::mouseDoubleClickEvent ( QMouseEvent * ) {
    emit hasBeenDoubleClicked(_title);
}

void Element::setTitle(QString str) {
    ui->_title->setWordWrap(true);
    QFontMetrics metrics(ui->_title->font());
    QString elidedText = metrics.elidedText(_title, Qt::ElideMiddle, ui->_title->width() * 2 - 30, Qt::TextWordWrap);
    ui->_title->setText(elidedText);
}

void Element::setIcon(QPixmap picture) {
    int w = ui->_icon->width();
    int h = ui->_icon->height();
    _image = picture.scaled(w,h,Qt::KeepAspectRatio);
    ui->_icon->setPixmap(_image);
}

void Element::menuRequested(const QPoint & pos) {
    _menu.popup(mapToGlobal(pos));
}

