#include "userInfo.h"

UserInfo* UserInfo::instance = 0;

UserInfo *UserInfo::getInstance()
{
    if (!instance)
        instance = new UserInfo;
    return instance;
}
