#include "socketmanager.h"

SocketManager *SocketManager::_instanceSocketManager = 0;

SocketManager::SocketManager() : QWebSocket()
{
    _listSocket.insert(SocketType::READ, new QWebSocket());
    _listSocket.insert(SocketType::WRITE, new QWebSocket());

    _bufferSize = 8000;

    configureRoute();

    // les erreurs ne marche pas, bizarre
    for (QMap<SocketType, QWebSocket *>::iterator it = _listSocket.begin(); it != _listSocket.end() ; ++it)
        connect(it.value(), static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error), this, &SocketManager::errorTest);
}

QWebSocket *SocketManager::getWebSocket(Route route) {
    return _listSocket[_infoRoute[route].first()];
}

int SocketManager::getBufferSize () {
    return _bufferSize;
}

void SocketManager::setBufferSize (int bufferSize) {
    _bufferSize = bufferSize;
}

QMap<QString, SocketManager::SocketType> SocketManager::createMapInfoRoute(QString string, SocketManager::SocketType type) {
    QMap<QString, SocketManager::SocketType> map;
    map.insert(string, type);
    return map;
}

void SocketManager::configureRoute() {
    _infoRoute.insert(Route::SENDFILE, createMapInfoRoute(QString("ws://127.0.0.1:3000/api/file/writefile"), SocketType::WRITE));
}

void SocketManager::open(Route route) {
    _listSocket[_infoRoute[route].first()]->open(QUrl(_infoRoute[route].firstKey()));
}

SocketManager *SocketManager::getInstanceSocketM()
{
    if (!_instanceSocketManager)
        _instanceSocketManager = new SocketManager;
    return _instanceSocketManager;
}

void SocketManager::errorTest(QAbstractSocket::SocketError socketError) {
    qDebug("ERROR");
    QMessageBox msgBox;
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        msgBox.setText(tr("Fortune Client"));
        msgBox.setInformativeText(tr("The host was not found. Please check the "
                                     "host name and port settings."));
        msgBox.exec();
        break;
    case QAbstractSocket::ConnectionRefusedError:
        msgBox.setText(tr("Fortune Client"));
        msgBox.setInformativeText(tr("The connection was refused by the peer. "
                                     "Make sure the fortune server is running, "
                                     "and check that the host name and port "
                                     "settings are correct."));
        msgBox.exec();
        break;
    default:
        msgBox.setText(tr("Fortune Client"));
        msgBox.setInformativeText(tr("The following error occurred: %1.")
                                  .arg(this->errorString()));
        msgBox.exec();
    }
}
