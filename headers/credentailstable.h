#ifndef CREDENTAILSTABLE_H
#define CREDENTAILSTABLE_H

#include <QByteArray>
#include <QString>

class CredentailsTable : public QByteArray
{
public:
    CredentailsTable();
    void addCredential(QString name, QString value);
};

#endif // CREDENTAILSTABLE_H
