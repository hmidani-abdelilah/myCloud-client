#include "panel.h"
#include <QScrollArea>
#include <QHBoxLayout>

Panel::Panel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Panel)
{
    ui->setupUi(this);

    _listBtnLeftMenu = new QVector<BtnLeftMenu*>();
    _viewFilesPage = new ViewFilesPage();
    _transfertPage = new TransfertPage();
    _sortPage = new SortPage();
    _headerManageElements = new QHBoxLayout();
    _headerTransfertPage = new QHBoxLayout();
    _listPages = new QVector<QWidget*>();

    QLabel *titleLeftMenu = new QLabel("Main");

    titleLeftMenu->setFont(QFont("Open Sans", 14));
    titleLeftMenu->setStyleSheet("padding-top:32px; "
                                 "padding-bottom:20px;"
                                 "padding-left:30px;"
                                 "background-color:#" + Color::GlobalInfo::grey + ";"
                                 "color:#747373");
    ui->headerBar->setStyleSheet("#headerBar { background-color:white; border: 1px solid #" + Color::GlobalInfo::greyBorder + ";}");

    ui->leftMenuLayout->addWidget(titleLeftMenu);
    ui->leftMenuLayout->addWidget(this->createBtnLeftMenu(QPixmap (":/logo/menu"), QString("DASHBOARD"), true));
    ui->leftMenuLayout->addWidget(this->createBtnLeftMenu(QPixmap (":/logo/cloud_download"), QString("DOWNLOAD")));
    ui->leftMenuLayout->addWidget(this->createBtnLeftMenu(QPixmap (":/logo/cloud_download"), QString("ORDERING")));
    ui->leftMenuLayout->addWidget(this->createBtnLeftMenu(QPixmap (":/logo/user"), QString("PROFIL")));

    QWidget* spacer = new QWidget();
    spacer->setStyleSheet("background-color:#" + Color::GlobalInfo::grey);
    spacer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    ui->leftMenuLayout->addWidget(spacer);
    ui->leftMenuLayout->setSpacing(0);
    ui->gridLayout->setSpacing(0);

    ui->stackedWidget->setStyleSheet("background-color:#" + Color::GlobalInfo::greyLight);
    ui->scrollArea->setStyleSheet("#scrollArea { border: 1px solid #" + Color::GlobalInfo::greyBorder + ";} ");

    ui->gridDownloadWidget->setStyleSheet("#gridDownloadWidget { border: 1px solid #" + Color::GlobalInfo::greyBorder + ";}"
                                          " QWidget {background-color:white;}");

    ui->gridOrderWidget->setStyleSheet("#gridDownloadWidget { border: 1px solid #" + Color::GlobalInfo::greyBorder + ";}"
                                          " QWidget {background-color:white;}");

    ui->wPage2->setStyleSheet("background-color:white; border: 1px solid #" + Color::GlobalInfo::greyBorder + ";");
    ui->stackedWidget->setCurrentIndex(0);

    /* Append page in the same order than button left for header bar */

    _listPages->append(_viewFilesPage);
    _listPages->append(_transfertPage);
    _listPages->append(_sortPage);
    initializeHeaderBar();

    /* ADD PAGE TO VIEW */

    ui->scrollManagerElements->addWidget(_viewFilesPage);
    ui->gridDownload->addWidget(_transfertPage);
    ui->gridOrder->addWidget(_sortPage);
}

Panel::~Panel()
{
    delete ui;
}

void Panel::initializeHeaderBar() {
    for (int i = 0 ; i < _listPages->count() ; i++) {
        ui->headerBarLayout->addWidget(dynamic_cast<HeaderBar *>(_listPages->at(i))->getHeaderBarLayout());
        ui->headerBarLayout->itemAt(i)->widget()->hide();
    }
    ui->headerBarLayout->itemAt(0)->widget()->show();
}

BtnLeftMenu* Panel::createBtnLeftMenu(QPixmap picture, QString title, bool value) {
    BtnLeftMenu *item = new BtnLeftMenu(picture, title);
    item->setActive(value);
    _listBtnLeftMenu->append(item);
    connect(item, SIGNAL(hasBeenClicked(QString)), this, SLOT(btnMenuClicked(QString)));
    return item;
}

void Panel::btnMenuClicked(QString title) {
    for (int i = 0 ; i < _listBtnLeftMenu->length() ; i++) {
        if (title == _listBtnLeftMenu->at(i)->getTitle()) {
            _listBtnLeftMenu->at(i)->setActive(true);
            ui->stackedWidget->setCurrentIndex(i);
            if (ui->stackedWidget->currentIndex() == 0) {
                _viewFilesPage->reloadPage();
            }
            for (int index = 0 ; index < ui->headerBarLayout->count() ; index++) {
                if (index == i) {
                    ui->headerBarLayout->itemAt(index)->widget()->show();
                }
                else {
                    ui->headerBarLayout->itemAt(index)->widget()->hide();
                }
            }
            ui->headerBarLayout->update();
            ui->headerBarLayout->activate();
        }
        else
            _listBtnLeftMenu->at(i)->setActive(false);
    }
}
