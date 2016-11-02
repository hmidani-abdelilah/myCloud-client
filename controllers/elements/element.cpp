#include "element.h"
#include "ui_element.h"
#include "globalinfo.h"
#include <QAction>
#include <QPainter>
#include <QStyleOption>

Element::Element(QString title, QWidget *parent) :
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

    //this->setContentsMargins(7, 7, 7, 7);

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
    if (event->button() == Qt::LeftButton) {
        _dragStartPosition = event->pos();
        emit clicked();
        setStyleSheetElementActive();
    }
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
//    ui->_title->setWordWrap(true);
    QFontMetrics metrics(ui->_title->font());
    ui->_title->setFixedSize(112, 40);

    QString elidedText = metrics.elidedText(str, Qt::ElideMiddle, ui->_title->width() * 2, Qt::TextWordWrap);

    ui->_title->setText(elidedText);
    ui->_title->setWordWrap(true);
}

void Element::setIcon(QPixmap picture) {
    int w = ui->_icon->width();
    int h = ui->_icon->height();

    _image = picture.scaled(w,h,Qt::KeepAspectRatio);

    ui->_icon->setMinimumSize(_image.width(), _image.height());
    ui->_icon->setPixmap(_image);
}

void Element::menuRequested(const QPoint & pos) {
    _menu.popup(mapToGlobal(pos));
}

void Element::setStyleSheetElementActive() {
    this->setStyleSheet("background-color:#" + Color::GlobalInfo::lightBlueSelection + "; border-radius:2px;");
}

void Element::paintEvent(QPaintEvent *pe) {
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

