#ifndef DOWNLOADELEMENT_H
#define DOWNLOADELEMENT_H

#include <QCryptographicHash>
#include "infoelement.h"

class DownloadElement : public InfoElement
{
public:
    DownloadElement(QString pathFile, QString name, QString pathClient, QString pathServer, QString status, quint64 size, quint64 id);

public:
    inline quint64 getTransferedSize() {return this->size();}
    int getProgression();
    bool isFinish();

    quint64 getSizeTransfering();
};

#endif // DOWNLOADELEMENT_H
