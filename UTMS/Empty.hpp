#ifndef Empty_HPP
#define Empty_HPP

#include <iostream>
#include <string>
#include "Error.hpp"


using namespace std;

class Empty : public Error
{
public:
    Empty();
};

#endif