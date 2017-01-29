#ifndef FILEELEMENT_H
#define FILEELEMENT_H

#include "element.h"
#include "filerequest.h"

class FileElement : public Element
{
public:
    FileElement(QString title, quint64 size, quint64 transferedSize, QString pathServer, QString pathClient, Status status, QWidget *parent = 0);
    FileElement(Stats stats, QWidget *parent = 0);

protected:
    void getIcon();

private slots:
    void responseReduceImage(QNetworkReply *reply);
    QMap<QString, QPixmap> _listPictureElement;

private:
    FileRequest *_fileRequest;
};

#endif // FILEELEMENT_H
