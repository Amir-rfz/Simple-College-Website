#ifndef Professor_HPP
#define Professor_HPP

#include <iostream>
#include <string>
#include <vector>
#include "User.hpp"
#include "Course.hpp"
#include "beingOfferedCourses.hpp"
#include "Time.hpp"
#include "Major.hpp"

using namespace std;

class BeingOfferedCourse;
class TAForm;

class Professor : public User
{
private:

    string position;
    vector<BeingOfferedCourse*> courses;
    vector<TAForm*> TaForms;

public:

    Major* major;
    Professor(int pid, string name, Major* major, string position, string password);
    string getName();
    vector<vector<string>> showPosts();
    vector<string> showInfo();
    bool ableToTakeCourse(Course* wantedCourse);
    bool haveInterferenceTime(Time* classTime);
    void addNewCourse(BeingOfferedCourse* newBeingOfferedCourse);
    bool haveAccessToCourseChanel(int courseId);
    bool haveAccessToGetCourseChanel(int CourseId);
    TAForm* addNewTAForm(string message ,BeingOfferedCourse* targetCourse);
    TAForm* getTAForm(int id);
};

#endif