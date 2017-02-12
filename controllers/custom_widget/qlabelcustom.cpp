#include <QPainter>

#include "qlabelcustom.h"
#include "generator.h"

QLabelCustom::QLabelCustom(const QString& text, QWidget* parent): QLabel(text, parent)
{

}

QLabelCustom::QLabelCustom(const QString& pathImg, int w, int h, QWidget* parent): QLabel(parent)
{
    this->createBtnImg(pathImg, w, h);
}

void QLabelCustom::createBtnImg(QString imgPath, int w, int h) {
    _image = QPixmap(imgPath);

    this->setPixmap(_image);
    this->setFixedSize(w, h);
    this->setScaledContents(true);
    this->setCursor(Qt::PointingHandCursor);
}

void QLabelCustom::mousePressEvent(QMouseEvent*)
{
    emit clicked();
}

void QLabelCustom::changeImageColor(QString color) {
    this->setPixmap(Generator::changeLogoColor(_image, color));
}
