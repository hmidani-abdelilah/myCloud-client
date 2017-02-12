#ifndef GENERATOR_H
#define GENERATOR_H

#include <QString>
#include <QPainter>

class Generator
{
public:
    Generator();

public:
    static QString getFormatSize(qint64 size);
    static QPixmap changeLogoColor(QPixmap pixmap, QString color);
};

#endif // GENERATOR_H
