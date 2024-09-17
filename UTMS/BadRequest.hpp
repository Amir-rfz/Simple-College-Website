#ifndef BadRequest_HPP
#define BadRequest_HPP

#include <iostream>
#include <string>
#include "Error.hpp"


using namespace std;

class BadRequest : public Error
{
public:
    BadRequest();
};

#endif