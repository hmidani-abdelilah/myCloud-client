#include "factoryelement.h"

FactoryElement::FactoryElement(const ManagerElements *managerElement)
{
    _managerElement = managerElement;
}

FileElement *FactoryElement::generateFileElement(QString name, quint64 size, QString path) {
    FileElement *file = new FileElement(name, size, path);
    connect(file, &FileElement::selected, _managerElement, &ManagerElements::elementHasBeenClicked);
    connect(file, &FileElement::isDragged, _managerElement, &ManagerElements::elementsHasBeenDragged);

    return file;
}

FolderElement *FactoryElement::generateFolderElement(QString name, QString pathServer) {
    FolderElement *folder = new FolderElement(name, pathServer);

    connect(folder, &FolderElement::selected, _managerElement, &ManagerElements::elementHasBeenClicked);
    connect(folder, &FolderElement::hasBeenDoubleClicked, _managerElement, &ManagerElements::folderHasBeenDoubleClicked);
    connect(folder, &FolderElement::hasBeenDoubleClicked, _managerElement, &ManagerElements::moveInFolder);
    connect(folder, &FolderElement::isDragged, _managerElement, &ManagerElements::elementsHasBeenDragged);

    return folder;
}
