#ifndef IMAGE_H
#define IMAGE_H

#include <QSvgRenderer>
#include <QPainter>
#include <QString>

class Image
{
public:
    Image();

public:
    static
    QPixmap fromSvgToPixmap(const QSize &imageSize, const QString &svgFile);
};

#endif // IMAGE_H
