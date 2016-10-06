#ifndef LINEEDITCUSTOM_H
#define LINEEDITCUSTOM_H

#include <QLineEdit>

class LineEditCustom : public QLineEdit
{
public:

    LineEditCustom(QWidget *parent = 0);
    ~LineEditCustom() {}
    virtual void focusInEvent(QFocusEvent *);
    virtual void focusOutEvent(QFocusEvent *);
    void changeTextColor(QString color);

private:
    bool _placeHolder;
    QString savPlaceHolder;
};

#endif // LINEEDITCUSTOM_H
