#include "headers/mainwindow.h"
#include "mycloudapplication.h"
#include "globalinfo.h"

int main(int argc, char *argv[])
{
    MyCloudApplication a(argc, argv);
    MainWindow w;

    QFont font;
    font.setFamily(Font::GlobalInfo::name);
    QApplication::setFont(font);
    a.setApplicationName(QString("MyOwnBrowserApp"));
    a.setApplicationVersion(QString("1.0"));
    w.show();

    return a.exec();
}
