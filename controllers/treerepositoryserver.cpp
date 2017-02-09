#include <QHeaderView>
#include <QFileInfo>
#include <QScrollBar>

#include "filemanager.h"
#include "treerepositoryserver.h"
#include "jsonmanager.h"
#include "globalinfo.h"

TreeRepositoryServer::TreeRepositoryServer() : QTreeWidget()
{
    setAcceptDrops(true);
    setDragEnabled(true);
    setDropIndicatorShown(true);
    viewport()->setAcceptDrops(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setFrameStyle(QFrame::NoFrame);
    _pathRequest = new PathRequest();
    _fileManager = FileManager::getInstanceFileM();

    connect(_pathRequest, &PathRequest::signalRepositoryTree, this, &TreeRepositoryServer::responseRepositoryTree);
    connect(_fileManager, &FileManager::folderCreated, this, &TreeRepositoryServer::addNewWidgetItem);
    this->header()->hide();
    this->verticalScrollBar()->setStyleSheet(StyleSheet::GlobalInfo::scrollBar);
    this->setStyleSheet("QTreeView { border: 1px solid #" + Color::GlobalInfo::greyBorder + ";}" + StyleSheet::GlobalInfo::tree);
    this->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    _treeRepositoryServerList = new QMap<QString, ItemRepositoryServer *>();
    actualizeRepository();
}

void TreeRepositoryServer::actualizeRepository() {
    this->_pathRequest->request(PathRequest::GET, PathRequest::RepositoryTree);
}

void TreeRepositoryServer::createTreeWidgetItem(QString path) {
    QFileInfo dirInfo(path);
    ItemRepositoryServer *widgetItem;

    if (dirInfo.fileName() == path) {
        widgetItem = new ItemRepositoryServer(this);
    }
    else {
        widgetItem = new ItemRepositoryServer(_treeRepositoryServerList->value(dirInfo.path()));
    }
    widgetItem->setPath(path);
    widgetItem->setText(0, dirInfo.fileName());
    widgetItem->setIcon(0, QIcon(":/elements/folder"));
    _treeRepositoryServerList->insert(path, widgetItem);
}

void TreeRepositoryServer::responseRepositoryTree(QNetworkReply *reply) {
    JsonManager json(reply);

    QVector<QVariant> array = json.getArray();

    for (int index = 0 ; index < array.length() ; index++) {
        createTreeWidgetItem(array[index].toString());
    }
}

void TreeRepositoryServer::clickCreateFolder(bool) {
    _fileManager->createFolder(dynamic_cast<ItemRepositoryServer *>(this->currentItem())->path());
}

void TreeRepositoryServer::addNewWidgetItem(QByteArray reply) {
    JsonManager *jsonFiles = new JsonManager(reply);
    QMap<QString, QVariant> map = jsonFiles->getJson();
    QString pathServer = "";

    if (map["pathServer"].toString().length() > 0)
        pathServer = map["pathServer"].toString() + '/';

    createTreeWidgetItem(pathServer + map["name"].toString());
}

void TreeRepositoryServer::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void TreeRepositoryServer::dropEvent(QDropEvent *event)
{
    QStringList list = QString::fromUtf8(event->mimeData()->data("myapplication::stringlist")).split(",");

    for (int i = 0 ; i < list.length() ; i++) {
        QFileInfo fileInfo(list[i]);

        ItemRepositoryServer *treeWidgetItem = dynamic_cast<ItemRepositoryServer *>(itemAt(event->pos()));
        if (list[i] != treeWidgetItem->path() + "/" + fileInfo.fileName())
            _fileManager->moveElementTo(list[i], treeWidgetItem->path() + "/" + fileInfo.fileName());
    }
    event->acceptProposedAction();
}
