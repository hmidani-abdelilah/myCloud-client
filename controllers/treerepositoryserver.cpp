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

    connect(_pathRequest, &PathRequest::signalTreeRepository, this, &TreeRepositoryServer::responseTreeRepository);
    connect(_fileManager, &FileManager::folderCreated, this, &TreeRepositoryServer::addNewWidgetItem);
    this->header()->hide();
    this->verticalScrollBar()->setStyleSheet(StyleSheet::GlobalInfo::scrollBarVertical);
    this->setStyleSheet("QTreeView { border: 1px solid #" + Color::GlobalInfo::greyBorder + ";}" + StyleSheet::GlobalInfo::tree);
    this->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    _treeRepositoryServerList = new QMap<QString, ItemRepositoryServer *>();
    actualizeRepository();
}

void TreeRepositoryServer::actualizeRepository() {
    this->_pathRequest->request(PathRequest::GET, PathRequest::TreeRepository);
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

void TreeRepositoryServer::responseTreeRepository(QNetworkReply *reply) {
    JsonManager json(reply);

    QVector<QVariant> array = json.getArray();

    ItemRepositoryServer *widgetItem = new ItemRepositoryServer(this);
    widgetItem->setPath("");
    widgetItem->setText(0, "HOME");
    widgetItem->setIcon(0, QIcon(":/logo/cloud2"));
    _treeRepositoryServerList->insert("", widgetItem);

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

        QString path = "";
        if (treeWidgetItem->path().length() > 0)
            path = treeWidgetItem->path() + "/";

        if (list[i] != path + fileInfo.fileName())
            _fileManager->moveElementTo(list[i], path + fileInfo.fileName());
    }
    event->acceptProposedAction();
}
