#ifndef TRANSFERTBAR_H
#define TRANSFERTBAR_H

#include <QObject>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>

#include "customqfile.h"
#include "qlabelcustom.h"

class TransfertBar : public QHBoxLayout
{
    Q_OBJECT

public:
    enum Status {
        EN_COURS,
        PAUSE,
        STOP
    };

public:
    TransfertBar(CustomQFile *file);

public:
    QLabelCustom    *_iconStatus;
    QLabelCustom    *_size;
    QLabelCustom    *_name;
    QLabelCustom    *_speedLabel;
    QLabelCustom    *_btnDelete;
    QLabelCustom    *_labelTime;
    QProgressBar    *_progressBar;
    QLabelCustom    *_transferedSize;
    QLabelCustom    *_statusLabel;
    CustomQFile     *_file;

    quint64         _sizeTransfered;
    float           _speed;
    Status          _status;
    QTime           *_time;

public:
    void setPourcentage(int value);
    void setSpeed(float speed);
    void setSize(quint64 size);
    void setName(QString name);
    void setTransferedSize(quint64 size);
    void updateElement();
    void setTime();

    void setStatus(Status status);
private:

};
#endif // TRANSFERTBAR_H
