#include "displaypath.h"
#include "elementpath.h"
#include <QPushButton>

DisplayPath::DisplayPath() : QHBoxLayout()
{
    ElementPath *cloud = new ElementPath(":/logo/cloud2", 29, 29, this->count() + 1);
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
        delete this->takeAt(this->count() - 1)->widget();
        delete this->takeAt(this->count() - 1)->widget();
        this->update();
    }
}

void DisplayPath::onClickElement(int pos) {
    while (this->count() != pos) {
        deleteLastElement();
    }

    QStringList list;
    for (int i = 0 ; i < this->count() ; i++) {
        list.append(((QLabel *)(this->itemAt(i)->widget()))->text());
    }
    emit pathChanged(list); //QStringList
}
