#ifndef FILEELEMENT_H
#define FILEELEMENT_H

#include "element.h"
#include "filerequest.h"

class FileElement : public Element
{
public:
    FileElement(QString title = "file", QWidget *parent = 0);

protected:
    void getIcon();

private slots:
    void responseReduceImage(QNetworkReply *reply);

private:
    FileRequest *_requestReduceImage;
};

#endif // FILEELEMENT_H
