#ifndef PATHREQUEST_H
#define PATHREQUEST_H

#include "serviceRequest.h"

class PathRequest : public ServiceRequest
{
public:
    enum Path {
        Contents
    };


    PathRequest();

protected:
    QString getRoute(int route);
};

#endif // PATHREQUEST_H
