#include "beingOfferedCourses.hpp"
#include "Chanel.hpp"

const string SEPARATOR = " ";

BeingOfferedCourse::BeingOfferedCourse(Course* course, Professor* professor, int capacity, Time* time, Date* exam_date, int class_number , int id)
{
    this->wantedCourse = course;
    this->wantedProfessor = professor;
    this->capacity = capacity;
    this->time = time;
    this->exam_date = exam_date;
    this->class_number = class_number;
    this->id = id;
    this->prerequisite = course->getPrerequisite();
    this->majors_id = course->getCourseMajor();
    this->postId = 1;
    this->chanel = new Chanel(this);
}

string BeingOfferedCourse::showLessDetail()
{
    return (to_string(this->id) + SEPARATOR + this->wantedCourse->getName() + SEPARATOR + to_string(capacity) + SEPARATOR + this->wantedProfessor->getName());
}

string BeingOfferedCourse::ShowAllDetail()
{
    return (to_string(this->id) + SEPARATOR + this->wantedCourse->getName() + SEPARATOR + to_string(capacity) + SEPARATOR + this->wantedProfessor->getName()
            + SEPARATOR + time->show() + SEPARATOR + exam_date->show() + SEPARATOR + to_string(class_number));
}

int BeingOfferedCourse::getId() 
{
    return this->id;
}

string BeingOfferedCourse::getCourseName()
{
    return this->wantedCourse->getName();
}

bool BeingOfferedCourse::haveInterference(Time* classTime)
{
    return this->time->haveInterferenceWith(classTime);
}

int BeingOfferedCourse::getPrerequisite()
{
    return this->prerequisite;
}

bool BeingOfferedCourse::haveMajor(int major)
{
    for(auto majorId : majors_id){
        if(majorId == major)
            return true;
    }
    return false;
}

bool BeingOfferedCourse::haveInterferenceWithCourse(BeingOfferedCourse *wantedCourse)
{
    if(this->time->haveInterferenceWith(wantedCourse->time)) return true;
    if(this->exam_date->isEqualTo(wantedCourse->exam_date)) return true;
    return false;
}

void BeingOfferedCourse::addNewPost(string title, string message, string image ,User* user)
{
    this->chanel->addNewPost(new Post(title, message, postId, image ,user->getName()) , user);
    this->postId += 1;
}

vector<string> BeingOfferedCourse::showChanel()
{
    vector<string> result;
    result.push_back(this->ShowAllDetail());
    result = this->chanel->showPosts(&result);

    return result;
}

vector<string> BeingOfferedCourse::showPost(int postId)
{
    vector<string> result;
    result.push_back(this->ShowAllDetail());
    result = this->chanel->showPost(postId, &result);
    return result;
}

void BeingOfferedCourse::addNewTA(User *user)
{
    this->chanel->addNewMember(user);
}

void BeingOfferedCourse::addNewMember(User *targetStudent)
{
    this->chanel->addNewMember(targetStudent);
}

void BeingOfferedCourse::removeMember(User *targetStudent)
{
    this->chanel->removeMember(targetStudent);
}

string BeingOfferedCourse::getcapacity()
{
    return to_string(capacity);
}

string BeingOfferedCourse::getProfessor()
{
    return wantedProfessor->getName();
}

string BeingOfferedCourse::getClassTime()
{
    return time->show();
}

string BeingOfferedCourse::getExamDate()
{
    return exam_date->show();
}

string BeingOfferedCourse::getClassNum()
{
    return to_string(class_number);
}
