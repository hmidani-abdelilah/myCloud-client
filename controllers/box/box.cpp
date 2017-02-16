#include <QLabel>
#include <QPainter>
#include <QStyleOption>

#include "headers/box/box.h"
#include "globalinfo.h"

Box::Box(QString title)
{
    _gridLayout = new QGridLayout();
    QLabel *titleLabel = new QLabel(title);

    QFont f = QFont(Font::GlobalInfo::name, 16);
    f.setStyleName("Moyen");
    f.setLetterSpacing(QFont::PercentageSpacing, 105);
    f.setWeight(450);
    this->setAccessibleName("box");
    this->setStyleSheet("* {background-color:#FFFFFF;} [accessibleName=\"box\"] {border: 1px solid #" + Color::GlobalInfo::greyBorder + "; border-radius: 3px;}; ");

    titleLabel->setFixedHeight(20);
    titleLabel->setFont(f);
    _gridLayout->addWidget(titleLabel, 0, 0);

    setLayout(_gridLayout);
}

void Box::addLayout(QLayout *layout, int row, int columns) {
    _gridLayout->addLayout(layout, row, columns);
}

void Box::paintEvent(QPaintEvent *) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
