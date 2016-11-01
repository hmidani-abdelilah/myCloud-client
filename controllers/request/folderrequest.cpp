#include "folderrequest.h"

FolderRequest::FolderRequest() : ServiceRequest()
{

}

QString FolderRequest::getRoute(int route) {
    switch (route) {
    case Create:
        return "/folder";
        break;
    default:
        break;
    }
}
