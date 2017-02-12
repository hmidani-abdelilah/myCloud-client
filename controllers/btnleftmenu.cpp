#include "btnleftmenu.h"
#include "ui_btnleftmenu.h"
#include "globalinfo.h"
#include "generator.h"

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

    this->setCursor(Qt::PointingHandCursor);
    this->setStyleSheet("background-color:#" + Color::GlobalInfo::grey);
    ui->logo->setScaledContents(true);
    ui->title->setText(text);

    QFont f = QFont(Font::GlobalInfo::name, 11);
    f.setStyleName("Moyen");
    f.setLetterSpacing(QFont::PercentageSpacing, 105);
    f.setWeight(450);
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

void BtnLeftMenu::setActive(bool value) {
    if (value == true) {
        this->setStyleSheet("background-color:#" + Color::GlobalInfo::greyLight);
        this->ui->title->setStyleSheet("color:#" + Color::GlobalInfo::grey);

        this->ui->line->setStyleSheet("background-color:#" + Color::GlobalInfo::mainBleu);
        ui->logo->setPixmap(Generator::changeLogoColor(_logo, Color::GlobalInfo::mainBleu));
    }
    else {
        this->setStyleSheet("background-color:#" + Color::GlobalInfo::grey );
        this->ui->title->setStyleSheet("color:#FFFFFF");
        this->ui->line->setStyleSheet("background-color:#" + Color::GlobalInfo::grey);
        ui->logo->setPixmap(Generator::changeLogoColor(_logo, Color::GlobalInfo::white));
    }
}

void BtnLeftMenu::mousePressEvent ( QMouseEvent * ) {
    emit hasBeenClicked(_title);
}
