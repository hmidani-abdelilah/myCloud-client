#ifndef LINEEDITCUSTOM_H
#define LINEEDITCUSTOM_H

#include <QLineEdit>

class LineEditCustom : public QLineEdit
{
public:

    LineEditCustom(QWidget *parent = 0);
    ~LineEditCustom() {}

private:
    QString savPlaceHolder;
};

#endif // LINEEDITCUSTOM_H
