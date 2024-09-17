#include "Student.hpp"

Student::Student(int sid, string name, Major* major, int semester, string password):User(sid , password , name)
{
    this->major = major;
    this->semester = semester;
    this->isStudent = true;
}

vector<vector<string>> Student::showPosts()
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

vector<string> Student::showInfo()
{
    vector<string> result;
    result.push_back("name : " + this->name);
    result.push_back("User type : Student");
    result.push_back("Semester : " + to_string(semester));
    return result;
}

string Student::showTaRequestInfo()
{
    return to_string(this->getId()) + " " + this->getName() + " " + to_string(semester);
}

int Student::getSemester()
{
    return this->semester;
}

int Student::getMajor()
{
    return this->major->getId();
}

bool Student::haveInterference(BeingOfferedCourse *wantedCourse)
{
    for(auto course : courses){
        if(course->haveInterferenceWithCourse(wantedCourse))
            return true;
    }
    return false;
}

void Student::getNewCourse(BeingOfferedCourse *wantedCourse)
{
    this->courses.push_back(wantedCourse);
    for(auto connectUser : connectUsers)
        connectUser->addGetCourseNotif(this);
}

void Student::deleteFromCourses(int id)
{
    for(int i=0 ; i < this->courses.size() ; i++){
        if(courses[i]->getId() == id){
            courses[i]->removeMember(this);
			courses.erase(courses.begin() + i);
            for(auto connectUser : connectUsers)
                connectUser->addDeleteCourseNotif(this);
            return;           
        }
    }
    throw NotFound();
}

vector<string> Student::ShowCourses()
{
    vector<string> result;
    // if(courses.size() == 0) throw Empty();
    for(auto course : courses){
        result.push_back(course->ShowAllDetail());
    }
    return result;
}

bool Student::haveAccessToCourseChanel(int courseId)
{
    for(auto course : TACourses){
        if(course->getId() == courseId)
            return true;
    }
    return false;
}

bool Student::haveAccessToGetCourseChanel(int CourseId)
{
    for(auto course : TACourses){
        if(course->getId() == CourseId)
            return true;
    }

    for(auto course : courses){
        if(course->getId() == CourseId)
            return true;
    }
    return false;
}

void Student::getAccept(BeingOfferedCourse *targetCourse)
{
    TACourses.push_back(targetCourse);
    this->getAcceptNotif(targetCourse);
}

void Student::getReject(BeingOfferedCourse *targetCourse)
{
    this->getRejectedNotif(targetCourse);
}

vector<BeingOfferedCourse *> Student::getCourses()
{
    return courses;
}
