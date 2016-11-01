#ifndef HEADERBAR_H
#define HEADERBAR_H

#include <QHBoxLayout>
#include <QWidget>

class HeaderBar
{
public:
    HeaderBar();

protected:
    QWidget *_headerLayout;
    inline virtual void setHeaderBar() = 0;

public:
    inline QWidget* getHeaderBarLayout() {return _headerLayout;}
};

#endif // HEADERBAR_H
