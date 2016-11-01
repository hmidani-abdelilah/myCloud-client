#ifndef ELEMENT_H
#define ELEMENT_H

#include <QWidget>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QMenu>

namespace Ui {
    class Element;
}

class Element : public QWidget
{
    Q_OBJECT

public:
    explicit Element(QString title, QPixmap icon, QWidget *parent = 0);
    ~Element();

protected:
    Ui::Element *ui;
    QPixmap _image;

    QString _title;
    void setTitle(QString str);
    void setIcon(QPixmap picture);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QMenu _menu;

    void paintEvent(QPaintEvent *pe);
private:
    QPoint _dragStartPosition;
    void configureRightClick();

    void setStyleSheetElementActive();
private slots:
    void menuRequested(const QPoint &pos);

    void actionDelete(bool b);

signals:
    void hasBeenDoubleClicked(QString);
    void clicked();
};

#endif // ELEMENT_H
