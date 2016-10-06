#ifndef CUSTOMQFILE_H
#define CUSTOMQFILE_H

#include <QFile>
#include <QTime>

class CustomQFile : public QFile, public QTime
{
public :
    CustomQFile(QString nameFile);

    inline quint64 getSize() {return _size;}
    inline QString getId() {return _id;}
    inline QString getStatus() {return _status;}
    inline QString getNameFile() {return _name;}
    inline quint64 getTransferedSize() {return _sizeUpload;}

    inline void setNameFile(QString name) {_name = name;}
    inline void setSize(quint64 size) {_size = size;}
    inline void setId(QString id) {_id = id;}
    inline void setStatus(QString status) {_status = status;}

    float   getUploadSpeed();
    int     getProgression();

public:
    CustomQFile();

    void setOctetsSentToServer(int nbOctet);
private:
    QString     _id;
    QString     _status;
    quint64      _size;
    QString     _name;
    quint64      _sizeUpload;

    float       _rangeUploadSpeed;
    int         _constRefreshSpeed;
    int         _averageUploadSize;
};

#endif // CUSTOMQFILE_H
