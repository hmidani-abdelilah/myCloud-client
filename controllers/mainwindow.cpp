#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "panel.h"
#include "image.h"
#include "globalinfo.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Login *log = new Login();
    ui->stackedWidget->addWidget(log);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->setStyleSheet("background-color:#282D31");
    ui->toolBar->hide();
    connect(log, SIGNAL(connexionSuccess()), this, SLOT(activeMainView()));
    connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(stackerWidgetChanged(int)));
    ui->toolBar->setStyleSheet("background-color:#" + Color::GlobalInfo::white + "; spacing:0px;");

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *layoutLogo = new QHBoxLayout();

    QLabel *titleApp = new QLabel("myCloud");
    titleApp->setFixedSize(120, 70);
    titleApp->setStyleSheet("color : white; font-size: 16px; padding-left: 10px;");

    QLabel *labelimage = new QLabel();
    labelimage->setPixmap(Image::fromSvgToPixmap(QSize(40, 23), ":/logo/cloudLogo"));

    layoutLogo->addWidget(labelimage);
    layoutLogo->addWidget(titleApp);

    QWidget *logoSection = new QWidget();
    logoSection->setLayout(layoutLogo);
    logoSection->setStyleSheet("background-color:#" + Color::GlobalInfo::greySolid + "; padding-left: 18px;");
    ui->toolBar->addWidget(logoSection);
    ui->toolBar->addWidget(spacer);
    ui->toolBar->setMovable(false);
}

void MainWindow::activeMainView()
{
    Panel *mainPanel = new Panel();
    ui->stackedWidget->addWidget(mainPanel);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::stackerWidgetChanged(int index) {
    switch (index) {
    case 0:
        ui->stackedWidget->setStyleSheet("background-color:#" + Color::GlobalInfo::greySolid);
        ui->toolBar->hide();
        break;
    case 1:
        ui->stackedWidget->setStyleSheet("");
        ui->toolBar->show();
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
