#include "jsonmanager.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

JsonManager::JsonManager(QNetworkReply *reply)
{
    this->convertJsonToArray((QString)reply->readAll());
}

JsonManager::JsonManager(QString reply)
{
    this->convertJsonToArray(reply);
}

void JsonManager::convertJsonToArray(QString json){

    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject obj;
    QString name;
    QString pathClient;
    QString status;
    QString size;

        if(!doc.isNull())
        {
            if(doc.isObject())
            {
                obj = doc.object();

                QJsonObject::Iterator it;

                for (it = obj.begin() ; it != obj.end() ; it++) {
                    _arrayValue[it.key()] = *it;
                }
            }
            else
                qDebug() << "Document is not an object" ;
        }
        else
            qDebug() << "Invalid JSON...\n";
}

QString JsonManager::getValue(const QString key) const {
    return _arrayValue[key].toString();
}

QVector<QString> JsonManager::getArray(const QString key) const {
    QVector<QString> array;
    QJsonArray jsonArray = _arrayValue[key].toArray();

    QJsonArray::iterator it;

    for (it = jsonArray.begin() ; it != jsonArray.end() ; it++)
        array.append((*it).toString());

    return array;
}

QString JsonManager::operator[](const QString key) const {
    return _arrayValue[key].toString();
}
