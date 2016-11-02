#include "filerequest.h"

FileRequest::FileRequest() : ServiceRequest()
{

}

QString FileRequest::getRoute(int route) {
    switch (route) {
    case DeleteFile:
        return "/file/deleteFile";
        break;
    case Write:
        return "/file/write";
        break;
    case Create:
        return "/file";
        break;
    case Historic:
        return "/file/historic";
        break;
    case Reduce:
        return "/file/reduce/71.PNG";
        break;
    default:
        break;
    }
}
