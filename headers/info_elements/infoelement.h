#ifndef INFOELEMENT_H
#define INFOELEMENT_H

#include <QFile>
#include <QTime>
#include <QMap>

class InfoElement : public QFile, public QTime
{
    Q_OBJECT

public:
    enum Status {
        NONE,
        EN_COURS,
        PAUSE,
        DELETE,
        FINISH,
        ERROR_CLIENT_PATH,
        ERROR
    };

    enum TransfertType {
        UNDEFINED,
        UPLOAD,
        DOWNLOAD
    };

public:
    InfoElement(QString pathFile, QString name, QString pathClient, QString pathServer, QString status, quint64 size, quint64 id);

    inline quint64 getSize() {return _size;}
    inline quint64 getId() {return _id;}
    inline QString getNameFile() {return _name;}
    inline QString getPathServer() {return _pathServer;}
    inline InfoElement::Status getStatus() {return _status;}
    inline InfoElement::TransfertType type() {return _transfertType;}

    inline void setNameFile(QString name) {_name = name;}
    inline void setSize(quint64 size) {_size = size;}
    inline void setId(quint64 id) {_id = id;}

    static QString convertStatusToString(InfoElement::Status status);
    static InfoElement::Status convertStringToStatus(QString status);

    void setStatus(InfoElement::Status status);
    float getTransfertSpeed();

    virtual bool isFinish() = 0;
    virtual int getProgression() = 0;
    virtual quint64 getTransferedSize() = 0;
    virtual quint64 getSizeTransfering() = 0;
    void actualizeElementBySizeTranfered(int nbOctet);

signals:
    void statusHasChanged(quint64);

protected:
    quint64                         _id;
    Status                          _status;
    quint64                         _size;
    QString                         _name;
    quint64                         _sizeTransfered;
    QString                         _pathServer;
    QString                         _pathClient;
    TransfertType                   _transfertType;
    float                           _rangeTransfertSpeed;
    int                             _constRefreshSpeed;
    int                             _averageTransfertSize;
};

#endif // INFOELEMENT_H
