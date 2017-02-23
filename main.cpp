#include "headers/mainwindow.h"
#include "mycloudapplication.h"
#include "globalinfo.h"
#include "image.h"

int main(int argc, char *argv[])
{
    MyCloudApplication a(argc, argv);
    MainWindow w;

    QFont font;
    font.setFamily(Font::GlobalInfo::name);
    QApplication::setFont(font);
    a.setApplicationName(QString("MyCloud"));

    QPixmap logo = Image::fromSvgToPixmap(QSize(111, 111), ":/logo/cloudMacLogo");

    a.setWindowIcon(logo);
    a.setApplicationVersion(QString("1.0"));
    w.show();

    return a.exec();
}
