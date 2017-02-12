#ifndef FACTORYBUTTON_H
#define FACTORYBUTTON_H

#include <QPixmap>

#include "qpushbuttoncustom.h"

class FactoryButton
{
private:
    QPushButtonCustom *_btn;

public:
    FactoryButton(QString title);

    FactoryButton size(QSize sizeButton);
    FactoryButton icon(QString icon, QSize iconSize);
    FactoryButton font(QFont font);
    QPushButtonCustom *gen();
};

#endif // FACTORYBUTTON_H
