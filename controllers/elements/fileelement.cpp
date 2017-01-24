#include "fileelement.h"
#include "ui_element.h"
#include "routeparams.h"

#include <QFileInfo>

FileElement::FileElement(QString title, quint64 size, QString path, QWidget *parent) : Element(title, size, path, Element::FILE, parent)
{
    _fileRequest = new FileRequest();
    connect(_fileRequest, &FileRequest::signalReduce, this, &FileElement::responseReduceImage);
    getIcon();
}

void FileElement::getIcon() {
    QFileInfo fileInfo(_title);
    QString suffix = fileInfo.suffix().toLower();
    RouteParams prms;

    QFile logo(":/elements/" + suffix);

    if (logo.exists()) {
        QIcon icon(":/elements/" + suffix);
        setIcon(icon.pixmap(100, 100));
    }
    else {
        prms.setParam("name", _title);
        _fileRequest->request(FileRequest::Type::GET, FileRequest::File::Reduce, prms);
    }
}

void FileElement::responseReduceImage(QNetworkReply *reply) {
    if (reply->error() != 0)
    {
        qDebug("Il y a eu une erreur lors de la recuperation de la petite image %d", reply->error());
        return ;
    }

    QPixmap icon;
    QByteArray data = reply->readAll();

    if (data.length() > 0)
        icon.loadFromData(data);
    else
        icon.load(":/elements/file");
    setIcon(icon);
}
