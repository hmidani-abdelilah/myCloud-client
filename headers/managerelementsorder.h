#ifndef MANAGERELEMENTSORDER_H
#define MANAGERELEMENTSORDER_H

#include "managerelements.h"

class ManagerElementsOrder : public ManagerElements
{
public:
    ManagerElementsOrder(QWidget *widget = 0);

protected slots:
    void elementsHasBeenDragged();
};

#endif // MANAGERELEMENTSORDER_H
