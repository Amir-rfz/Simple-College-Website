#ifndef Error_HPP
#define Error_HPP

#include <iostream>
#include <string>


using namespace std;

class Error
{
private:
    string type;
public:
    Error(string type);
    string show();
};

#endif