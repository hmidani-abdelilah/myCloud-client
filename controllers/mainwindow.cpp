#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "image.h"
#include "globalinfo.h"
#include "factorybutton.h"
#include "factoryfont.h"
#include "jsonmanager.h"
#include "generator.h"
#include "httperror.h"

#include <QLabel>
#include <QVariant>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _loginView = new Login();
    ui->stackedWidget->addWidget(_loginView);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->setStyleSheet("background-color:#282D31");
    ui->toolBar->hide();
    connect(_loginView, &Login::connexionSuccess, this, &MainWindow::activeMainView);
    connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(stackerWidgetChanged(int)));
    ui->toolBar->setStyleSheet("background-color:#" + Color::GlobalInfo::white + "; spacing:0px;");

    _userRequest = new UserRequest();
    connect(_userRequest, &UserRequest::signalLogOut, this, &MainWindow::slotDisconnected);

    _btnParamsAccount = new QLabelCustom(":/logo/down-arrow", 15, 15);
    connect(_btnParamsAccount, &QLabelCustom::clickedPos, this, &MainWindow::menuParamsRequested);

    QAction *disconnection = new QAction("Log out");
    connect(disconnection, &QAction::triggered, this, &MainWindow::actionDisconnection);
    _menu.addAction(disconnection);

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

    QFont f = QFont(Font::GlobalInfo::name, 20);
    f.setStyleName("Moyen");
    f.setLetterSpacing(QFont::PercentageSpacing, 120);
    f.setWeight(450);

    _pageName = new QLabelCustom("Dashboard");
    _pageName->setFont(FactoryFont(Font::GlobalInfo::name).size(24).styleName("Normal").weight(450).letterSpacing(120).gen());
    _pageName->setStyleSheet("padding-left: 20px; color:#" + Color::GlobalInfo::mainBleu);
    _pageName->setFixedHeight(84);

    logoSection->setLayout(layoutLogo);
    logoSection->setStyleSheet("background-color:#" + Color::GlobalInfo::greySolid + "; padding-left: 18px;");


    ui->toolBar->addWidget(logoSection);
    ui->toolBar->setFixedHeight(84);
    ui->toolBar->addWidget(_pageName);
    ui->toolBar->addWidget(spacer);
    QWidget *infoSection = new QWidget();

    /* MAIN HEADER BAR */

    QHBoxLayout *hLayout = new QHBoxLayout();
    _labelCustom = new QLabelCustom(":/logo/avatar", 50, 50);
    _labelLastName = new QLabelCustom("");
    _labelFirstName = new QLabelCustom("");
    _labelFreeSize = new QLabelCustom("");
    QVBoxLayout  *vLayout = new QVBoxLayout();

    hLayout->setContentsMargins(0, 0, 20, 0);
    vLayout->setSpacing(0);
    _labelLastName->setFont(FactoryFont(Font::GlobalInfo::name).size(14).styleName("Moyen").weight(450).letterSpacing(115).gen());
    _labelLastName->setFixedHeight(20);
    _labelLastName->setAlignment(Qt::AlignRight);
    _labelLastName->setStyleSheet("color:#" + Color::GlobalInfo::grey);

    _labelFirstName->setFont(FactoryFont(Font::GlobalInfo::name).size(14).styleName("Moyen").weight(450).letterSpacing(115).gen());
    _labelFirstName->setFixedHeight(20);
    _labelFirstName->setAlignment(Qt::AlignRight);
    _labelFirstName->setStyleSheet("color:#" + Color::GlobalInfo::grey);

    _labelFreeSize->setFont(FactoryFont(Font::GlobalInfo::name).size(11).styleName("Moyen").weight(450).letterSpacing(115).gen());
    _labelFreeSize->setFixedHeight(30);
    _labelFreeSize->setAlignment(Qt::AlignRight);
    _labelFreeSize->setStyleSheet("color:#" + Color::GlobalInfo::greyText + "; padding-top:10px;");

    vLayout->addWidget(_labelLastName);
    vLayout->addWidget(_labelFirstName);
    vLayout->addWidget(_labelFreeSize);
    vLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    vLayout->setContentsMargins(15, 15, 0, 15);
    hLayout->setSpacing(10);
    hLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));
    hLayout->addLayout(vLayout);
    hLayout->addWidget(new QLabelCustom(":/logo/line", 20, 50));
    hLayout->addWidget(_labelCustom);
    hLayout->addWidget(_btnParamsAccount);

    infoSection->setLayout(hLayout);

    infoSection->setFixedHeight(84);
    ui->toolBar->addWidget(infoSection);

    ui->toolBar->setMovable(false);
}

void MainWindow::menuParamsRequested(const QPoint & pos) {
    _menu.popup(mapToGlobal(pos));
}

void MainWindow::actionDisconnection(bool) {
    _userRequest->request(UserRequest::Type::GET, UserRequest::LogOut);
}

void MainWindow::slotChangePageName(QString name) {
    QString value = name.toLower();
    value[0] = value[0].toUpper();
    _pageName->setText(value);
}

void MainWindow::activeMainView(QNetworkReply* reply)
{
    QList<QByteArray> headerList = reply->rawHeaderList();

    _labelFirstName->setText(reply->rawHeader("firstName"));
    _labelLastName->setText(reply->rawHeader("lastName"));
    _labelFreeSize->setText(Generator::getFormatSize(reply->rawHeader("totalSizeFree").toLongLong()) + " free");
    QByteArray data = reply->readAll();

    if (data.length() > 0) {
        QPixmap img;

        img.loadFromData(data);
        _labelCustom->setPixmap(img);
    }
    else
        _labelCustom = new QLabelCustom(":/logo/avatar", 50, 50);


    _mainPanel = new Panel();

    connect(_mainPanel, &Panel::pageNameChange, this, &MainWindow::slotChangePageName);
    ui->stackedWidget->addWidget(_mainPanel);
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

void MainWindow::slotDisconnected(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError)
        throw HttpError(reply);

    _loginView->clearForm();
    ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget->setStyleSheet("background-color:#282D31");
    if (_mainPanel != NULL)
        delete _mainPanel;
}

MainWindow::~MainWindow()
{
    delete ui;
}
