#include "jsonmanager.h"
#include "jsonerror.h"

JsonManager::JsonManager(QNetworkReply *reply) : QJsonDocument()
{
    _typeSav = ISDOCUMENT;
    QByteArray text = reply->readAll();
    _doc = QJsonDocument::fromJson(text);
}

JsonManager::JsonManager(QByteArray reply) : QJsonDocument()
{
    _typeSav = ISDOCUMENT;
    _doc = QJsonDocument::fromJson(reply);
}

JsonManager::JsonManager(QString reply)
{
    _doc = QJsonDocument::fromJson(reply.toUtf8());
}

QJsonDocument JsonManager::getJsonDocument() {
    return _doc;
}

void JsonManager::initialize() {
    _typeSav = ISDOCUMENT;
}

QVector<QString> JsonManager::getArray(const QString key) const {
    QVector<QString> array;
    QJsonArray jsonArray = _arrayValue[key].toArray();

    QJsonArray::iterator it;

    for (it = jsonArray.begin() ; it != jsonArray.end() ; it++)
        array.append((*it).toString());

    return array;
}

JsonManager *JsonManager::toArray(int index) { //vient d'un array
    try {
        QJsonArray array;

        switch (_typeSav) {
        case ISDOCUMENT:
            array = _doc.array();
            break;

        case ISARRAY:
            array = _arraySav;
            break;
        default:
            throw JsonError("[toArray] : This format is not an array - index : " + QString::number(index));
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
            else
                throw JsonError("[toArray] : This array is not an array or an object - index : " + QString::number(index));
            return this;
        }
        throw JsonError("[toArray] : This format is not an array - index : " + QString::number(index));
    }
    catch(JsonError *jsonError) {
        qDebug() << jsonError->error();
    }

    return this;
}

int JsonManager::length() {
    try {
        switch (_typeSav) {
        case ISDOCUMENT:
            if (_doc.isArray())
                return _doc.array().size();
            else if (_doc.isObject())
                return _doc.object().size();
            else
                throw JsonError("[length] : Can not get length of this document");
            break;
        case ISARRAY:
            return _arraySav.size();
            break;
        case ISOBJECT:
            return _objectSav.size();
            break;
        default:
            throw JsonError("[length] : Can not get length of this json");
            break;
        }
    }
    catch(JsonError *jsonError) {
        qDebug() << jsonError->error();
    }
    return 0;
}

JsonManager *JsonManager::toObject(QString value) {
    try {
        QJsonObject object;
        switch (_typeSav) {
        case ISDOCUMENT:
            object = _doc.object();
            break;
        case ISOBJECT:
            object = _objectSav;
            break;
        default:
            throw JsonError("[toObject] : This format is not an object - value : " + value);
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
            throw JsonError("[toObject] : QJsonObject is not an object or an array - value : " + value);
            return this;
        }
        return this;
    }
    catch(JsonError *jsonError) {
        qDebug() << jsonError->error();
    }
    return this;
}

QMap<QString, QString> JsonManager::getJson() {
    try {
        QJsonObject object;
        switch (_typeSav) {
        case ISDOCUMENT:
            object = _doc.object();
            break;
        case ISOBJECT:
            object = _objectSav;
            break;
        default:
            throw JsonError("[getJson] : This format is not a json - type : " + QString::number(_typeSav));
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
    catch(JsonError *jsonError) {
        qDebug() << jsonError->error();
    }
    return QMap<QString, QString>();
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
