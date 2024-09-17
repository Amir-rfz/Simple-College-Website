#ifndef BeingOfferedCourse_HPP
#define BeingOfferedCourse_HPP

#include <iostream>
#include <string>
#include <vector>
#include "UTMS.hpp"

using namespace std;

class Professor;
class Chanel;
class Time;
class Date;

class BeingOfferedCourse
{
private:
    int id;
    Course* wantedCourse;
    Professor* wantedProfessor;
    Chanel* chanel;
    int capacity;
    Time* time;
    Date* exam_date;
    int class_number;
    int prerequisite;
    vector<int> majors_id;
    int postId;
public:
    BeingOfferedCourse(Course* course, Professor* professor, int capacity, Time* time, Date* exam_date, int class_number ,int id);
    string showLessDetail();
    string ShowAllDetail();
    int getId();
    string getCourseName();
    bool haveInterference(Time* classTime);
    int getPrerequisite();
    bool haveMajor(int major);
    bool haveInterferenceWithCourse(BeingOfferedCourse* wantedCourse);
    void addNewPost(string title,string message,string image,User* user);
    vector<string> showChanel();
    vector<string> showPost(int postId);
    void addNewTA(User* user);
    void addNewMember(User* targetStudent);
    void removeMember(User* targetStudent);
    string getcapacity();
    string getProfessor();
    string getClassTime();
    string getExamDate();
    string getClassNum();
};

#endif