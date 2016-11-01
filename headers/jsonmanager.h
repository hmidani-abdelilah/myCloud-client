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
    JsonManager(QString reply);

    QMap<QString, QJsonValue> _arrayValue;

    QString getValue(const QString key) const;
    QString operator [](const QString key) const;

    QVector<QString> getArray(const QString key) const;
    static QVector<QMap<QString, QString> > getArrayByJson(const QString json);

    QJsonDocument getJsonDocument();

    static QMap<QString, QString> getObjectJson(QJsonDocument doc);
    static QMap<QString, QString> getObjectJson(QString value);
    static QVector<QJsonArray> getArrayJson(const QString json);
    static QVector<QJsonArray> getArrayJson(const QJsonDocument doc);
    void convertJsonToArray(QString json);
    JsonManager *toArray(int index);
    JsonManager *toObject(QString value);
    QMap<QString, QString> getJson();
    QVector<QString> getArray();

    int length();
    void initialize();
private:
    QJsonDocument _doc;

    QJsonArray    _arraySav;
    QJsonObject   _objectSav;

    Type          _typeSav;

    // void convertJsonToArray(QString json);
};

#endif // JSONMANAGER_H
