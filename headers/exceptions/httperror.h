#ifndef HTTPERROR_H
#define HTTPERROR_H

#include <QException>
#include <QNetworkReply>


class HttpError : public QException
{
public:
    HttpError(QNetworkReply *reply);

private:
    QNetworkReply *_reply;

public:
    void raise() const { throw *this; }
    HttpError *clone() const { return new HttpError(*this); }
    QString error();
};

#endif // HTTPERROR_H
