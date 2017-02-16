#include "generator.h"

Generator::Generator()
{

}

QString Generator::getFormatSize(qint64 size, int precision)
{
    if (size < 1000000)
        return QString::number((float)size / 1000, 'f', precision) + " Ko";
    else if (size < 1000000000)
        return QString::number((float)size / 1000000, 'f', precision) + " Mo";
    else
        return QString::number((float)size / 1000000000, 'f', precision) + " Go";
}

QString Generator::getFormatSpeed(quint64 speed, int precision) {
    if (speed < 1000) {
        return (QString::number((float)speed, 'f', precision) + " Ko/s");
    }
    else
        return (QString::number((float)speed / 1000, 'f', precision) + " Mo/s");
}

QPixmap Generator::changeLogoColor(QPixmap pixmap, QString color) {
    QPainter painters (&pixmap);
    painters.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painters.fillRect(pixmap.rect(), QColor("#" + color));
    painters.end();

    return pixmap;
}
