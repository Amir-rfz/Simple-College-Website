#include "Error.hpp"

Error::Error(string _type){
    this->type = _type;
}

string Error::show(){
    return this->type;
}