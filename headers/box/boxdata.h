#ifndef BOXDATA_H
#define BOXDATA_H

#include "box.h"

class BoxData : public Box
{
public:
    BoxData(QString title);

    void setValueBarItem(QString name, qint64 size, int nbItem);

private:
    QVBoxLayout *_vLayout;
};

#endif // BOXDATA_H
