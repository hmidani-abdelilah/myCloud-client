#include "credentailstable.h"

CredentailsTable::CredentailsTable() : QByteArray()
{

}

void CredentailsTable::addCredential(QString name, QString value) {
    if (this->length() == 0)
        this->append(name + "=" + value);
    else
        this->append("&" + name + "=" + value);
}
