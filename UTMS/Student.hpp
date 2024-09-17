#ifndef Student_HPP
#define Student_HPP

#include <iostream>
#include <string>
#include <vector>
#include "User.hpp"
#include "Course.hpp"
#include "beingOfferedCourses.hpp"
#include "Major.hpp"

using namespace std;

class BeingOfferedCourse;

class Student : public User
{
private:

    int semester;
    vector<BeingOfferedCourse*> courses;
    vector<BeingOfferedCourse*> TACourses;

public:

    Major* major;
    Student(int sid, string name, Major* major, int semester, string password);
    vector<vector<string>> showPosts();
    vector<string> showInfo();
    string showTaRequestInfo();
    int getSemester();
    int getMajor();
    bool haveInterference(BeingOfferedCourse* wantedCourse);
    void getNewCourse(BeingOfferedCourse* wantedCourse);
    void deleteFromCourses(int id);
    vector<string> ShowCourses();
    bool haveAccessToCourseChanel(int courseId);
    bool haveAccessToGetCourseChanel(int CourseId);
    void getAccept(BeingOfferedCourse* targetCourse);
    void getReject(BeingOfferedCourse* targetCourse);
    vector<BeingOfferedCourse*> getCourses();
    
};

#endif