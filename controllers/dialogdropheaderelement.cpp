#include "headers/dialogdropheaderelement.h"
#include "ui_dialogdropheaderelement.h"
#include "globalinfo.h"
#include "generator.h"
#include <QPainter>

DialogDropHeaderElement::DialogDropHeaderElement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogDropHeaderElement)
{
    ui->setupUi(this);
    QFont fontTitle;
    QFont fontSize;

    fontTitle.setPointSize(16);
    fontTitle.setBold(true);

    fontSize.setItalic(true);
    fontSize.setPointSize(18);

    ui->_title->setFont(fontTitle);
    ui->_size->setFont(fontSize);

    this->setStyleSheet("background-color:#" + Color::GlobalInfo::white);

    //this->ui->_mainLayout->widget()->setStyleSheet("background-color:#" + Color::GlobalInfo::white);
}

DialogDropHeaderElement::~DialogDropHeaderElement()
{
    delete ui;
}

void DialogDropHeaderElement::setInformation(QPixmap pixmap, QString title, QString path, QString createAt, quint64 size) {
    //ui->_picture->setPixmap(pixmap);
    setIcon(pixmap);
    ui->_title->setText(title);
    ui->_path->setText(path);
    ui->_createdAt->setText(createAt);
    ui->_size->setText(Generator::getFormatSize(size));
}

void DialogDropHeaderElement::setIcon(QPixmap picture) {
    int w = ui->_picture->width();
    int h = ui->_picture->height();

    QPixmap image = picture.scaled(w,h,Qt::KeepAspectRatio);

    qDebug("%d", image.width());
    ui->_picture->setMinimumSize(image.width(), image.height());
    ui->_picture->setPixmap(image);
}

void DialogDropHeaderElement::paintEvent(QPaintEvent *pe) {
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
