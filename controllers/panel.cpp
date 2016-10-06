#include "panel.h"
#include <QScrollArea>
#include <QHBoxLayout>

Panel::Panel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Panel)
{
    ui->setupUi(this);

    _listBtnLeftMenu = new QVector<BtnLeftMenu*>();
    _managerElements = new ManagerElements();
    _transfertPage = new TransfertPage();
    QLabel *titleLeftMenu = new QLabel("Main");
    titleLeftMenu->setFont(QFont("Open Sans", 14));
    titleLeftMenu->setStyleSheet("padding-top:32px; "
                                 "padding-bottom:20px;"
                                 "padding-left:30px;"
                                 "background-color:#" + Color::GlobalInfo::grey + ";"
                                 "color:#747373");
    ui->toolBar2->setStyleSheet("#toolBar2 { background-color:white; border: 1px solid #" + Color::GlobalInfo::greyBorder + ";}");

    ui->leftMenuLayout->addWidget(titleLeftMenu);
    ui->leftMenuLayout->addWidget(this->createBtnLeftMenu(QPixmap (":/logo/cloud_download.png"), QString("DASHBOARD"), true));
    ui->leftMenuLayout->addWidget(this->createBtnLeftMenu(QPixmap (":/logo/cloud_download.png"), QString("DOWNLOAD")));
    ui->leftMenuLayout->addWidget(this->createBtnLeftMenu(QPixmap (":/logo/cloud_download.png"), QString("PROFIL")));

    configureHeaderBarInformationPath();

    QWidget* spacer = new QWidget();
    spacer->setStyleSheet("background-color:#" + Color::GlobalInfo::grey);
    spacer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    ui->leftMenuLayout->addWidget(spacer);
    ui->leftMenuLayout->setSpacing(0);
    ui->gridLayout->setSpacing(0);

    ui->stackedWidget->setStyleSheet("background-color:#" + Color::GlobalInfo::greyLight);
//    ui->scrollArea->setStyleSheet("QScrollArea { border: 1px solid #" + Color::GlobalInfo::greyBorder + ";} ");

    ui->gridDownloadWidget->setStyleSheet("#gridDownloadWidget { border: 1px solid #" + Color::GlobalInfo::greyBorder + ";}"
                                          " QWidget {background-color:white;}");
    ui->wPage2->setStyleSheet("background-color:white; border: 1px solid #" + Color::GlobalInfo::greyBorder + ";");
    ui->stackedWidget->setCurrentIndex(0);

    ui->scrollManagerElements->addWidget(_managerElements);
    ui->gridDownload->addLayout(_transfertPage, 0, 0);
}

Panel::~Panel()
{
    delete ui;
}

void Panel::configureHeaderBarInformationPath() {
    QWidget* spacerHorizontal = new QWidget();
    _previousAction = new QLabelCustom();

    QPixmap image(":/elements/previous");

    _previousAction->setPixmap(image);
    _previousAction->setFixedSize(20, 20);
    _previousAction->setScaledContents(true);
    _previousAction->setCursor(Qt::PointingHandCursor);
    _displayPath = new DisplayPath();
    connect(_displayPath, &DisplayPath::pathChanged, _managerElements, &ManagerElements::moveTo);

    _managerElements->setDisplayPath(_displayPath);

    spacerHorizontal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);

    ui->informationPath->addWidget(_previousAction);

    ui->informationPath->addLayout(_displayPath);
    ui->informationPath->addWidget(spacerHorizontal);

    connect(_previousAction, &QLabelCustom::clicked, _displayPath, &DisplayPath::deleteLastElement);
    connect(_previousAction, &QLabelCustom::clicked, _managerElements, &ManagerElements::moveBackToFolder);
}

void Panel::getPreviousPath() {
    //_managerElements->refreshFiles(_managerElements->getCurrentPath());
}

BtnLeftMenu* Panel::createBtnLeftMenu(QPixmap picture, QString title, bool value) {
    BtnLeftMenu *item = new BtnLeftMenu(picture, title);
    item->setActive(value);
    _listBtnLeftMenu->append(item);
    connect(item, SIGNAL(hasBeenClicked(QString)), this, SLOT(btnMenuClicked(QString)));
    return item;
}

void Panel::btnMenuClicked(QString title) {
 /*   UserRequest *createFileRequest = new UserRequest();

    createFileRequest->request(FileRequest::GET, UserRequest::Test);
*/


    for (int i = 0 ; i < _listBtnLeftMenu->length() ; i++) {
        if (title == _listBtnLeftMenu->at(i)->getTitle()) {
            _listBtnLeftMenu->at(i)->setActive(true);
            ui->stackedWidget->setCurrentIndex(i);
        }
        else
            _listBtnLeftMenu->at(i)->setActive(false);
    }
}
