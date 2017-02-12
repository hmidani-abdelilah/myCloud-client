#include "generator.h"

Generator::Generator()
{

}

QString Generator::getFormatSize(qint64 size)
{
    if (size < 1000000)
        return QString::number((float)size / 1000) + " Ko";
    else if (size < 1000000000)
        return QString::number((float)size / 1000000) + "Mo";
    else
        return QString::number((float)size / 1000000000) + "Go";
}

QPixmap Generator::changeLogoColor(QPixmap pixmap, QString color) {
    QPainter painters (&pixmap);
    painters.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painters.fillRect(pixmap.rect(), QColor("#" + color));
    painters.end();

    return pixmap;
}
