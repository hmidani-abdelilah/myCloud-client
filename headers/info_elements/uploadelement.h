#ifndef UPLOADELEMENT_H
#define UPLOADELEMENT_H

#include "infoelement.h"

class UploadElement : public InfoElement
{
public:
    UploadElement(QString pathFile, QString name, QString pathClient, QString pathServer, Status status, qint64 size, qint64 id, qint64 octetAlreadyTransfered, TypeElement typeElement);

    inline qint64 getTransferedSize() {return _sizeTransfered;}

    int getProgression();
    bool isFinish();
    void setOctetsTransfered(int nbOctet);
    qint64 getSizeTransfering();
};

#endif // UPLOADELEMENT_H
