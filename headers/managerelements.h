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
#include "dialoguedropelement.h"

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

    void ElementhasBeenClicked(DataElement dataElement);
    void responseFolderCreate(QNetworkReply *reply);
    void elementsHasBeenDragged();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

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
    QVector<DataElement> _itemsSelected;
    bool        _ctrlKeyPress;
    void configureRightClick();

    QLabelCustom    *_previousAction;
    void paintEvent(QPaintEvent *pe);

    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);
signals:
    void folderHasBeenDoubleClicked(QString title);
};

#endif // MANAGERELEMENTS_H
