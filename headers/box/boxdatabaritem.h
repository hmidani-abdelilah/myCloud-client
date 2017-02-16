#ifndef BOXDATABARITEM_H
#define BOXDATABARITEM_H

#include "qlabelcustom.h"

#include <QHBoxLayout>
#include <QPixmap>
#include <QString>

class BoxDataBarItem : public QWidget
{
public:

    enum TypeUnit {
        SPEED,
        DIGITAL_STORAGE
    };

    BoxDataBarItem(QString picture, QString longTitle, QString title = "");
    void setValue(TypeUnit type, qint64 size, int nbItem = 0);
    inline QString longTitle() {return _longTitle;}

protected:
    QString         _title;
    QString         _longTitle;

    int             _size;
    int             _nbItem;

    QLabel *_titleLabel;
    QLabel *_sizeLabel;
};

#endif // BOXDATABARITEM_H
