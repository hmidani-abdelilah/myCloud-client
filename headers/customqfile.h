#ifndef CUSTOMQFILE_H
#define CUSTOMQFILE_H

#include <QFile>
#include <QTime>

class CustomQFile : public QFile, public QTime
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

public :
    CustomQFile();
    CustomQFile(QString pathFile);
    CustomQFile(QString pathFile, QString name, QString pathClient, QString pathServer, QString status, quint64 size, quint64 id, quint64 octetAlreadyTransfert);

    inline quint64 getSize() {return _size;}
    inline quint64 getId() {return _id;}
    inline QString getNameFile() {return _name;}
    inline quint64 getTransferedSize() {return _sizeUpload;}
    inline QString getPathServer() {return _pathServer;}
    inline CustomQFile::Status getStatus() {return _status;}

    inline void setNameFile(QString name) {_name = name;}
    inline void setSize(quint64 size) {_size = size;}
    inline void setId(quint64 id) {_id = id;}

    void setOctetsSentToServer(int nbOctet);
    void setStatus(CustomQFile::Status status);
    void setPathServer(QString pathServer);
    void setPathClient(QString pathClient);

    float getUploadSpeed();
    int   getProgression();

    static QString convertStatusToString(CustomQFile::Status status);
    static CustomQFile::Status convertStringToStatus(QString status);
    bool isFinish();

signals:
    void statusHasChanged(quint64);

private:
    quint64     _id;
    Status      _status;
    quint64     _size;
    QString     _name;
    quint64     _sizeUpload;
    QString     _pathServer;
    QString     _pathClient;
    float       _rangeUploadSpeed;
    int         _constRefreshSpeed;
    int         _averageUploadSize;

};

#endif // CUSTOMQFILE_H
