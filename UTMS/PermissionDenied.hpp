#ifndef PermissionDenied_HPP
#define PermissionDenied_HPP

#include <iostream>
#include <string>
#include "Error.hpp"


using namespace std;

class PermissionDenied : public Error
{
public:
    PermissionDenied();
};

#endif