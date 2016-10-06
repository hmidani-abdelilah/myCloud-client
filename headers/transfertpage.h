#ifndef TRANSFERTPAGE_H
#define TRANSFERTPAGE_H

#include <QObject>
#include <QHBoxLayout>
#include <Qwidget>
#include <QTimer>
#include <QVector>

#include "filemanager.h"
#include "transfertbar.h"

class TransfertPage : public QVBoxLayout
{
    Q_OBJECT

public:
    TransfertPage();

private slots:
    void addNewUpload(QString id);
    void updateData();

private:
    FileManager             *_fileManager;
    QTimer                  *_timer;
    QVector<TransfertBar*>  *_listBar;
};

#endif // TRANSFERTPAGE_H
