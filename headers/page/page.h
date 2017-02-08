#ifndef PAGE_H
#define PAGE_H

#include <Qwidget>
#include "headerbar.h"

class Page : public QWidget, public HeaderBar
{
public:
    Page();
};

#endif // PAGE_H
