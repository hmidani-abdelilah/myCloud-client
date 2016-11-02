#include "routeparams.h"

RouteParams::RouteParams()
{

}

void RouteParams::addValueToBody(const QString &key, const QString &value) {
    if (_body.length() == 0)
        _body.append(key + "=" + value);
    else
        _body.append("&" + key + "=" + value);
}

QByteArray RouteParams::body() {
    return _body;
}

void RouteParams::setParam(const QString &key, const QString &value) {
    _params.insert(key, value);
}

QMap<QString, QString> RouteParams::params() {
    return _params;
}

void RouteParams::addQueryItem(const QString &key, const QString &value) {
    _urlQuery.addQueryItem(key, value);
}
