#ifndef DOWNLOADELEMENT_H
#define DOWNLOADELEMENT_H

#include <QCryptographicHash>
#include "infoelement.h"

class DownloadElement : public InfoElement
{
public:
    DownloadElement(QString pathFile, QString name, QString pathClient, QString pathServer, Status status, qint64 size, qint64 id, TypeElement typeElement);

public:
    inline qint64 getTransferedSize() {return this->size();}
    int getProgression();
    bool isFinish();

    qint64 getSizeTransfering();
};

#endif // DOWNLOADELEMENT_H
