#include "folderelement.h"
#include "ui_element.h"

FolderElement::FolderElement(QString name, qint64 size, qint64 transferedSize, QString pathServer, QString pathClient, Status status, QWidget *parent)
    : Element(name, size, transferedSize, pathServer, pathClient, TypeElement::FOLDER, status, parent)
{
    setIcon(QPixmap(":/elements/folder"));
}
