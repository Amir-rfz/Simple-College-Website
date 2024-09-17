#include "Date.hpp"

const char DATE_SEPARATOR = '/';

Date::Date(string dateString)
{
    separateDate(dateString);
}

void Date::separateDate(const string &dateString)
{
    istringstream stream(dateString);
    char delimiter;
    stream >> year >> delimiter >> month >> delimiter >> day;
}

string Date::show()
{
    return to_string(year) + DATE_SEPARATOR + to_string(month) + DATE_SEPARATOR + to_string(day);
}

bool Date::isEqualTo(Date *date)
{
    if(this->year == date->year && this->month == date->month && this->day == date->day){
        return true;
    }
    return false;
}
