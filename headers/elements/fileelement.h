#ifndef FILEELEMENT_H
#define FILEELEMENT_H
#include "element.h"

class FileElement : public Element
{
public:
    FileElement(QString title = "file", QWidget *parent = 0);
};

#endif // FILEELEMENT_H
