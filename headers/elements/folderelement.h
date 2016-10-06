#ifndef FOLDERELEMENT_H
#define FOLDERELEMENT_H
#include "element.h"

class FolderElement : public Element
{
public:
    FolderElement(QString title = "folder", QWidget *parent = 0);

protected:
};

#endif // FOLDERELEMENT_H
