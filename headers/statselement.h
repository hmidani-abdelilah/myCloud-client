#ifndef STATSELEMENT_H
#define STATSELEMENT_H

#include <QString>

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
        const QString     &name;
        const quint64     &size;
        const quint64     &transferedSize;
        const QString     &pathServer;
        const QString     &pathClient;
        const TypeElement &typeElement;
        const Status      &status;
        Stats(const QString &name, const quint64 &size, const quint64 &transferedSize, const QString &pathServer, const QString &pathClient, const TypeElement &typeElement, const Status &status)
        : name(name), size(size), transferedSize(transferedSize), pathServer(pathServer), pathClient(pathClient), typeElement(typeElement), status(status) {}
    };

    StatsElement(QString name = "", quint64 size = 0, quint64 transferedSize = 0, QString pathServer = "undefined", QString pathClient = "undefined", TypeElement type = TypeElement::UNDEFINED, Status status = Status::NONE);
    ~StatsElement() {}

    inline const QString name() {return _name;}
    inline quint64 sizeServer() {return _sizeServer;}
    inline quint64 transferedSize() {return _transferedSize;}
    inline const QString pathServer() {return _pathServer;}
    inline const QString pathClient() {return _pathClient;}
    inline Status status() {return _status;}
    inline TypeElement typeElement() {return _typeElement;}

    const Stats *stats();
    bool setStats(Stats *stats);

    static QString convertStatusToString(StatsElement::Status status);
    static StatsElement::Status convertStringToStatus(QString status);

protected:
    QString     _name;
    quint64     _sizeServer; // size total
    quint64     _transferedSize; // size transfered
    QString     _pathServer;
    QString     _pathClient;
    TypeElement _typeElement;
    Status      _status;
    const Stats *_stats;

private:
    bool isInitialize();
    void setStats(QString name, quint64 size, quint64 transferedSize, QString pathServer, QString pathClient, TypeElement typeElement, Status status);
};

#endif // STATSELEMENT_H
