#ifndef Course_HPP
#define Course_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Course
{
private:
    int cid;
    string name;
    int credit;
    int prerequisite;
    vector<int> majors_id;
public:
    Course(int cid, string name, int credit, int prerequisite, vector<int> majors_id);
    int getId();
    string getName();
    vector<int> getCourseMajor();
    int getPrerequisite();
};

#endif