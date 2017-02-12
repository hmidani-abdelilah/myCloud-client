#include "itemrepositoryserver.h"

ItemRepositoryServer::ItemRepositoryServer(ItemRepositoryServer *treeWidgetItem) : QWidget(), QTreeWidgetItem(treeWidgetItem)
{
    setAcceptDrops(true);
}

ItemRepositoryServer::ItemRepositoryServer(QTreeWidget *treeWidget) : QTreeWidgetItem(treeWidget)
{

}
