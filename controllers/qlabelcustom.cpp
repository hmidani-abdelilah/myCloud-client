#include "qlabelcustom.h"

QLabelCustom::QLabelCustom(const QString& text, QWidget* parent): QLabel(text, parent)
{

}

QLabelCustom::QLabelCustom(const QString& pathImg, int w, int h, QWidget* parent): QLabel(parent)
{
    this->createBtnImg(pathImg, w, h);
}

void QLabelCustom::createBtnImg(QString imgPath, int w, int h) {
    QPixmap image(imgPath);

    this->setPixmap(image);
    this->setFixedSize(w, h);
    this->setScaledContents(true);
    this->setCursor(Qt::PointingHandCursor);
}

void QLabelCustom::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}
