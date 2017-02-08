#include <QScrollArea>

#include "sortpage.h"
#include "jsonmanager.h"
#include "globalinfo.h"

SortPage::SortPage(QWidget *parent) : Page()
{
    _manageElements = new ManagerElementsOrder(parent);
    _previousAction = new QLabelCustom();
    _displayPath = new DisplayPath();
    _treeRepositoryServer = new TreeRepositoryServer();
    QHBoxLayout *_hBox = new QHBoxLayout();
    QScrollArea *scrollArea = new QScrollArea();

    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(1);
    spRight.setHorizontalStretch(1);
    _treeRepositoryServer->setSizePolicy(spRight);
    scrollArea->setSizePolicy(spLeft);
    //_manageElements->setSizePolicy(spLeft);


    connect(_manageElements, &ManagerElements::folderHasBeenDoubleClicked, _displayPath, &DisplayPath::addElement);
    _manageElements->setDraggableMode(Element::NORMAL);

    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    scrollArea->setWidgetResizable( true );
    scrollArea->setWidget(_manageElements);
    scrollArea->setFrameStyle(QFrame::NoFrame);
    scrollArea->setStyleSheet("QScrollArea { border: 1px solid #" + Color::GlobalInfo::greyBorder + ";}" + StyleSheet::GlobalInfo::scrollBar);
    _hBox->addWidget(scrollArea);
    _hBox->addWidget(_treeRepositoryServer);
    _hBox->setContentsMargins(0, 0, 0, 0);
    _hBox->setSpacing(0);

    setLayout(_hBox);
    setHeaderBar();
}

void SortPage::setHeaderBar() {
    QHBoxLayout *layout = new QHBoxLayout();

    QWidget* spacerHorizontal = new QWidget();

    QPixmap image(":/elements/previous");
    QPushButton *createFolder = new QPushButton("Create folder");
    QPushButton *start = new QPushButton("Start");
    QPushButton *stop = new QPushButton("Stop");

    connect(createFolder, &QPushButton::clicked, _treeRepositoryServer, &TreeRepositoryServer::clickCreateFolder);

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
    layout->addWidget(createFolder);
    layout->addWidget(start);
    layout->addWidget(stop);
    connect(_previousAction, &QLabelCustom::clicked, _displayPath, &DisplayPath::deleteLastElement);
    connect(_previousAction, &QLabelCustom::clicked, _manageElements, &ManagerElements::moveBackToFolder);

    _headerLayout->setLayout(layout);
}
