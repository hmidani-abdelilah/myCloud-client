#ifndef DISPLAYPATH_H
#define DISPLAYPATH_H

#include "qlabelcustom.h"

#include <QHBoxLayout>

class DisplayPath : public QHBoxLayout
{
    Q_OBJECT
public:
    DisplayPath();

public slots:
    void addElement(QString element);
    void deleteLastElement();

private slots:
    void onClickElement(int pos);

signals:
    void pathChanged(QStringList);
};

#endif // DISPLAYPATH_H
