#ifndef FOLDERREQUEST_H
#define FOLDERREQUEST_H

#include "serviceRequest.h"

class FolderRequest : public ServiceRequest
{
public:
    enum Folder {
        Create
    };

    FolderRequest();

protected:
    QString getRoute(int route);
};

#endif // FOLDERREQUEST_H
