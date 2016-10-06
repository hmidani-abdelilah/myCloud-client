#include "filerequest.h"

FileRequest::FileRequest() : ServiceRequest()
{

}

QString FileRequest::getRoute(int route) {
    switch (route) {
    case Write:
        return "/file/write";
        break;
    case Create:
        return "/file/create";
        break;
    default:
        break;
    }
}
