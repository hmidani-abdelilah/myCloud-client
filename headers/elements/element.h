#ifndef ELEMENT_H
#define ELEMENT_H

#include <QWidget>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QMenu>
#include <QStandardItemModel>
#include "statselement.h"

namespace Ui {
class Element;
}

class Element : public QWidget, public StatsElement
{
    Q_OBJECT

public:
    explicit Element(QString name, qint64 size, qint64 transferedSize, QString pathServer, QString pathClient, TypeElement typeElement, Status status, QWidget *parent = 0);
    Element(Stats stats, QWidget *parent);
    ~Element();

    enum DraggableMode {
        DISABLE,
        NORMAL,
        EMIT
    };

public:
    inline TypeElement type() {return _typeElement;} // changer le nom de la fonction typeElement - a surrpime
    void setSelected(bool value);
    inline void setDraggableMode(DraggableMode draggableMode = EMIT) {_draggableMode = draggableMode;}
    inline bool isSelected() {return _isSelected;}

protected:
    Ui::Element *ui;

    void setTitle(QString str);
    void mouseDoubleClickEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    QMenu _menu;
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    void setIcon(QPixmap picture);
   // bool event(QEvent *event);

private:
    QPoint _dragStartPosition;
    void configureRightClick();

    bool            _isSelected;
    DraggableMode   _draggableMode;

private slots:
    void menuRequested(const QPoint &pos);

    void actionDelete(bool);
    void actionDownload(bool);

signals:
    void hasBeenDoubleClicked(QString);
    void selected(Stats);
    void unselected(Stats);
    void isDragged();
    void isDeleted();

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // ELEMENT_H
