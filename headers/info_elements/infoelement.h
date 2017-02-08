#ifndef INFOELEMENT_H
#define INFOELEMENT_H

#include "statselement.h"

#include <QFile>
#include <QTime>
#include <QMap>

class InfoElement : public QFile, public QTime, public StatsElement
{
    Q_OBJECT

public:
    enum TransfertType {
        UNDEFINED,
        UPLOAD,
        DOWNLOAD
    };

public:
    InfoElement(QString pathFile, QString name, QString pathClient, QString pathServer, Status status, qint64 size, qint64 id, TypeElement typeElement);

    inline qint64 id()  {return _id;}
    inline InfoElement::TransfertType type() {return _transfertType;}

    void setStatus(InfoElement::Status status);
    float getTransfertSpeed();

    virtual bool isFinish() = 0;
    virtual int getProgression() = 0;
    virtual qint64 getTransferedSize() = 0;
    virtual qint64 getSizeTransfering() = 0;
    void actualizeElementBySizeTranfered(int nbOctet);

signals:
    void statusHasChanged(qint64);

protected:
    qint64                         _id;
    qint64                         _sizeTransfered;
    TransfertType                   _transfertType;
    float                           _rangeTransfertSpeed;
    int                             _constRefreshSpeed;
    int                             _averageTransfertSize;
};

#endif // INFOELEMENT_H
