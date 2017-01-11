#include "mycloudapplication.h"
#include <QSessionManager>
#include <QMessageBox>

#include "httperror.h"

MyCloudApplication::MyCloudApplication(int argc, char *argv[]) : QApplication(argc, argv)
{
}

bool MyCloudApplication::notify(QObject *receiver, QEvent *event)
{
    try {
        return QApplication::notify(receiver, event);
    }
    catch(HttpError &httpError) {
        qDebug() << httpError.what();
    }
}
