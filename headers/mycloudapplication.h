#ifndef MYCLOUDAPPLICATION_H
#define MYCLOUDAPPLICATION_H

#include <QApplication>

class MyCloudApplication : public QApplication
{
public:
    MyCloudApplication(int argc, char *argv[]);

protected:
    bool notify(QObject *receiver, QEvent *event);
public:
    void commitData(QSessionManager &manager);
private slots:
    void slotApplicationStateChanged(Qt::ApplicationState state);
};

#endif // MYCLOUDAPPLICATION_H
