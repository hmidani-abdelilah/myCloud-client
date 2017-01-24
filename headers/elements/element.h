#ifndef ELEMENT_H
#define ELEMENT_H

#include <QWidget>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QMenu>
#include <QStandardItemModel>

//#include "filemanager.h"

namespace Ui {
class Element;
}

struct DataElement {
    QPixmap image;
    QString name;
    QString path;
    quint64 size;
};

class Element : public QWidget
{
    Q_OBJECT

public:
    enum Type {
        UNDEFINED,
        FILE,
        FOLDER
    };

    explicit Element(QString title, quint64 size, QString path, Type type = UNDEFINED, QWidget *parent = 0);
    ~Element();

public:
    inline QString title() {return _title;}
    inline QString path() {return _path;}
    inline quint64 size() {return _size;}
    inline Type type() {return _type;}
    void setSelected(bool value);

protected:
    Ui::Element *ui;
    QPixmap _image;

    QString _title;
    void setTitle(QString str);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QMenu _menu;
    void paintEvent(QPaintEvent *pe);
    void setIcon(QPixmap picture);
    Type _type;
   // bool event(QEvent *event);

private:
    QPoint _dragStartPosition;
    void configureRightClick();

    int          _size;
    QString      _path;
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
