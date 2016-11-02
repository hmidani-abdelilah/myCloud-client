#ifndef ROUTEPARAMS_H
#define ROUTEPARAMS_H

#include <QByteArray>
#include <QString>
#include <QMap>
#include <QUrlQuery>

class RouteParams
{
public:
    RouteParams();

    void setParam(const QString &key, const QString &value);
    QByteArray body();
    void addValueToBody(QString key, QString value);
    QMap<QString, QString> params();

    void addQueryItem(const QString &key, const QString &value);
    void addValueToBody(const QString &key, const QString &value);
private:
    QByteArray              _body;
    QMap<QString, QString>  _params;
    QUrlQuery               _urlQuery;
};

#endif // ROUTEPARAMS_H
