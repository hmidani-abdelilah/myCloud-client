#ifndef UPLOADELEMENT_H
#define UPLOADELEMENT_H

#include "infoelement.h"

class UploadElement : public InfoElement
{
public:
    UploadElement(QString pathFile, QString name, QString pathClient, QString pathServer, Status status, quint64 size, quint64 id, quint64 octetAlreadyTransfered);

    inline quint64 getTransferedSize() {return _sizeTransfered;}

    int getProgression();
    bool isFinish();
    void setOctetsTransfered(int nbOctet);
    quint64 getSizeTransfering();
};

#endif // UPLOADELEMENT_H
