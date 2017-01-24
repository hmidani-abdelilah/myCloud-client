#include "managerelements.h"
#include "socketmanager.h"
#include "jsonmanager.h"
#include "httperror.h"

#include <QNetworkReply>
#include <QFileInfo>
#include <QStyleOption>
#include <QPainter>

ManagerElements::ManagerElements(QWidget *parent) : QWidget(parent)
{
    _flowLayout = new FlowLayout();
    _pathRequest = new PathRequest();
    _folderRequest = new FolderRequest();
    _fileManager = FileManager::getInstanceFileM();
    _ctrlKeyPress = false;
    _messageBoxCreateFolder = new MessageBoxNaming ("Name of the folder", "Create");

    setFocusPolicy(Qt::StrongFocus);
    setAcceptDrops(true);

    this->setStyleSheet("QWidget {background-color:#" + Color::GlobalInfo::white + ";}");

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &ManagerElements::customContextMenuRequested, this, &ManagerElements::menuRequested);
    connect(_fileManager, &FileManager::fileSended, this, &ManagerElements::slotFileSended);
    connect(_fileManager, &FileManager::fileReplaced, this, &ManagerElements::slotFileReplaced);
    connect(_pathRequest, &PathRequest::signalContent, this, &ManagerElements::setContents);
    connect(_folderRequest, &FolderRequest::signalCreate, this, &ManagerElements::responseFolderCreate);
    configureRightClick();

    moveTo(_path);
    setLayout(_flowLayout);
}

void ManagerElements::slotFileSended(FileInfo fileInfo) {
    FileElement *file = createFileElement(fileInfo.name, fileInfo.size, fileInfo.serverPath);
    addOneElement(file);
}

void ManagerElements::slotFileReplaced(FileInfo fileInfo) {
    removeOneElement(fileInfo.name, fileInfo.serverPath, Element::FILE);
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

void ManagerElements::actionCreateFolder(bool checked) {
    _messageBoxCreateFolder->exec();

    RouteParams prms;

    prms.addValueToBody("pathServer", _path.join("/"));
    prms.addValueToBody("name", _messageBoxCreateFolder->text());

    _folderRequest->request(FolderRequest::POST, FolderRequest::Folder::Create, prms);
}

void ManagerElements::responseFolderCreate(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);
    JsonManager *jsonFiles = new JsonManager(reply);
    QMap<QString, QString> map = jsonFiles->getJson();
    addOneElement(createFolderElement(map["name"], map["pathServer"]));
}

void ManagerElements::setContents(QNetworkReply *reply) {
    JsonManager *jsonFiles = new JsonManager(reply);
    _flowLayout->removeAllList();

    int nbFile = jsonFiles->toObject("files")->length();
    jsonFiles->initialize();

    for (int i = 0 ; i < nbFile ; i++) {
        QMap<QString, QString> fileStat = jsonFiles->toObject("files")->toArray(i)->getJson();

        FileElement *file = createFileElement(fileStat["name"], fileStat["size"].toULongLong(), fileStat["path"]);
        _flowLayout->addWidget(file);
        jsonFiles->initialize();
    }

    QString path = jsonFiles->getJson()["path"];
    jsonFiles->initialize();

    QVector<QString> folders = jsonFiles->toObject("folders")->getArray();

    for (int i = 0 ; i < folders.length() ; i++) {
        FolderElement *folder = createFolderElement(folders.at(i), path);
        _flowLayout->addWidget(folder);
    }
}

FileElement *ManagerElements::createFileElement(QString name, quint64 size, QString path) {
    FileElement *file = new FileElement(name, size, path);
    connect(file, &FileElement::selected, this, &ManagerElements::ElementhasBeenClicked);
    connect(file, &FileElement::isDragged, this, &ManagerElements::elementsHasBeenDragged);

    return file;
}

FolderElement *ManagerElements::createFolderElement(QString name, QString pathServer) {
    FolderElement *folder = new FolderElement(name, pathServer);

    connect(folder, &FolderElement::selected, this, &ManagerElements::ElementhasBeenClicked);
    connect(folder, &FolderElement::hasBeenDoubleClicked, this, &ManagerElements::folderHasBeenDoubleClicked);
    connect(folder, &FolderElement::hasBeenDoubleClicked, this, &ManagerElements::moveInFolder);
    connect(folder, &FolderElement::isDragged, this, &ManagerElements::elementsHasBeenDragged);

    return folder;
}

void ManagerElements::addOneElement(Element *element) {
    if (_path.join("/") == element->path()) {
        _flowLayout->addWidget(element);
    }
}

void ManagerElements::removeOneElement(QString name, QString path, Element::Type type) {
    if (_path.join("/") == path) {
        for (int i = 0 ; _flowLayout->count() ; i++) {
            Element *elem = dynamic_cast<Element *>(_flowLayout->itemAt(i)->widget());
            if (elem->title() == name && elem->type() == type) {
                delete _flowLayout->itemAt(i)->widget();
                delete _flowLayout->takeAt(i);
                break;
            }
        }
    }
}

void ManagerElements::ElementHasBeenDoubleClicked(QString title) {
    emit folderHasBeenDoubleClicked(title);
}

void ManagerElements::menuRequested(const QPoint & pos) {
    _menu.popup(mapToGlobal(pos));
}

void ManagerElements::ElementhasBeenClicked(DataElement dataElement) {

    if (_ctrlKeyPress == true) {
        _itemsSelected.append(dataElement);
        return;
    }
    _itemsSelected.clear();
    _itemsSelected.append(dataElement);
    for (int i = 0 ; i < _flowLayout->count() ; i++) {
        dynamic_cast<Element *>(_flowLayout->itemAt(i)->widget())->setSelected(false);
    }
}

void ManagerElements::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == 16777249) // CTRL
        _ctrlKeyPress = true;
}

void ManagerElements::keyReleaseEvent(QKeyEvent *ev)
{
    if (ev->key() == 16777249) // CTRL
        _ctrlKeyPress = false;
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
                _fileManager->downloadFile(_itemsSelected[index].path + "/" + _itemsSelected[index].name, directory, _itemsSelected[index].size);
                continue;
            }

            //if file does not exist

            msgBox.setText(_itemsSelected[index].name + " already exist");
            int ret = msgBox.exec();
            switch (ret) {
            case QMessageBox::Yes: {
                if (file.remove())
                    _fileManager->downloadFile(_itemsSelected[index].path + "/" + _itemsSelected[index].name, directory, _itemsSelected[index].size);
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

void ManagerElements::paintEvent(QPaintEvent *pe) {
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
