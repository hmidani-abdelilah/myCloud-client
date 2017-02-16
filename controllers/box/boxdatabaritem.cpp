#include "headers/box/boxdatabaritem.h"
#include "generator.h"

#include <QHBoxLayout>

BoxDataBarItem::BoxDataBarItem(QString picture, QString longTitle, QString title)
{
    QHBoxLayout *layout = new QHBoxLayout();
    QLabel *longTitleLabel = new QLabel(longTitle);
    _longTitle = longTitle;
    _titleLabel = new QLabel(title);
    _sizeLabel = new QLabel("0 Mo/s");

    _titleLabel->setFixedHeight(30);
    _sizeLabel->setFixedHeight(30);
    longTitleLabel->setFixedHeight(30);

    _title = title;

    longTitleLabel->setMinimumWidth(130);
    _titleLabel->setMinimumWidth(100);

    _titleLabel->setAlignment(Qt::AlignLeft);
    _sizeLabel->setAlignment(Qt::AlignRight);
    longTitleLabel->setAlignment(Qt::AlignLeft);

    layout->addWidget(new QLabelCustom(picture, 13, 13));
    layout->addWidget(longTitleLabel);
    if (title.length() > 0)
        layout->addWidget(_titleLabel);
    layout->addWidget(_sizeLabel);
    this->setFixedHeight(30);
    setLayout(layout);
}

void BoxDataBarItem::setValue(TypeUnit type, qint64 size, int nbItem)
{
    if (_title.length() > 0)
        _titleLabel->setText(QString::number(nbItem) + " " + _title);

    if (type == TypeUnit::DIGITAL_STORAGE)
        _sizeLabel->setText(Generator::getFormatSize(size));
    else if (type == TypeUnit::SPEED)
        _sizeLabel->setText(Generator::getFormatSpeed(size));
}
