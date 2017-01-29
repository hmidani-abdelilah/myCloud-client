#ifndef FOLDERELEMENT_H
#define FOLDERELEMENT_H

#include "element.h"

class FolderElement : public Element
{
public:
    FolderElement(QString name, quint64 size, quint64 transferedSize, QString pathServer, QString pathClient, Status status, QWidget *parent = 0);
protected:
};

#endif // FOLDERELEMENT_H
