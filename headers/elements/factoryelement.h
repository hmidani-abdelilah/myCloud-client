#ifndef FACTORYELEMENT_H
#define FACTORYELEMENT_H

#include "managerelements.h"
#include "fileelement.h"
#include "folderelement.h"

class ManagerElements;
class FactoryElement : QObject
{
    Q_OBJECT

public:
    FactoryElement(const ManagerElements *managerElement);

    FolderElement *generateFolderElement(QString name, QString pathServer);

    FileElement *generateFileElement(StatsElement::Stats stats);
    FileElement *generateFileElement(QString name, qint64 size, QString pathServer);
    inline void setDraggableMode(Element::DraggableMode draggableMode = Element::EMIT) {_draggableMode = draggableMode;}

private:
    const ManagerElements *_managerElement;
    Element::DraggableMode _draggableMode;
};

#endif // FACTORYELEMENT_H
