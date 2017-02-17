#ifndef QLABELCUSTOM_H
#define QLABELCUSTOM_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

class QLabelCustom : public QLabel
{
    Q_OBJECT

public:
     explicit QLabelCustom( const QString &text = "", QWidget* parent = 0 );
     QLabelCustom(QWidget *parent);
     QLabelCustom(const QString& pathImg, int w, int h, QWidget* parent = 0);
     QLabelCustom(const QPixmap img, int w, int h, QWidget *parent = 0);

protected:
    virtual void mousePressEvent(QMouseEvent*ev);

signals:
     void clicked();
     void clickedPos(QPoint);

public:
     void createBtnImg(QString imgPath, int w, int h);
     void changeImageColor(QString color);

     void createBtnImg(QPixmap img, int w, int h);
private:
     QPixmap    _image;
};

#endif // QLABELCUSTOM_H
