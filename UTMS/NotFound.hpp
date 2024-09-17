#ifndef NotFound_HPP
#define NotFound_HPP

#include <iostream>
#include <string>
#include "Error.hpp"


using namespace std;

class NotFound : public Error
{
public:
    NotFound();
};

#endif