#include "Time.hpp"

Time::Time(string timeString)
{
    separateTime(timeString);
}

void Time::separateTime(const string &timeString)
{
    istringstream stream(timeString);
    getline(stream, weekDay, ':');
    char dash;
    stream >> startTime >> dash >> endTime;
}

string Time::show()
{
    return weekDay + ":" + to_string(startTime) + "-" + to_string(endTime);
}

bool Time::haveInterferenceWith(Time *classTime)
{
    if(this->weekDay == classTime->weekDay){
        if((this->startTime < classTime->endTime && this->startTime > classTime->startTime)
        ||(this->endTime < classTime->endTime && this->endTime > classTime->startTime)
        ||(this->endTime == classTime->endTime || this->startTime == classTime->startTime))
            return true;
    }
    return false;
}
