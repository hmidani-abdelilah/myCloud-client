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

struct DataElement {
    QPixmap image;
    QString name;
    QString path;
    quint64 size;
};

class Element : public QWidget, public StatsElement
{
    Q_OBJECT

public:

    explicit Element(QString name, quint64 size, quint64 transferedSize, QString pathServer, QString pathClient, TypeElement typeElement, Status status, QWidget *parent = 0);
    Element(Stats stats, QWidget *parent);
    ~Element();

public:
    inline TypeElement type() {return _typeElement;} // changer le nom de la fonction typeElement - a surrpime
    void setSelected(bool value);

protected:
    Ui::Element *ui;
    QPixmap _image;

    void setTitle(QString str);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QMenu _menu;
    void paintEvent(QPaintEvent *pe);
    void setIcon(QPixmap picture);
   // bool event(QEvent *event);

private:
    QPoint _dragStartPosition;
    void configureRightClick();

    bool         _isSelected;

    DataElement getDataElement();

private slots:
    void menuRequested(const QPoint &pos);

    void actionDelete(bool b);
    void actionDownload(bool b);
    void actionDownloadIn(bool b);

    void targetChangedSlot(QObject *newTarget);

signals:
    void hasBeenDoubleClicked(QString);
    void selected(DataElement);
    void isDragged();

protected:
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
protected slots:
    void dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
};

#endif // ELEMENT_H
