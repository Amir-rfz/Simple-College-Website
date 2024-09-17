#include "PermissionDenied.hpp"

const string PERMISSION_ERROR = "Permission Denied";

PermissionDenied::PermissionDenied():Error(PERMISSION_ERROR){}
