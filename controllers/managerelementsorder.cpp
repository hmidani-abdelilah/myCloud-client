#include "managerelementsorder.h"

ManagerElementsOrder::ManagerElementsOrder(QWidget *widget) : ManagerElements(widget)
{

}

void ManagerElementsOrder::elementsHasBeenDragged() {
    QDrag *drag = new QDrag(this);
    //drag->setDragCursor(QPixmap(":/logo/cloud2"), Qt::MoveAction);
    QMimeData *mimeData = new QMimeData;

    drag->setPixmap(_itemsSelected[0].image);
    QString listPathsFiles = "";
    for (int index = 0 ; index < _itemsSelected.length() ; index++) {
        if (index > 0)
            listPathsFiles += ",";

        if (_itemsSelected[index].pathServer.length() > 0) {
            listPathsFiles += _itemsSelected[index].pathServer + "/";
        }
        listPathsFiles += _itemsSelected[index].name;
    }
    mimeData->setData("myapplication::stringlist", QByteArray(listPathsFiles.toStdString().c_str()));
    drag->setMimeData(mimeData);
    drag->exec(Qt::MoveAction);
}
