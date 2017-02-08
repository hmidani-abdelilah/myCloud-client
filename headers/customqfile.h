#ifndef UploadElement_H
#define UploadElement_H

#include <QFile>
#include <QTime>
#include <QMap>

class UploadElement : public QFile, public QTime
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

public :
    UploadElement();
    UploadElement(QString pathFile);
    UploadElement(QString pathFile, QString name, QString pathClient, QString pathServer, QString status, qint64 size, qint64 id, qint64 octetAlreadyTransfert, QString transfertType);

    inline qint64 getSize() {return _size;}
    inline qint64 getId() {return _id;}
    inline QString getNameFile() {return _name;}
    inline qint64 getTransferedSize() {return _sizeTransfered;}
    inline QString getPathServer() {return _pathServer;}
    inline InfoElement::Status getStatus() {return _status;}

    inline void setNameFile(QString name) {_name = name;}
    inline void setSize(qint64 size) {_size = size;}
    inline void setId(qint64 id) {_id = id;}

    void setOctetsTransfered(int nbOctet);
    void setStatus(InfoElement::Status status);
    void setPathServer(QString pathServer);
    void setPathClient(QString pathClient);

    float getTransfertSpeed();
    int   getProgression();

    static QString convertStatusToString(InfoElement::Status status);
    static InfoElement::Status convertStringToStatus(QString status);
    bool isFinish();

    TransfertType type();

signals:
    void statusHasChanged(qint64);

private:
    qint64                         _id;
    Status                          _status;
    qint64                         _size;
    QString                         _name;
    qint64                         _sizeTransfered;
    QString                         _pathServer;
    QString                         _pathClient;
    TransfertType                   _transfertType;
    QMap<QString, TransfertType>    _transfertTypeRef;
    float                           _rangeTransfertSpeed;
    int                             _constRefreshSpeed;
    int                             _averageTransfertSize;
};

#endif // UploadElement_H
