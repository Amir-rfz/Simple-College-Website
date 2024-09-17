#include "TAForm.hpp"
#include "beingOfferedCourses.hpp"


TAForm::TAForm(string title, string message, int id, BeingOfferedCourse* course, Professor* professor):Post(title, message ,id)
{
    this->course = course;
    this->professor = professor;
}

string TAForm::showPostSummery()
{
    return to_string(this->getId()) + " " + this->getTitle();
}

string TAForm::showPost()
{
    return this->showPostSummery()+"\n"+ this->course->ShowAllDetail()+ "\n" + "\"" + this->getMessage() + "\" ";
}

int TAForm::numOfRequest()
{
    return this->applicantStudent.size();
}

vector<Student *> TAForm::getStudentRequests()
{
    return this->applicantStudent;
}

BeingOfferedCourse *TAForm::getCourse()
{
    return this->course;
}

void TAForm::addNewTaRequest(Student *targetStudent)
{
    this->applicantStudent.push_back(targetStudent);
}
