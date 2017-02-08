#ifndef JSONERROR_H
#define JSONERROR_H

#include <QException>

class JsonError : QException
{
public:
    JsonError(QString msg);

private:
    QString _msg;

public:
    void raise() const { throw *this; }
    JsonError *clone() const { return new JsonError(*this); }
    QString error();
};

#endif // JSONERROR_H
