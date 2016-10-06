#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "panel.h"
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
    QLabel *titleApp = new QLabel("myCloud");
    titleApp->setFixedSize(210, 70);
    titleApp->setAlignment(Qt::AlignCenter);
    titleApp->setStyleSheet("background-color:#" + Color::GlobalInfo::greySolid + "; color : white; font-size: 16px;");

    ui->toolBar->addWidget(titleApp);
    ui->toolBar->addWidget(spacer);
    //ui->toolBar->setStyleSheet("border-bottom: 1px solid #" + Color::GlobalInfo::greyBorder + ";");
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
