#include "headers/mimedatafile.h"

MineDataFile::MineDataFile()
{

}

QVariant MineDataFile::retrieveData(const QString & mimeType, QVariant::Type type) {
    qDebug(mimeType.toStdString().c_str());
    qDebug("retrieveData");
    return "toto";
}


bool MineDataFile::hasFormat(const QString & mimeType) const {
    qDebug(mimeType.toStdString().c_str());
    qDebug("hasFormat");
    return true;
}
