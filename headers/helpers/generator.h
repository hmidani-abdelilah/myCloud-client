#ifndef GENERATOR_H
#define GENERATOR_H

#include <QString>
#include <QPainter>

class Generator
{
public:
    Generator();

public:
    static QString getFormatSize(qint64 size, int precision = 2);
    static QPixmap changeLogoColor(QPixmap pixmap, QString color);
    static QString getFormatSpeed(quint64 speed, int precision = 2);
};

#endif // GENERATOR_H
