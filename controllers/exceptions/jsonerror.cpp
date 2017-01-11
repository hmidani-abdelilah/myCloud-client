#include "jsonerror.h"

JsonError::JsonError(QString msg)
{
    _msg = msg;
}

QString JsonError::what()
{
    QString msg = "[ERROR JSON] : " + _msg;
    return msg;
}
