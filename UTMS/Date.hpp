#ifndef Date_HPP
#define Date_HPP

#include <string>
#include <sstream>

using namespace std;

class Date
{
private:
    int year;
    int month;
    int day;
public:
    Date(string dateString);
    void separateDate(const string& dateString);
    string show();
    bool isEqualTo(Date* date);
};

#endif