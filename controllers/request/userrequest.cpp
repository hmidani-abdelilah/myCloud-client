#include "userrequest.h"

UserRequest::UserRequest() : ServiceRequest()
{

}

QString UserRequest::getRoute(int route) {
    switch (route) {
    case Connection:
        return "/user/login";
        break;
    case Test:
        return "/user";
        break;
    default:
        break;
    }
}
