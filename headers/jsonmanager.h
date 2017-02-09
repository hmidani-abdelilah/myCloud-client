#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QMap>
#include <QNetworkReply>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class JsonManager : public QJsonDocument
{
    enum Type {
        ISDOCUMENT,
        ISOBJECT,
        ISARRAY
    };

public:
    JsonManager(QNetworkReply *reply);
    JsonManager(QByteArray reply);
    JsonManager(QString reply);

    QVector<QVariant> getArray(const QString key) const;

    QJsonDocument getJsonDocument();

    JsonManager *toArray(int index);
    JsonManager *toObject(QString value);
    QMap<QString, QVariant> getJson();
    QVector<QVariant> getArray();

    int length();
    void initialize();
private:
    QJsonDocument             _doc;
    QJsonArray                _arraySav;
    QJsonObject               _objectSav;

    QMap<QString, QJsonValue> _arrayValue;
    Type                      _typeSav;
};

#endif // JSONMANAGER_H
