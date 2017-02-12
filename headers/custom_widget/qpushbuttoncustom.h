#ifndef QPUSHBUTTONCUSTOM_H
#define QPUSHBUTTONCUSTOM_H

#include <QPushButton>

class QPushButtonCustom : public QPushButton
{
public:
    QPushButtonCustom(QString title);
protected:
    void leaveEvent(QEvent *);
    void enterEvent(QEvent *);
};

#endif // QPUSHBUTTONCUSTOM_H
