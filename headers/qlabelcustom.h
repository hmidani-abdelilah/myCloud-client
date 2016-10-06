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
     QLabelCustom(const QString& pathImg, int w, int h, QWidget* parent = 0);

protected:
    virtual void mousePressEvent(QMouseEvent* event);

signals:
     void clicked();

private:
     void createBtnImg(QString imgPath, int w, int h);
};

#endif // QLABELCUSTOM_H
