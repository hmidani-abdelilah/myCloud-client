#include "managerelements.h"
#include "socketmanager.h"
#include "jsonmanager.h"
#include "httperror.h"

#include <QApplication>
#include <QNetworkReply>
#include <QFileInfo>
#include <QStyleOption>
#include <QPainter>

ManagerElements::ManagerElements(QWidget *parent) : QWidget(parent)
{
    _flowLayout = new FlowLayout();
    _pathRequest = new PathRequest();
    _fileManager = FileManager::getInstanceFileM();
    _factoryElement = new FactoryElement(this);

    setFocusPolicy(Qt::StrongFocus);
    setAcceptDrops(true);

    this->setStyleSheet("QWidget {background-color:#" + Color::GlobalInfo::white + ";}");

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &ManagerElements::customContextMenuRequested, this, &ManagerElements::menuRequested);
    connect(_fileManager, &FileManager::fileSended, this, &ManagerElements::slotFileSended);
    connect(_fileManager, &FileManager::fileDeleted, this, &ManagerElements::slotFileDeleted);
    connect(_pathRequest, &PathRequest::signalContent, this, &ManagerElements::setContents);
    connect(_fileManager, &FileManager::folderCreated, this, &ManagerElements::responseFolderCreate);
    configureRightClick();

    moveTo(_path);
    setLayout(_flowLayout);
}

void ManagerElements::slotFileSended(StatsElement::Stats stats) {
    FileElement *file = _factoryElement->generateFileElement(stats);

    removeOneElement(file->name(), file->pathServer(), file->type());
    addOneElement(file);
}

void ManagerElements::slotFileDeleted(StatsElement::Stats stats) {
    removeOneElement(stats.name, stats.pathServer, Element::FILE);
}

void ManagerElements::moveTo(const QStringList list) {
    RouteParams prms;

    _path = list;
    prms.addValueToBody("path", _path.join("/"));
    _pathRequest->request(PathRequest::POST, PathRequest::Contents, prms);
}

void ManagerElements::moveInFolder(const QString &folder) {
    RouteParams prms;

    _path.append(folder);
    prms.addValueToBody("path", _path.join("/"));
    _pathRequest->request(PathRequest::POST, PathRequest::Contents, prms);
}

void ManagerElements::deleteFileSelectedOnServer() {
    QString pathServer = "";

    for (int index = 0 ; index < _itemsSelected.length() ; index++) {
        if (_itemsSelected[index].pathServer.length() > 0)
            pathServer = _itemsSelected[index].pathServer + '/';
        _fileManager->deleteFileOnServer(pathServer + _itemsSelected[index].name);
    }
}

void ManagerElements::refreshActualPage() {
    RouteParams prms;
    prms.addValueToBody("path", _path.join("/"));

    _pathRequest->request(PathRequest::POST, PathRequest::Contents, prms);
}

void ManagerElements::moveBackToFolder() {
    RouteParams prms;

    if (_path.size() <= 0)
        return;
    _path.removeLast();
    prms.addValueToBody("path", _path.join("/"));
    _pathRequest->request(PathRequest::POST, PathRequest::Contents, prms);
}

void ManagerElements::configureRightClick() {
    QAction *createFolderA = new QAction("Create folder");
    connect(createFolderA, &QAction::triggered, this, &ManagerElements::actionCreateFolder);
    _menu.addAction(createFolderA);
}

void ManagerElements::actionCreateFolder(bool) {
    _fileManager->createFolder(_path.join("/"));
}

void ManagerElements::responseFolderCreate(QByteArray reply) {
    JsonManager *jsonFiles = new JsonManager(reply);
    QMap<QString, QVariant> map = jsonFiles->getJson();
    addOneElement(_factoryElement->generateFolderElement(map["name"].toString(), map["pathServer"].toString()));
}

void ManagerElements::setContents(QNetworkReply *reply) {
    JsonManager *jsonFiles = new JsonManager(reply);
    _flowLayout->removeAllList();

    int nbFile = jsonFiles->toObject("files")->length();
    jsonFiles->initialize();

    for (int i = 0 ; i < nbFile ; i++) {
        QMap<QString, QVariant> fileStat = jsonFiles->toObject("files")->toArray(i)->getJson();

        FileElement *file = _factoryElement->generateFileElement(fileStat["name"].toString(), fileStat["size"].toLongLong(), fileStat["path"].toString());
        _flowLayout->addWidget(file);
        jsonFiles->initialize();
    }

    QString path = jsonFiles->getJson()["path"].toString();
    jsonFiles->initialize();

    QVector<QVariant> folders = jsonFiles->toObject("folders")->getArray();

    for (int i = 0 ; i < folders.length() ; i++) {
        FolderElement *folder = _factoryElement->generateFolderElement(folders.at(i).toString(), path);
        _flowLayout->addWidget(folder);
    }
}

void ManagerElements::addOneElement(Element *element) {
    if (_path.join("/") == element->pathServer()) {
        _flowLayout->addWidget(element);
    }
}

void ManagerElements::removeOneElement(QString name, QString path, Element::TypeElement type) {
    if (_path.join("/") == path) {
        for (int i = 0 ; i < _flowLayout->count() ; i++) {
            QLayoutItem *layoutItem = _flowLayout->itemAt(i);
            Element *elem = dynamic_cast<Element *>(layoutItem->widget());
            if (elem->name() == name && elem->type() == type) {
                _flowLayout->removeItem(layoutItem);
                delete layoutItem->widget();
                delete layoutItem;
                break;
            }
        }
    }
}

void ManagerElements::elementHasBeenDoubleClicked(QString title) {
    emit folderHasBeenDoubleClicked(title);
}

void ManagerElements::menuRequested(const QPoint & pos) {
    _menu.popup(mapToGlobal(pos));
}

void ManagerElements::elementHasBeenClicked(StatsElement::Stats dataElement) {
    if (QApplication::keyboardModifiers() == Qt::ControlModifier) {
        _itemsSelected.append(dataElement);
        _lastFileSelected = dataElement;
        emit nbElementsSelectedChanged(_itemsSelected.length() > 0);
        return;
    }
    if (QApplication::keyboardModifiers() == Qt::ShiftModifier) {
        bool startSelect = false;
        for (int index = 0 ; index < _flowLayout->count() ; index++) {
            Element *elem = dynamic_cast<Element *>(_flowLayout->itemAt(index)->widget());
            if (startSelect == true || _lastFileSelected.name == elem->name() || dataElement.name == elem->name()) {
                if (elem->isSelected() == false) {
                    elem->setSelected(true);
                    _itemsSelected.append(elem->stats());
                }
                if (_lastFileSelected.name == elem->name() || dataElement.name == elem->name())
                    startSelect = !startSelect;
            }
        }
        emit nbElementsSelectedChanged(_itemsSelected.length());
        return;
    }
    _lastFileSelected = dataElement;
    _itemsSelected.clear();
    _itemsSelected.append(dataElement);
    for (int i = 0 ; i < _flowLayout->count() ; i++) {
        dynamic_cast<Element *>(_flowLayout->itemAt(i)->widget())->setSelected(false);
    }
    emit nbElementsSelectedChanged(_itemsSelected.length());
}

void ManagerElements::elementHasBeenUnselected(StatsElement::Stats dataElement) {
    for (int i = 0 ; i < _itemsSelected.length() ; i++) {
        if (_itemsSelected[i].name == dataElement.name)
            _itemsSelected.remove(i);
    }
}

void ManagerElements::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void ManagerElements::dropEvent(QDropEvent *event)
{
    QList<QUrl> listFilesUrls = event->mimeData()->urls();
    for (int fileUrlIndex = 0 ; fileUrlIndex < listFilesUrls.length() ; fileUrlIndex++) {
        _fileManager->sendFile(listFilesUrls[fileUrlIndex], _path.join("/"));
    }
    event->acceptProposedAction();
}

void ManagerElements::elementsHasBeenDragged() {
    DialogueDropElement dialogDropElement;
    QMessageBox msgBox;

    dialogDropElement.setFiles(_itemsSelected);
    msgBox.setInformativeText("Do you want to replace this file ?");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    if (dialogDropElement.exec()) {
        QString directory = dialogDropElement.getSelectedPath();
        for (int index = 0 ; index < _itemsSelected.length() ; index++) {

            //Check if file exist

            QFile file(QUrl(directory + "/" + _itemsSelected[index].name).path());

            if (!file.exists()) {
                _fileManager->downloadFile(_itemsSelected[index].pathServer + "/" + _itemsSelected[index].name, directory, _itemsSelected[index].size);
                continue;
            }

            //if file does not exist

            msgBox.setText(_itemsSelected[index].name + " already exist");
            int ret = msgBox.exec();
            switch (ret) {
            case QMessageBox::Yes: {
                if (file.remove())
                    _fileManager->downloadFile(_itemsSelected[index].pathServer + "/" + _itemsSelected[index].name, directory, _itemsSelected[index].size);
                else
                    QMessageBox::critical(this, "Can not delete file " + _itemsSelected[index].name,
                                          "This document does not exist, try it again");
            }
            case QMessageBox::Cancel: {
                // Don't Save was clicked
                break;
            }
            default: {
                // should never be reached
                break;
            }
            }
        }
    }
}

void ManagerElements::setDraggableMode(Element::DraggableMode draggableMode)
{
    _factoryElement->setDraggableMode(draggableMode);
}

void ManagerElements::paintEvent(QPaintEvent *) {
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

