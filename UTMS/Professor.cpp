#include "Professor.hpp"
#include "TAForm.hpp"

Professor::Professor(int pid, string name, Major* major, string position, string password):User(pid , password , name)
{
    this->major = major;
    this->position = position;
    this->isTeacher = true;
}

string Professor::getName()
{
    return this->name;
}

vector<vector<string>> Professor::showPosts()
{
    vector<vector<string>> result;
    for(auto post : posts){
        vector<string> Post;
        Post.push_back(post->getImageAddr());
        Post.push_back(to_string(post->getId()));
        Post.push_back(post->getTitle());
        Post.push_back(post->getMessage());
        result.push_back(Post);
    }
    return result;
}

vector<string> Professor::showInfo()
{
    vector<string> result;
    result.push_back("name : " + this->name);
    result.push_back("User type : Teacher");
    result.push_back("Position : " + this->position);
    return result;
}

bool Professor::ableToTakeCourse(Course *wantedCourse)
{
    vector<int> CourseMajors = wantedCourse->getCourseMajor();
    for(auto CourseMajor : CourseMajors){
        if(CourseMajor == this->major->getId())
            return true;
    }
    return false;
}

bool Professor::haveInterferenceTime(Time *classTime)
{
    for(auto course : courses){
        if(course->haveInterference(classTime))
            return true;
    }
    return false;
}

void Professor::addNewCourse(BeingOfferedCourse *newBeingOfferedCourse)
{
    this->courses.push_back(newBeingOfferedCourse);
}

bool Professor::haveAccessToCourseChanel(int courseId)
{
    for(auto course : courses){
        if(course->getId() == courseId)
            return true;
    }
    return false;
}

bool Professor::haveAccessToGetCourseChanel(int CourseId)
{
    for(auto course : courses){
        if(course->getId() == CourseId)
            return true;
    }
    return false;
}

TAForm* Professor::addNewTAForm(string message, BeingOfferedCourse *targetCourse)
{
    string title = "TA form for "+ targetCourse->getCourseName() +" course";
    TAForm* newTAForm = new TAForm(title, message, this->postIndex , targetCourse ,this);
    this->posts.push_back(newTAForm);
    this->postIndex += 1;
    if(!this->isManager){
        for(auto connectUser : connectUsers)
            connectUser->addNewTAFormNotif(this);
    }
    this->TaForms.push_back(newTAForm);
    return newTAForm;
}

TAForm *Professor::getTAForm(int id)
{
    for(auto taForm : TaForms){
        if(taForm->getId() == id)
            return taForm;
    }
    throw NotFound();
}
