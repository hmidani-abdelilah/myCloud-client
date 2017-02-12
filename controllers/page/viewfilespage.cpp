#include "Viewfilespage.h"
#include "factorybutton.h"

ViewFilesPage::ViewFilesPage(QWidget *parent) : Page()
{
    _manageElements = new ManagerElements(parent);
    _previousAction = new QLabelCustom();
    _displayPath = new DisplayPath();

    connect(_manageElements, &ManagerElements::folderHasBeenDoubleClicked, _displayPath, &DisplayPath::addElement);

    QVBoxLayout *_hBox = new QVBoxLayout();
    _hBox->addWidget(_manageElements);

    _hBox->setContentsMargins(0, 0, 0, 0);

    setLayout(_hBox);
    setHeaderBar();
}

void ViewFilesPage::setHeaderBar() {
    QHBoxLayout *layout = new QHBoxLayout();
    QWidget* spacerHorizontal = new QWidget();

    _headerLayout->setContentsMargins(0, 0, 12, 0);

    QPushButton *createFolder = FactoryButton("CREATE FOLDER").size(QSize(110, 24)).icon(":/elements/folder", QSize(10, 10)).gen();
    QPushButton *downloadBtn = FactoryButton("DOWNLOAD").size(QSize(100, 24)).icon(":/logo/download", QSize(10, 10)).gen();
    QPushButton *deleteBtn = FactoryButton("DELETE").size(QSize(100, 24)).icon(":/logo/delete", QSize(10, 10)).gen();

    downloadBtn->setEnabled(false);
    deleteBtn->setEnabled(false);

    connect(_manageElements, &ManagerElements::nbElementsSelectedChanged, downloadBtn, &QPushButton::setEnabled);
    connect(_manageElements, &ManagerElements::nbElementsSelectedChanged, deleteBtn, &QPushButton::setEnabled);

    QPixmap image(":/elements/previous");

    _previousAction->setPixmap(image);
    _previousAction->setFixedSize(20, 20);
    _previousAction->setScaledContents(true);
    _previousAction->setCursor(Qt::PointingHandCursor);

    connect(_displayPath, &DisplayPath::pathChanged, _manageElements, &ManagerElements::moveTo);
    connect(createFolder, &QPushButton::clicked, _manageElements, &ManagerElements::actionCreateFolder);
    connect(downloadBtn, &QPushButton::clicked, _manageElements, &ManagerElements::elementsHasBeenDragged);
    connect(deleteBtn, &QPushButton::clicked, _manageElements, &ManagerElements::deleteFileSelectedOnServer);
    spacerHorizontal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);

    layout->setContentsMargins(10, 2, 6, 2);
    layout->addWidget(_previousAction);

    layout->addLayout(_displayPath);
    layout->addWidget(spacerHorizontal);
    layout->addWidget(deleteBtn);
    layout->addWidget(downloadBtn);
    layout->addWidget(createFolder);
    connect(_previousAction, &QLabelCustom::clicked, _displayPath, &DisplayPath::deleteLastElement);
    connect(_previousAction, &QLabelCustom::clicked, _manageElements, &ManagerElements::moveBackToFolder);

    _headerLayout->setLayout(layout);
}

void ViewFilesPage::reloadPage() {
    //_manageElements->refreshActualPage();
}
