#ifndef GENERATOR_H
#define GENERATOR_H

#include <QString>

class Generator
{
public:
    Generator();

public:
    static QString getFormatSize(quint64 size);
};

#endif // GENERATOR_H
