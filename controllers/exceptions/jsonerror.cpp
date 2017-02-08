#include "jsonerror.h"

JsonError::JsonError(QString msg)
{
    _msg = msg;
}

QString JsonError::error()
{
    QString msg = "[ERROR JSON] : " + _msg;
    return msg;
}
