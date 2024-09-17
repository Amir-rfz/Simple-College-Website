#include "Major.hpp"

Major::Major(int id, string name)
{
    this->id = id;
    this->name = name;
}

int Major::getId()
{
    return this->id;
}

string Major::getMajor()
{
    return this->name;
}
