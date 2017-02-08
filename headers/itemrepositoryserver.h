#ifndef ITEMREPOSITORYSERVER_H
#define ITEMREPOSITORYSERVER_H

#include <QTreeWidgetItem>
#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>

class ItemRepositoryServer : public QWidget, public QTreeWidgetItem
{
public:
    ItemRepositoryServer(ItemRepositoryServer *treeWidgetItem);
    ItemRepositoryServer(QTreeWidget *treeWidget);

    inline void setPath(QString path) {_path = path;}
    inline QString path() {return _path;}

private:
    QString _path;
};

#endif // ITEMREPOSITORYSERVER_H
