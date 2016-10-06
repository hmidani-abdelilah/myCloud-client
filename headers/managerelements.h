#ifndef MANAGERELEMENTS_H
#define MANAGERELEMENTS_H

#include <QScrollArea>
#include "flowlayout.h"
#include "fileelement.h"
#include "folderelement.h"
#include "globalinfo.h"
#include "userrequest.h"
#include "pathrequest.h"
#include "displaypath.h"
#include "filemanager.h"

class FileManager;

class ManagerElements : public QScrollArea
{

public:
    explicit ManagerElements(QWidget *parent = 0);
    void setDisplayPath(DisplayPath *dispPath);

public slots:
    void moveInFolder(const QString &folder);
    void moveBackToFolder();
    void moveTo(const QStringList list);
    void refreshActualPage();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

protected slots:
    void getDataElements(QNetworkReply *reply);

private slots:
    void setContents(QNetworkReply *reply);
    void menuRequested(const QPoint &pos);
    void actionCreateFolder(bool checked);

private:
    FlowLayout *_flowLayout;
    PathRequest *_pathRequest;
    FileManager *_fileManager;
    QMenu _menu;
    QStringList _path;
    DisplayPath *_displayPath;
    void getElements();
    void configureRightClick();
};

#endif // MANAGERELEMENTS_H
