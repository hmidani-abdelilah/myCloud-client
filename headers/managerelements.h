#ifndef MANAGERELEMENTS_H
#define MANAGERELEMENTS_H

#include <QWidget>

#include "flowlayout.h"
#include "fileelement.h"
#include "folderelement.h"
#include "globalinfo.h"
#include "userrequest.h"
#include "pathrequest.h"
#include "displaypath.h"
#include "filemanager.h"
#include "messageboxnaming.h"
#include "folderrequest.h"

class FileManager;

class ManagerElements : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerElements(QWidget *parent = 0);
    //void setDisplayPath(DisplayPath *dispPath);

public slots:
    void moveInFolder(const QString &folder);
    void moveBackToFolder();
    void moveTo(const QStringList list);
    void refreshActualPage();

private slots:
    void ElementHasBeenDoubleClicked(QString title);

    void ElementhasBeenClicked();
    void responseFolderCreate(QNetworkReply *reply);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

protected slots:
    void getDataElements(QNetworkReply *reply);

protected slots:
    void setContents(QNetworkReply *reply);
    void menuRequested(const QPoint &pos);
    void actionCreateFolder(bool checked);

protected:
    FlowLayout *_flowLayout;
    PathRequest *_pathRequest;
    FolderRequest *_folderRequest;
    FileManager *_fileManager;
    QMenu _menu;
    QStringList _path;
    DisplayPath *_displayPath;
    MessageBoxNaming *_messageBoxCreateFolder;

    void configureRightClick();

    QLabelCustom    *_previousAction;
    void paintEvent(QPaintEvent *pe);

signals:
    void folderHasBeenDoubleClicked(QString title);
};

#endif // MANAGERELEMENTS_H
