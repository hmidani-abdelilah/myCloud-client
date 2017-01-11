#ifndef TRANSFERTBAR_H
#define TRANSFERTBAR_H

#include <QObject>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>

#include "infoelement.h"
#include "qlabelcustom.h"

class TransfertBar : public QWidget
{
    Q_OBJECT

public:

public:
    TransfertBar(InfoElement *file);

public:
    QHBoxLayout     *_layout;
    QLabelCustom    *_iconStatus;
    QLabelCustom    *_size;
    QLabelCustom    *_name;
    QLabelCustom    *_speedLabel;
    QLabelCustom    *_btnDelete;
    QLabelCustom    *_labelTime;
    QProgressBar    *_progressBar;
    QLabelCustom    *_transferedSize;
    QLabelCustom    *_statusLabel;
    InfoElement     *_file;

    quint64         _sizeTransfered;
    float           _speed;
    QTime           *_time;

public:
    void setPourcentage();
    void setSpeed();
    void setSize(quint64 size);
    void setName(QString name);
    void setTransferedSize();
    void updateElement();
    void setTime();

    void setStatus();
    void hasBeenSelected(bool value);

    quint64 getId();
    InfoElement::Status getStatus();

    void changeStatusOfFile(InfoElement::Status status);
    QLabelCustom *getBtnDelete();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:

signals:
    void clicked(quint64);
    void clickOnDelete(TransfertBar*);

private slots:
    void slotClickOnDelete();
};
#endif // TRANSFERTBAR_H
