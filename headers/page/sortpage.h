#ifndef SORTPAGE_H
#define SORTPAGE_H

#include "treerepositoryserver.h"
#include "managerelementsorder.h"
#include "managerelements.h"
#include "page.h"

class SortPage : public Page
{
public:
    SortPage(QWidget *parent = 0);

protected:
    void setHeaderBar();

private:
    ManagerElementsOrder                     *_manageElements;

    QLabelCustom                        *_previousAction;
    DisplayPath                         *_displayPath;
    TreeRepositoryServer                *_treeRepositoryServer;
};

#endif // SORTPAGE_H
