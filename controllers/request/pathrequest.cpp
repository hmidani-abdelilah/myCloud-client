#include "pathrequest.h"

PathRequest::PathRequest() : ServiceRequest()
{

}

QString PathRequest::getRoute(int route) {
    switch (route) {
    case Contents:
        return "/path/contents";
        break;
    default:
        break;
    }
}
