#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QMap>
#include <QNetworkReply>
#include <QJsonValue>

class JsonManager
{
public:
    JsonManager(QNetworkReply *reply);
    JsonManager(QString reply);

    QMap<QString, QJsonValue> _arrayValue;

    QString getValue(const QString key) const;
    QString operator [](const QString key) const;

    QVector<QString> getArray(const QString key) const;
private:
    void convertJsonToArray(QString json);
};

#endif // JSONMANAGER_H
