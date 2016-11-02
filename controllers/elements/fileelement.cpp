#include "fileelement.h"
#include "ui_element.h"

#include <QFileInfo>

FileElement::FileElement(QString title, QWidget *parent) : Element(title, parent)
{
    QFileInfo fi("/tmp/archive.tar.gz");


    _requestReduceImage = new FileRequest();
    connect(_requestReduceImage, &FileRequest::finished, this, &FileElement::responseReduceImage);
    //setIcon(QPixmap(":/elements/file"));
    getIcon();
}

void FileElement::getIcon() {
    QFileInfo fileInfo(_title);
    QString suffix = fileInfo.suffix();

    _requestReduceImage->request(FileRequest::Type::GET, FileRequest::File::Reduce);

//    if (suffix == "PNG") {

//    }
//    else {
//        setIcon(QPixmap(":/elements/file"));
//    }

}

void FileElement::responseReduceImage(QNetworkReply *reply) {
    if (reply->error() != 0)
    {
        qDebug("Il y a eu une erreur lors de la recuperation de la petite image %d", reply->error());
        return ;
    }

    QPixmap icon;
    icon.loadFromData(reply->readAll());
    setIcon(icon);
}
