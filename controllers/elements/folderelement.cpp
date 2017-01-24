#include "folderelement.h"
#include "ui_element.h"

FolderElement::FolderElement(QString title, QString path, QWidget *parent) : Element(title, 0, path, Element::FOLDER, parent)
{
    setIcon(QPixmap(":/elements/folder"));
}
