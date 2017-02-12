#include "factoryelement.h"

FactoryElement::FactoryElement(const ManagerElements *managerElement)
{
    _managerElement = managerElement;
    _draggableMode = Element::EMIT;
}

FileElement *FactoryElement::generateFileElement(QString name, qint64 size, QString pathServer) {
    FileElement *file = new FileElement(name, size, 0, pathServer, "", StatsElement::Status::NONE);
    createConnection(file);
    return file;
}

FileElement *FactoryElement::generateFileElement(StatsElement::Stats stats) {
    FileElement *file = new FileElement(stats);
    createConnection(file);
    return file;
}

FileElement *FactoryElement::createConnection(FileElement *file) {
    connect(file, &FileElement::selected, _managerElement, &ManagerElements::elementHasBeenClicked);
    connect(file, &FileElement::unselected, _managerElement, &ManagerElements::elementHasBeenUnselected);
    connect(file, &FileElement::isDragged, _managerElement, &ManagerElements::elementsHasBeenDragged);
    connect(file, &FileElement::isDeleted, _managerElement, &ManagerElements::deleteFileSelectedOnServer);
    file->setDraggableMode(_draggableMode);
    return file;
}

FolderElement *FactoryElement::generateFolderElement(QString name, QString pathServer) {
    FolderElement *folder = new FolderElement(name, 0, 0, pathServer, "", StatsElement::Status::NONE);

    connect(folder, &FolderElement::selected, _managerElement, &ManagerElements::elementHasBeenClicked);
    connect(folder, &FolderElement::unselected, _managerElement, &ManagerElements::elementHasBeenUnselected);
    connect(folder, &FolderElement::hasBeenDoubleClicked, _managerElement, &ManagerElements::folderHasBeenDoubleClicked);
    connect(folder, &FolderElement::hasBeenDoubleClicked, _managerElement, &ManagerElements::moveInFolder);
    connect(folder, &FolderElement::isDragged, _managerElement, &ManagerElements::elementsHasBeenDragged);
    folder->setDraggableMode(_draggableMode);
    return folder;
}
