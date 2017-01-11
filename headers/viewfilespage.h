#ifndef VIEWFILESPAGE_H
#define VIEWFILESPAGE_H

#include "managerelements.h"
#include "page.h"

class ViewFilesPage : public Page
{
public:
    ViewFilesPage(QWidget *parent = 0);

    void reloadPage();
protected:
    void setHeaderBar();

private:
    ManagerElements     *_manageElements;

    QLabelCustom        *_previousAction;
    DisplayPath         *_displayPath;
};

#endif // VIEWFILESPAGE_H
