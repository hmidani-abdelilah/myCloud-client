#include "factoryelement.h"

FactoryElement::FactoryElement(const ManagerElements *managerElement)
{
    _managerElement = managerElement;
    _draggableMode = Element::EMIT;
}

FileElement *FactoryElement::generateFileElement(QString name, qint64 size, QString pathServer) {
    FileElement *file = new FileElement(name, size, 0, pathServer, "", StatsElement::Status::NONE);
    connect(file, &FileElement::selected, _managerElement, &ManagerElements::elementHasBeenClicked);
    connect(file, &FileElement::isDragged, _managerElement, &ManagerElements::elementsHasBeenDragged);
    file->setDraggableMode(_draggableMode);
    return file;
}

FileElement *FactoryElement::generateFileElement(StatsElement::Stats stats) {
    FileElement *file = new FileElement(stats);
    connect(file, &FileElement::selected, _managerElement, &ManagerElements::elementHasBeenClicked);
    connect(file, &FileElement::isDragged, _managerElement, &ManagerElements::elementsHasBeenDragged);
    file->setDraggableMode(_draggableMode);
    return file;
}

FolderElement *FactoryElement::generateFolderElement(QString name, QString pathServer) {
    FolderElement *folder = new FolderElement(name, 0, 0, pathServer, "", StatsElement::Status::NONE);

    connect(folder, &FolderElement::selected, _managerElement, &ManagerElements::elementHasBeenClicked);
    connect(folder, &FolderElement::hasBeenDoubleClicked, _managerElement, &ManagerElements::folderHasBeenDoubleClicked);
    connect(folder, &FolderElement::hasBeenDoubleClicked, _managerElement, &ManagerElements::moveInFolder);
    connect(folder, &FolderElement::isDragged, _managerElement, &ManagerElements::elementsHasBeenDragged);
    folder->setDraggableMode(_draggableMode);
    return folder;
}
