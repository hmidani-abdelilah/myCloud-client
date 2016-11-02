#ifndef FILEREQUEST_H
#define FILEREQUEST_H

#include "serviceRequest.h"

class FileRequest : public ServiceRequest
{
public:
    enum File {
        DeleteFile,
        Write,
        Create,
        Historic,
        Reduce
    };

    FileRequest();

protected:
    QString getRoute(int route);
};

#endif // FILEREQUEST_H
