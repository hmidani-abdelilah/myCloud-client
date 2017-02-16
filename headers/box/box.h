#ifndef BOX_H
#define BOX_H

#include <QWidget>
#include <QGridLayout>
#
class Box : public QWidget
{
public:
    Box(QString title);

    void addLayout(QLayout *layout, int row, int columns);

protected:
    void paintEvent(QPaintEvent *);
private:
    QGridLayout *_gridLayout;
};

#endif // BOX_H
