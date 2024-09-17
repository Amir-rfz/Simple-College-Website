#ifndef TAForm_HPP
#define TAForm_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Post.hpp"

using namespace std;

class BeingOfferedCourse;
class Professor;
class Student;

class TAForm : public Post
{
private:
    BeingOfferedCourse* course;
    Professor* professor;
    vector<Student*> applicantStudent;
public:
    TAForm(string title, string message ,int id,BeingOfferedCourse* course, Professor* professor);
    string showPostSummery();
    string showPost();
    int numOfRequest();
    vector<Student*> getStudentRequests();
    BeingOfferedCourse* getCourse();
    void addNewTaRequest(Student* targetStudent);
};

#endif