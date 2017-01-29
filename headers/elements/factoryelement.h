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
    FileElement *generateFileElement(QString name, quint64 size, QString pathServer);
private:
    const ManagerElements *_managerElement;
};

#endif // FACTORYELEMENT_H
