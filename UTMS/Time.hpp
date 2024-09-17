#ifndef Time_HPP
#define Time_HPP

#include <string>
#include <sstream>

using namespace std;

class Time
{
private:
    string weekDay;
    int startTime;
    int endTime;
public:
    Time(string timeString);
    void separateTime(const string& timeString);
    string show();
    bool haveInterferenceWith(Time* classTime);
};

#endif