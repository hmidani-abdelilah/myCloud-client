#ifndef BTNLEFTMENU_H
#define BTNLEFTMENU_H

#include <QWidget>

namespace Ui {
class BtnLeftMenu;
}

class BtnLeftMenu : public QWidget
{
    Q_OBJECT

public:
    explicit BtnLeftMenu(QPixmap image, QString text, QWidget *parent = 0);
    ~BtnLeftMenu();
    void setActive(bool value);
    QString getTitle();
    inline QString title() {return _title;}

protected:
    void mousePressEvent(QMouseEvent *);

private:
    Ui::BtnLeftMenu *ui;
    QString _title;
    QPixmap _logo;

signals:
    void hasBeenClicked(QString);
};

#endif // BTNLEFTMENU_H
