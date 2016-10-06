#include "managerelements.h"
#include "socketmanager.h"
#include "jsonmanager.h"

#include <QNetworkReply>
#include <QFileInfo>

ManagerElements::ManagerElements(QWidget *parent) : QScrollArea(parent)
{
    _flowLayout = new FlowLayout();
    _pathRequest = new PathRequest();
    _fileManager = FileManager::getInstanceFileM();
    _fileManager->addManagerElement(this);

    setAcceptDrops(true);

    this->setStyleSheet("QWidget {background-color:#" + Color::GlobalInfo::white + ";} QScrollArea { border: 1px solid #" + Color::GlobalInfo::greyBorder + "; } ");

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &ManagerElements::customContextMenuRequested, this, &ManagerElements::menuRequested);

    connect(_pathRequest, &PathRequest::finished, this, &ManagerElements::setContents);

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
    qDebug("folder create");
}

void ManagerElements::setContents(QNetworkReply *reply) {
    JsonManager *json = new JsonManager(reply);

    _flowLayout->removeAllList();
    QVector<QString> files = json->getArray("files");
    QVector<QString> folders = json->getArray("folders");

    for (int i = 0 ; i < files.length() ; i++) {
        FileElement *file = new FileElement(files.at(i));
        _flowLayout->addWidget(file);
    }

    for (int i = 0 ; i < folders.length() ; i++) {
        FolderElement *folder = new FolderElement(folders.at(i));
        connect(folder, &FolderElement::hasBeenDoubleClicked, _displayPath, &DisplayPath::addElement);
        connect(folder, &FolderElement::hasBeenDoubleClicked, this, &ManagerElements::moveInFolder);
        _flowLayout->addWidget(folder);
    }
}

void ManagerElements::getElements() {
//    _serviceRequest = new ServiceRequest();
//    connect(_serviceRequest, SIGNAL(finished(QNetworkReply*)),
//            this, SLOT(getDataElements(QNetworkReply*)));

//    CredentailsTable cdt;
//   // cdt.addCredential("email", ui->emailInput->text());
//   // cdt.addCredential("password", ui->passwordInput->text());
//    _serviceRequest->get(QNetworkRequest(QUrl("http://127.0.0.1:3000/api/user/login")));
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

void ManagerElements::setDisplayPath(DisplayPath *dispPath) {
    _displayPath = dispPath;
}

void ManagerElements::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug(event->mimeData()->urls().at(0).url().toStdString().c_str());
    event->acceptProposedAction();
}

void ManagerElements::dropEvent(QDropEvent *event)
{
    _fileManager->sendFile(event->mimeData()->text(), "/" + _path.join("/"));
     event->acceptProposedAction();
}
