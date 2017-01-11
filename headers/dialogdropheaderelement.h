#ifndef DIALOGDROPHEADERELEMENT_H
#define DIALOGDROPHEADERELEMENT_H

#include <QWidget>

namespace Ui {
class DialogDropHeaderElement;
}

class DialogDropHeaderElement : public QWidget
{
    Q_OBJECT

public:
    explicit DialogDropHeaderElement(QWidget *parent = 0);
    ~DialogDropHeaderElement();

    void setInformation(QPixmap pixmap, QString title, QString path, QString createAt, quint64 size);
private:
    Ui::DialogDropHeaderElement *ui;
    void paintEvent(QPaintEvent *pe);
    void setIcon(QPixmap picture);
};

#endif // DIALOGDROPHEADERELEMENT_H
