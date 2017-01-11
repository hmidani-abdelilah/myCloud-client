#ifndef MINEDATAFILE_H
#define MINEDATAFILE_H

#include <QMimeData>

class MineDataFile : public QMimeData
{
public:
    MineDataFile();
protected:
    QVariant retrieveData(const QString &mimeType, QVariant::Type type);
    bool hasFormat(const QString &mimeType) const;
   // QStringList formats() const;
};

#endif // MINEDATAFILE_H
