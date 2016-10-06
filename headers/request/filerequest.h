#ifndef FILEREQUEST_H
#define FILEREQUEST_H

#include "serviceRequest.h"

class FileRequest : public ServiceRequest
{
public:
    enum File {
        Write,
        Create,
        WriteFiles
    };

    FileRequest();

protected:
    QString getRoute(int route);
};

#endif // FILEREQUEST_H
