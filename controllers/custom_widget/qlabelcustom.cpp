#include <QPainter>

#include "qlabelcustom.h"
#include "generator.h"

QLabelCustom::QLabelCustom(QWidget* parent): QLabel(parent)
{

}

QLabelCustom::QLabelCustom(const QString& text, QWidget* parent): QLabel(text, parent)
{

}

QLabelCustom::QLabelCustom(const QString& pathImg, int w, int h, QWidget* parent): QLabel(parent)
{
    this->createBtnImg(pathImg, w, h);
}

QLabelCustom::QLabelCustom(const QPixmap img, int w, int h, QWidget* parent): QLabel(parent)
{
    this->createBtnImg(img, w, h);
}

void QLabelCustom::createBtnImg(QPixmap img, int w, int h) {
    _image = img;

    this->setPixmap(_image);
    this->setFixedSize(w, h);
    this->setScaledContents(true);
    this->setCursor(Qt::PointingHandCursor);
}

void QLabelCustom::createBtnImg(QString imgPath, int w, int h) {
    _image = QPixmap(imgPath);

    this->setPixmap(_image);
    this->setFixedSize(w, h);
    this->setScaledContents(true);
    this->setCursor(Qt::PointingHandCursor);
}

void QLabelCustom::mousePressEvent(QMouseEvent* ev)
{
    const QPoint p = this->mapTo(this->window(), ev->pos());

    emit clicked();
    emit clickedPos(p);
}

void QLabelCustom::changeImageColor(QString color) {
    this->setPixmap(Generator::changeLogoColor(_image, color));
}
