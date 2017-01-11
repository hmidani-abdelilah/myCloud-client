#include "folderelement.h"
#include "ui_element.h"

FolderElement::FolderElement(QString title, quint64 size, QString path, QWidget *parent) : Element(title, size, path, parent)
{
    setIcon(QPixmap(":/elements/folder"));
}
