#ifndef TREEREPOSITORYSERVER_H
#define TREEREPOSITORYSERVER_H

#include <QTreeWidget>

#include "itemrepositoryserver.h"
#include "pathrequest.h"
#include "filemanager.h"

class TreeRepositoryServer : public QTreeWidget
{
public:
    TreeRepositoryServer();

public slots:
    void clickCreateFolder(bool);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
private:
    void actualizeRepository();
    void createTreeWidgetItem(QString path);

    QMap<QString, ItemRepositoryServer*>     *_treeRepositoryServerList;
    PathRequest                         *_pathRequest;
    FileManager                         *_fileManager;

private slots:
    void responseTreeRepository(QNetworkReply *reply);
    void addNewWidgetItem(QByteArray reply);
};

#endif // TREEREPOSITORYSERVER_H
