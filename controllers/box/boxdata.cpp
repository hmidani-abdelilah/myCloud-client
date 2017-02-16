#include "headers/box/boxdata.h"
#include "boxdatabaritem.h"
#include "globalinfo.h"
#include <QSpacerItem>

BoxData::BoxData(QString title) : Box(title)
{
    _vLayout = new QVBoxLayout();

    _vLayout->setSpacing(0);
    _vLayout->addWidget(new BoxDataBarItem(":/logo/fileLogo", "All of the files", "files"));
    _vLayout->addWidget(new BoxDataBarItem(":/logo/folderIcon", "All of the folder", "folders"));
    _vLayout->addWidget(new BoxDataBarItem(":/logo/picture", "All of the pictures", "pictures"));
    _vLayout->addWidget(new BoxDataBarItem(":/logo/movie", "All of the movies", "movies"));
    _vLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Expanding));

    addLayout(_vLayout, 1, 0);
}

void BoxData::setValueBarItem(QString name, qint64 size, int nbItem) {
    BoxDataBarItem *item;

    for (int i = 0 ; i < _vLayout->count() - 1 ; i++) {
        item = dynamic_cast<BoxDataBarItem *>(_vLayout->itemAt(i)->widget());
        if (item->longTitle() == name)
            item->setValue(BoxDataBarItem::TypeUnit::DIGITAL_STORAGE, size, nbItem);
    }
}
