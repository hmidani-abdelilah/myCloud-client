#ifndef MANAGERELEMENTS_H
#define MANAGERELEMENTS_H

#include <QWidget>

#include "flowlayout.h"
#include "globalinfo.h"
#include "userrequest.h"
#include "pathrequest.h"
#include "displaypath.h"
#include "filemanager.h"
#include "messageboxnaming.h"
#include "dialoguedropelement.h"
#include "factoryelement.h"

class FileManager;
class FactoryElement;

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
    void elementHasBeenDoubleClicked(QString title);
    void elementHasBeenClicked(StatsElement::Stats dataElement);
    virtual void elementsHasBeenDragged();
    void setDraggableMode(Element::DraggableMode draggableMode = Element::EMIT);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void addOneElement(Element *element);
    void removeOneElement(QString name, QString path, Element::TypeElement type);
    void configureRightClick();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

protected slots:
    void setContents(QNetworkReply *reply);
    void menuRequested(const QPoint &pos);
    void responseFolderCreate(QByteArray reply);
    void slotFileSended(StatsElement::Stats stats);
    void slotFileReplaced(StatsElement::Stats stats);
    void actionCreateFolder(bool);

protected:
    FlowLayout *_flowLayout;
    PathRequest *_pathRequest;
    FileManager *_fileManager;
    QMenu _menu;
    QStringList _path;
    DisplayPath *_displayPath;
    QVector<StatsElement::Stats> _itemsSelected;
    bool        _ctrlKeyPress;
    FactoryElement *_factoryElement;
    QLabelCustom    *_previousAction;

signals:
    void folderHasBeenDoubleClicked(QString title);
};

#endif // MANAGERELEMENTS_H
