#include "btnleftmenu.h"
#include "ui_btnleftmenu.h"
#include "globalinfo.h"
#include <QPixmap>
#include <Qt>
#include <QMouseEvent>
#include <QPainter>
#include "globalinfo.h"

BtnLeftMenu::BtnLeftMenu(QPixmap image, QString text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BtnLeftMenu)
{
    ui->setupUi(this);
    _title = text;
    _logo = image;

    this->setStyleSheet("background-color:#" + Color::GlobalInfo::grey);
    ui->logo->setScaledContents(true);
    ui->title->setText(text);

    QFont f = QFont(Font::GlobalInfo::name, 12);
    f.setStyleName("Moyen");
    ui->title->setFont(f);
    ui->horizontalLayout->setSpacing(0);
}

BtnLeftMenu::~BtnLeftMenu()
{
    delete ui;
}

QString BtnLeftMenu::getTitle() {
    return _title;
}

void BtnLeftMenu::changeLogoColor(QString color) {
    QPainter painters(&_logo);
    painters.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painters.fillRect(_logo.rect(), QColor("#" + color));
    painters.end();
    ui->logo->setPixmap(_logo);
}

void BtnLeftMenu::setActive(bool value) {
    if (value == true) {
        this->setStyleSheet("background-color:#" + Color::GlobalInfo::greyLight);
        this->ui->title->setStyleSheet("color:#" + Color::GlobalInfo::grey);

        this->ui->line->setStyleSheet("background-color:#" + Color::GlobalInfo::lightBlue);
        changeLogoColor(Color::GlobalInfo::lightBlue);
    }
    else {
        this->setStyleSheet("background-color:#" + Color::GlobalInfo::grey);
        this->ui->title->setStyleSheet("color:#FFFFFF");
        this->ui->line->setStyleSheet("background-color:#" + Color::GlobalInfo::grey);
        changeLogoColor(Color::GlobalInfo::white);
    }
}

void BtnLeftMenu::mousePressEvent ( QMouseEvent * event ) {
    emit hasBeenClicked(_title);
}
