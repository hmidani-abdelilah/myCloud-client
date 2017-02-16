#ifndef BOXTRANFERT_H
#define BOXTRANFERT_H

#include "box.h"

class BoxTranfert : public Box
{
public:
    BoxTranfert(QString title);
    void setValueBarItem(QString name, qint64 size);

private:
    QVBoxLayout *_vLayout;
};

#endif // BOXTRANFERT_H
