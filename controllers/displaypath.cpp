#include "displaypath.h"
#include "elementpath.h"
#include <QPushButton>

DisplayPath::DisplayPath() : QHBoxLayout()
{
    ElementPath *cloud = new ElementPath(":/logo/cloudLogo", 29, 29, this->count() + 1);
    connect(cloud, &ElementPath::clicked, this, &DisplayPath::onClickElement);
    this->addWidget(cloud);
}

void DisplayPath::addElement(QString element) {
    if (element.size() <= 0)
        return;
    this->addWidget(new QLabelCustom(":/logo/pathSpacer", 14, 14));
    ElementPath *label = new ElementPath(element, this->count() + 1);
    connect(label, &ElementPath::clicked, this, &DisplayPath::onClickElement);
    label->setCursor(Qt::PointingHandCursor);

    this->addWidget(label);
}

void DisplayPath::deleteLastElement() {
    if (this->count() > 1) {
        QLayoutItem *layoutItem = this->takeAt(this->count() - 1);
        delete layoutItem->widget();
        delete layoutItem;

        layoutItem = this->takeAt(this->count() - 1);
                delete layoutItem->widget();
                delete layoutItem;
        this->update();
    }
}

void DisplayPath::onClickElement(int pos) {
    while (this->count() != pos) {
        deleteLastElement();
    }
    QStringList list;
    QString str;
    for (int i = 0 ; i < this->count() ; i++) {
        str = ((QLabel *)(this->itemAt(i)->widget()))->text();
        if (str.length() > 0)
            list.append(str);
    }
    emit pathChanged(list); //QStringList
}
