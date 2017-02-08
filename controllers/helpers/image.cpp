#include "image.h"

Image::Image()
{

}

QPixmap Image::fromSvgToPixmap(const QSize &imageSize, const QString &svgFile)
{
    QSvgRenderer renderer(svgFile);
    QImage image(imageSize.width(), imageSize.height(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    renderer.render(&painter);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.end();

    return QPixmap::fromImage(image);
}
