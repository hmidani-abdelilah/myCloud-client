#ifndef FOLDERELEMENT_H
#define FOLDERELEMENT_H

#include "element.h"

class FolderElement : public Element
{
public:
    FolderElement(QString title = "folder", quint64 size = 0, QString path = "", QWidget *parent = 0);

protected:
};

#endif // FOLDERELEMENT_H
