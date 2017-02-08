#include "itemrepositoryserver.h"

ItemRepositoryServer::ItemRepositoryServer(ItemRepositoryServer *treeWidgetItem) : QWidget(), QTreeWidgetItem(treeWidgetItem)
{

}

ItemRepositoryServer::ItemRepositoryServer(QTreeWidget *treeWidget) : QTreeWidgetItem(treeWidget)
{

}
