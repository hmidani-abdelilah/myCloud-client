#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <QWebSocket>
#include <QFile>
#include <QMessageBox>

class SocketManager : public QWebSocket
{
public :
    enum Route {
        SENDFILE
    };

    enum SocketType {
        WRITE,
        READ
    };

private:
    SocketManager();

    QMap<Route, QMap<QString, SocketManager::SocketType>> _infoRoute;
    QMap<SocketType, QWebSocket *> _listSocket;

    static SocketManager *_instanceSocketManager;
    QWidget _parent;
    int _bufferSize;
    void configureRoute();

    QMap<QString, SocketManager::SocketType> createMapInfoRoute(QString string, SocketManager::SocketType type);
public:
    static SocketManager *getInstanceSocketM();
    void open(Route route);
    QWebSocket *getWebSocket(Route route);
    void setBufferSize(int bufferSize);
    int getBufferSize();

protected slots:
    void bytesWritten(qint64 bytes);
    void errorTest(QAbstractSocket::SocketError socketError);
};

#endif // SOCKETMANAGER_H
