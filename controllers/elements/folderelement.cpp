#include "folderelement.h"
#include "ui_element.h"

FolderElement::FolderElement(QString title, QWidget *parent) : Element(title, parent)
{
    setIcon(QPixmap(":/elements/folder"));
}
