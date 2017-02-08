#include "elementpath.h"

ElementPath::ElementPath(QString text, int pos) : QLabelCustom(text)
{
    _position = pos;
}

ElementPath::ElementPath(const QString &pathImg, int w, int h, int pos, QWidget *parent) : QLabelCustom(pathImg, w, h, parent)
{
    _position = pos;
}

void ElementPath::mousePressEvent(QMouseEvent*)
{
    emit clicked(_position);
}
