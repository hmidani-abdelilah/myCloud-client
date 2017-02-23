#include "mycloudapplication.h"
#include "globalinfo.h"

#include <QSessionManager>
#include <QMessageBox>
#include <QtMac>

#include "httperror.h"

MyCloudApplication::MyCloudApplication(int argc, char *argv[]) : QApplication(argc, argv)
{
    connect(this, &MyCloudApplication::applicationStateChanged, this, &MyCloudApplication::slotApplicationStateChanged);
}

bool MyCloudApplication::notify(QObject *receiver, QEvent *event)
{
    try {
        return QApplication::notify(receiver, event);
    }
    catch(HttpError &httpError) {
        qDebug() << httpError.error();
        return false;
    }
}

void MyCloudApplication::slotApplicationStateChanged(Qt::ApplicationState state) {
    if (state == Qt::ApplicationActive) {
        Application::GlobalInfo::notificationNumber = 0;
        QtMac::setBadgeLabelText("");
    }
    Application::GlobalInfo::appState = state;
}
