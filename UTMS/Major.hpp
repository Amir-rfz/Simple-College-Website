#ifndef Major_HPP
#define Major_HPP

#include <iostream>
#include <string>

using namespace std;

class Major
{
private:

    int id;
    string name;

public:

    Major(int id,string name);
    int getId();
    string getMajor();
    
};

#endif