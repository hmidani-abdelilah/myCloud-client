#ifndef MYCLOUDAPPLICATION_H
#define MYCLOUDAPPLICATION_H

#include <QApplication>

class MyCloudApplication : public QApplication
{
public:
    MyCloudApplication(int argc, char *argv[]);

public:
    void commitData(QSessionManager &manager);
};

#endif // MYCLOUDAPPLICATION_H
