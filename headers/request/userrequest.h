#ifndef USERREQUEST_H
#define USERREQUEST_H

#include "serviceRequest.h"

class UserRequest : public ServiceRequest
{
public:
    enum User {
        Connection,
        Test
    };


    UserRequest();

protected:
    QString getRoute(int route);
};

#endif // USERREQUEST_H
