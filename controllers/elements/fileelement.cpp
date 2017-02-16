#include "fileelement.h"
#include "ui_element.h"
#include "routeparams.h"

#include <QFileInfo>

FileElement::FileElement(QString name, qint64 size, qint64 transferedSize, QString pathServer, QString pathClient, Status status, QWidget *parent)
    : Element(name, size, transferedSize, pathServer, pathClient, TypeElement::FILE, status, parent)
{
    _fileRequest = new FileRequest();
    connect(_fileRequest, &FileRequest::signalReduce, this, &FileElement::responseReduceImage);
    getIcon();
}

FileElement::FileElement(Stats stats, QWidget *parent) : Element(stats, parent)
{
    _fileRequest = new FileRequest();
    connect(_fileRequest, &FileRequest::signalReduce, this, &FileElement::responseReduceImage);
    getIcon();
}

void FileElement::getIcon() {
    QFileInfo fileInfo(_name);
    QString suffix = fileInfo.suffix().toLower();
    RouteParams prms;

    QFile logo(":/elements/" + suffix);

    if (logo.exists()) {
        QIcon icon(":/elements/" + suffix);
        setIcon(icon.pixmap(100, 100));
    }
    else {
        prms.setParam("name", _name);
        prms.addQueryItem("pathServer", _pathServer);

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

void FileElement::setIcon(QPixmap picture) {
    _image = picture.scaled(_sizeIcon, Qt::KeepAspectRatio);

    ui->containerIcon->setFixedSize(_image.width() + 8, _image.height() + 8);
    ui->containerIcon->setStyleSheet("[accessibleName=\"containerIcon\"] {border-color:#" + Color::GlobalInfo::greyBorderElement + "; border-style:double; border-width:4px;}");
    ui->_icon->setPixmap(_image);
}
