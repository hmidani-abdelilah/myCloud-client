#ifndef STATSELEMENT_H
#define STATSELEMENT_H

#include <QString>
#include <QPixmap>

class StatsElement
{
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

    enum TypeElement {
        UNDEFINED,
        FILE,
        FOLDER
    };

    struct Stats {
        QString     name;
        qint64     size;
        qint64     transferedSize;
        QString     pathServer;
        QString     pathClient;
        TypeElement typeElement;
        Status      status;
        QPixmap     image;
        Stats()
            : name(""), size(0), transferedSize(0), pathServer("undefined"), pathClient("undefined"), typeElement(TypeElement::UNDEFINED), status(Status::NONE), image(QPixmap()) {}
        Stats(QString name, QString pathServer)
            : name(name), size(0), transferedSize(0), pathServer(pathServer), pathClient("undefined"), typeElement(TypeElement::UNDEFINED), status(Status::NONE), image(QPixmap()) {}
        Stats(QString name, qint64 size, qint64 transferedSize, QString pathServer, QString pathClient, TypeElement typeElement, Status status, QPixmap image)
        : name(name), size(size), transferedSize(transferedSize), pathServer(pathServer), pathClient(pathClient), typeElement(typeElement), status(status), image(image) {}
    };

    StatsElement(QString name = "", qint64 size = 0, qint64 transferedSize = 0, QString pathServer = "undefined", QString pathClient = "undefined", TypeElement type = TypeElement::UNDEFINED, Status status = Status::NONE);
    ~StatsElement() {}

    inline const QString name() {return _name;}
    inline qint64 sizeServer() {return _sizeServer;}
    inline qint64 transferedSize() {return _transferedSize;}
    inline const QString pathServer() {return _pathServer;}
    inline const QString pathClient() {return _pathClient;}
    inline Status status() {return _status;}
    inline TypeElement typeElement() {return _typeElement;}

    StatsElement::Stats stats();
    bool setStats(Stats stats);

    static QString convertStatusToString(StatsElement::Status status);
    static StatsElement::Status convertStringToStatus(QString status);

protected:
    QString     _name;
    qint64     _sizeServer; // size total
    qint64     _transferedSize; // size transfered
    QString     _pathServer;
    QString     _pathClient;
    TypeElement _typeElement;
    Status      _status;
    QPixmap     _image;

private:
    bool isInitialize();
    void setStats(QString name, qint64 size, qint64 transferedSize, QString pathServer, QString pathClient, TypeElement typeElement, Status status);
};

#endif // STATSELEMENT_H
