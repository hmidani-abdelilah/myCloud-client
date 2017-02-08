#ifndef TRANSFERTPAGE_H
#define TRANSFERTPAGE_H

#include <QObject>
#include <QHBoxLayout>
#include <QTimer>
#include <QVector>

#include "filemanager.h"
#include "transfertbar.h"
#include "page.h"

class TransfertPage : public Page
{
    Q_OBJECT

public:
    TransfertPage();

protected:
    void setHeaderBar();

private slots:
    void addNewTransfertBar(qint64 id);
    void updateData();
    void barHasBeenClicked(qint64 id);
    void slotDeleteTransfertBar(qint64 id);
    void slotDeleteAllFile(TransfertBar *bar);
    void slotDeleteTransfert();
    void slotPauseTransfert();
    void slotStartTransfert();

private:
    FileManager             *_fileManager;
    QTimer                  *_timer;
    QVector<TransfertBar*>  *_listBar;
    QVBoxLayout             *_layout;
    QPushButton             *_deleteBtn;
    QPushButton             *_pauseBtn;
    QPushButton             *_startBtn;
    TransfertBar            *_barSelected;
    void updateHeaderBar();
};

#endif // TRANSFERTPAGE_H
