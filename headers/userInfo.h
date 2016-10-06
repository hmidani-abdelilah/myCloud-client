#ifndef USERINFO_H
#define USERINFO_H

#include <QString>

class UserInfo
{
public:
    static UserInfo *getInstance();

private:
    UserInfo() {}
    static UserInfo *instance;
    QString _name;
};

#endif // USERINFO_H
