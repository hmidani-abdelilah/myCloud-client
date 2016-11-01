#include "jsonmanager.h"

JsonManager::JsonManager(QNetworkReply *reply) : QJsonDocument()
{
    _typeSav = ISDOCUMENT;
    QString text = ((QString)reply->readAll());
    _doc = QJsonDocument::fromJson(text.toUtf8());
}

JsonManager::JsonManager(QString reply)
{
    _doc = QJsonDocument::fromJson(reply.toUtf8());
    //this->convertJsonToArray(reply);
}

QJsonDocument JsonManager::getJsonDocument() {
    return _doc;
}

void JsonManager::initialize() {
    _typeSav = ISDOCUMENT;
}

QMap<QString, QString> JsonManager::getObjectJson(QJsonDocument doc) {
    //    if(!doc.isObject())
    //        return ;

    QJsonObject obj;
    QMap<QString, QString> array;
    obj = doc.object();

    QJsonObject::Iterator it;

    for (it = obj.begin() ; it != obj.end() ; it++) {
        array[it.key()] = (*it).toString();
    }
    return array;
}

QMap<QString, QString> JsonManager::getObjectJson(QString value) {
    JsonManager::getObjectJson(JsonManager::fromJson(value.toUtf8()));
}

void JsonManager::convertJsonToArray(QString json){

    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject obj;
    qDebug() << "convert json to array" << json.toStdString().c_str();
    if(!doc.isNull())
    {
        if(doc.isObject())
        {
            obj = doc.object();

            QJsonObject::Iterator it;

            for (it = obj.begin() ; it != obj.end() ; it++) {
                qDebug(it.key().toStdString().c_str());
                _arrayValue[it.key()] = *it;
            }
        }
        else if (doc.isArray()) {
            qDebug() << "Document is an array" << doc.array().count() ;
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

QVector<QJsonArray> JsonManager::getArrayJson(const QString json)  {
    JsonManager::getArrayJson(JsonManager::fromJson(json.toUtf8()));
}

QVector<QJsonArray> JsonManager::getArrayJson(const QJsonDocument doc) {
    QVector<QJsonArray> array;

    if (doc.isArray())
        qDebug("OUUUIIIIIIIIIIIIIIIIII");
    else
        qDebug("NOOOOOOOOOOOOOOON");
    QJsonArray jsonArray = doc.array();
    QJsonArray::iterator it;
    //    for (it = jsonArray.begin() ; it != jsonArray.end() ; it++) {
    //        array.append((*it));
    //    }
    return array;
}

QVector<QString> JsonManager::getArray(const QString key) const {
    QVector<QString> array;
    QJsonArray jsonArray = _arrayValue[key].toArray();

    QJsonArray::iterator it;

    for (it = jsonArray.begin() ; it != jsonArray.end() ; it++)
        array.append((*it).toString());

    return array;
}

//QVector<QMap<QString, QString>> JsonManager::getArrayByJson(const QString json)
//{
//    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
//    QVector<QMap<QString, QString>> vector;
//    QJsonArray array = doc.array();
//    QJsonObject obj;

//    QJsonArray::iterator it;
//    for (it = array.begin() ; it != array.end() ; it++) {
//        obj = (*it).toObject();

//        QJsonObject::Iterator itObj;
//        QMap<QString, QString> map;
//        for (itObj = obj.begin() ; itObj != obj.end() ; itObj++) {
//            map.insert(itObj.key(), (*itObj).toString());
//            vector.append(map);
//        }
//    }
//    //     vector.append((*it).toObject());

//    return vector;
//}

QString JsonManager::operator[](const QString key) const {
    return _arrayValue[key].toString();
}

//[{}, {}]

//[{toto : {} }, {titi : {}}]

//[{titi : []}, {toto : []}]

//{titi : []}

JsonManager *JsonManager::toArray(int index) { //vient d'un array
    QJsonArray array;

    switch (_typeSav) {
    case ISDOCUMENT:
        array = _doc.array();
        break;

    case ISARRAY:
        array = _arraySav;
        break;
    default:
        break;
    }

    QJsonArray::iterator it;
    int i = 0;


    for (it = array.begin() ; it != array.end() ; it++) {
        if (index != i) {
            i++;
            continue;
        }
        else if ((*it).isArray()) {
            _arraySav = (*it).toArray();
            _typeSav = ISARRAY;
            return this;
        }
        else if ((*it).isObject()) {
            _objectSav = (*it).toObject();
            _typeSav = ISOBJECT;
            return this;
        }
        qDebug("ERROR JSON ARRAY");
        return this;
    }
    qDebug("ERROR JSON ARRAY");
    return this;
}

int JsonManager::length() {
    switch (_typeSav) {
    case ISDOCUMENT:
        if (_doc.isArray())
            return _doc.array().size();
        else if (_doc.isObject())
            return _doc.object().size();
        break;
    case ISARRAY:
        return _arraySav.size();
        break;
    case ISOBJECT:
        return _objectSav.size();
        break;
    default:
        break;
    }
}

JsonManager *JsonManager::toObject(QString value) {
    QJsonObject object;
    switch (_typeSav) {
    case ISDOCUMENT:
        object = _doc.object();
        break;
    case ISOBJECT:
        object = _objectSav;
        break;
    default:
        break;
    }

    QJsonObject::iterator it;
    int i = 0;

    for (it = object.begin() ; it != object.end() ; it++) {
        if (it.key() != value) {
            i++;
            continue;
        }
        else if ((*it).isArray()) {
            _arraySav = (*it).toArray();
            _typeSav = ISARRAY;
            return this;
        }
        else if ((*it).isObject()) {
            _objectSav = (*it).toObject();
            _typeSav = ISOBJECT;
            return this;
        }
        qDebug("ERROR JSON TO OBJECT");
        return this;
    }
    return this;
}

QMap<QString, QString> JsonManager::getJson() {
    QJsonObject object;
    switch (_typeSav) {
    case ISDOCUMENT:
        object = _doc.object();
        break;
    case ISOBJECT:
        object = _objectSav;
        break;
    default:
        break;
    }

    QJsonObject::Iterator itObj;
    QMap<QString, QString> map;

    for (itObj = object.begin() ; itObj != object.end() ; itObj++) {
        if ((*itObj).isDouble()) {
            map[itObj.key()] = QString::number((*itObj).toDouble(), 'g', 1000);
        }
        if ((*itObj).isString()) {
            map[itObj.key()] = (*itObj).toString();
        }
    }

    return map;
}



QVector<QString> JsonManager::getArray() {
    QJsonArray jsonArray;
    switch (_typeSav) {
    case ISDOCUMENT:
        jsonArray = _doc.array();
        break;

    case ISARRAY:
        jsonArray = _arraySav;
        break;
    default:
        break;
    }

    QVector<QString> array;
    QJsonArray::iterator it;

    for (it = jsonArray.begin() ; it != jsonArray.end() ; it++)
        if ((*it).isDouble()) {
            array.append(QString::number((*it).toDouble(), 'g', 1000));
        }
        else
            array.append((*it).toString());
    return array;
}
