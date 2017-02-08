#include "Viewfilespage.h"

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

    QPixmap image(":/elements/previous");

    _previousAction->setPixmap(image);
    _previousAction->setFixedSize(20, 20);
    _previousAction->setScaledContents(true);
    _previousAction->setCursor(Qt::PointingHandCursor);

    connect(_displayPath, &DisplayPath::pathChanged, _manageElements, &ManagerElements::moveTo);

    spacerHorizontal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);

    layout->setContentsMargins(10, 2, 6, 2);
    layout->addWidget(_previousAction);

    layout->addLayout(_displayPath);
    layout->addWidget(spacerHorizontal);

    connect(_previousAction, &QLabelCustom::clicked, _displayPath, &DisplayPath::deleteLastElement);
    connect(_previousAction, &QLabelCustom::clicked, _manageElements, &ManagerElements::moveBackToFolder);

    _headerLayout->setLayout(layout);
}

void ViewFilesPage::reloadPage() {
    //_manageElements->refreshActualPage();
}
