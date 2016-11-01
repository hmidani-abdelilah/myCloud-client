#include "managerelements.h"
#include "socketmanager.h"
#include "jsonmanager.h"

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
    _messageBoxCreateFolder = new MessageBoxNaming ("Name of the folder", "Create");

    setAcceptDrops(true);

    this->setStyleSheet("QWidget {background-color:#" + Color::GlobalInfo::white + ";}");

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &ManagerElements::customContextMenuRequested, this, &ManagerElements::menuRequested);

    connect(_fileManager, &FileManager::fileSended, this, &ManagerElements::refreshActualPage);
    connect(_pathRequest, &PathRequest::finished, this, &ManagerElements::setContents);
    connect(_folderRequest, &FolderRequest::finished, this, &ManagerElements::responseFolderCreate);
    configureRightClick();

    moveTo(_path);
    setLayout(_flowLayout);
}

void ManagerElements::moveTo(const QStringList list) {
    CredentailsTable cdt;

    _path = list;
    cdt.addCredential("path", "/" + _path.join("/"));
    _pathRequest->request(PathRequest::POST, PathRequest::Contents, cdt);
}

void ManagerElements::moveInFolder(const QString &folder) {
    CredentailsTable cdt;

    _path.append(folder);
    cdt.addCredential("path", "/" + _path.join("/"));
    _pathRequest->request(PathRequest::POST, PathRequest::Contents, cdt);
}

void ManagerElements::refreshActualPage() {
    CredentailsTable cdt;
    cdt.addCredential("path", "/" + _path.join("/"));

    _pathRequest->request(PathRequest::POST, PathRequest::Contents, cdt);
}

void ManagerElements::moveBackToFolder() {
    CredentailsTable cdt;

    if (_path.size() <= 0)
        return;
    _path.removeLast();
    cdt.addCredential("path", "/" + _path.join("/"));
    _pathRequest->request(PathRequest::POST, PathRequest::Contents, cdt);
}

void ManagerElements::configureRightClick() {
    QAction *createFolderA = new QAction("Create folder");
    connect(createFolderA, &QAction::triggered, this, &ManagerElements::actionCreateFolder);
    _menu.addAction(createFolderA);
}

void ManagerElements::actionCreateFolder(bool checked) {
    _messageBoxCreateFolder->exec();

    CredentailsTable cdt;

    cdt.addCredential("pathServer", _path.join("/"));
    cdt.addCredential("name", _messageBoxCreateFolder->text());

    _folderRequest->request(FolderRequest::POST, FolderRequest::Folder::Create, cdt);
}

void ManagerElements::responseFolderCreate(QNetworkReply *reply) {
    if (reply->error() != 0)
    {
        qDebug("Il y a eu une erreur lors de la creation du dossier %d", reply->error());
        return ;
    }
    refreshActualPage();
}

void ManagerElements::setContents(QNetworkReply *reply) {
    JsonManager *jsonFiles = new JsonManager(reply);
    _flowLayout->removeAllList();

    QMap<QString, QString> json = jsonFiles->getJson();
    jsonFiles->initialize();
    QVector<QString> files = jsonFiles->toObject("files")->getArray();
    jsonFiles->initialize();
    QVector<QString> folders = jsonFiles->toObject("folders")->getArray();

    for (int i = 0 ; i < files.length() ; i++) {
        FileElement *file = new FileElement(files.at(i));
        connect(file, &FileElement::clicked, this, &ManagerElements::ElementhasBeenClicked);
        _flowLayout->addWidget(file);
    }

    for (int i = 0 ; i < folders.length() ; i++) {
        FolderElement *folder = new FolderElement(folders.at(i));
        connect(folder, &FileElement::clicked, this, &ManagerElements::ElementhasBeenClicked);
        connect(folder, &FolderElement::hasBeenDoubleClicked, this, &ManagerElements::folderHasBeenDoubleClicked);
        connect(folder, &FolderElement::hasBeenDoubleClicked, this, &ManagerElements::moveInFolder);
        _flowLayout->addWidget(folder);
    }
}

void ManagerElements::ElementHasBeenDoubleClicked(QString title) {
    emit folderHasBeenDoubleClicked(title);
}

void ManagerElements::getDataElements(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray asdf = reply->readAll();
        qDebug() << (QString("asdf %1").arg(asdf.length()));
        qDebug() << (QString(asdf));
    }
    else
    {
        qDebug("error request");
    }
    qDebug("replyFinished");
}

void ManagerElements::menuRequested(const QPoint & pos) {
    _menu.popup(mapToGlobal(pos));
}

void ManagerElements::ElementhasBeenClicked() {
    for (int i = 0 ; i < _flowLayout->count() ; i++) {
        _flowLayout->itemAt(i)->widget()->setStyleSheet("");
    }
}

//void ManagerElements::setDisplayPath(DisplayPath *dispPath) {
//    _displayPath = dispPath;
//}

void ManagerElements::dragEnterEvent(QDragEnterEvent *event)
{
    //qDebug(event->mimeData()->urls().at(0).url().toStdString().c_str());
    event->acceptProposedAction();
}

void ManagerElements::dropEvent(QDropEvent *event)
{
    _fileManager->sendFile(event->mimeData()->text(), _path.join("/"));
     event->acceptProposedAction();
}

void ManagerElements::paintEvent(QPaintEvent *pe) {
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
