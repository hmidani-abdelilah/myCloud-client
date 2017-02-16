#include "boxtranfert.h"
#include "boxdatabaritem.h"
#include "globalinfo.h"

#include <QSpacerItem>

BoxTranfert::BoxTranfert(QString title) : Box(title)
{
    _vLayout = new QVBoxLayout();

    _vLayout->setSpacing(0);

    Server::GlobalInfo::uploadBarItem = new BoxDataBarItem(":/logo/upload", "Upload");
    Server::GlobalInfo::downloadBarItem = new BoxDataBarItem(":/logo/download", "Download");

    _vLayout->addWidget(Server::GlobalInfo::uploadBarItem);
    _vLayout->addWidget(Server::GlobalInfo::downloadBarItem);
    _vLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    addLayout(_vLayout, 1, 0);
}

void BoxTranfert::setValueBarItem(QString name, qint64 size) {
    BoxDataBarItem *item;

    for (int i = 0 ; i < _vLayout->count() - 1 ; i++) {
        item = dynamic_cast<BoxDataBarItem *>(_vLayout->itemAt(i)->widget());
        if (item->longTitle() == name)
            item->setValue(BoxDataBarItem::TypeUnit::SPEED, size);
    }
}
