#ifndef ELEMENTPATH_H
#define ELEMENTPATH_H

#include "qlabelcustom.h"
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>

class ElementPath : public QLabelCustom
{
    Q_OBJECT
public:
    ElementPath(QString text, int pos);
    ElementPath(const QString& pathImg, int w, int h, int pos, QWidget* parent = 0);

private:
    int _position;

protected:
    virtual void mousePressEvent(QMouseEvent*);

signals:
    void clicked(int);
};

#endif // ELEMENTPATH_H
