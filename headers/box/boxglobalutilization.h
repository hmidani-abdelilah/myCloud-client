#ifndef BOXGLOBALUTILIZATION_H
#define BOXGLOBALUTILIZATION_H

#include "box.h"

#include <QLabel>
#include <QProgressBar>

class BoxGlobalUtilization : public Box
{
public:
    BoxGlobalUtilization(QString title);

    void setUsedSize(qint64 sizeUsed);
    void setFreeSize(qint64 sizeFree);
    void setProgressBarValue(int value);
private:
    QLabel  *_usedSize;
    QLabel  *_sizeFree;
    QProgressBar  *_progressBar;
};

#endif // BOXGLOBALUTILIZATION_H
