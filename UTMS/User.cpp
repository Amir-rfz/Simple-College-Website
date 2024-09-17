#include "User.hpp"
#include "beingOfferedCourses.hpp"

const string NEW_POST_NOTIFICATION = "New Post";
const string NEW_COURSE_OFFER_NOTIFICATION = "New Course Offering";
const string GET_COURSE_NOTIFICATION = "Get Course";
const string DELETE_COURSE_NOTIFICATION = "Delete Course";
const string NEW_COURSE_POST_NOTIFICATION = "New Course Post";
const string NEW_FORM_NOTIFICATION = "New Form";
const string GET_ACCEPT_NOTIFICATION = "Your request to be a teaching assistant has been accepted.";
const string GET_REJECT_NOTIFICATION = "Your request to be a teaching assistant has been rejected.";

User::User(int id, string password, string name)
{
    this->id = id;
    this->password = password;
    this->postIndex = 1;
    this->name = name;
    this->isTeacher = false;
    this->isStudent = false;
    this->isManager = false;
}

int User::getId()
{
    return this->id;
}

string User::getName()
{
    return this->name;
}

string User::getPass()
{
    return this->password;
}

void User::addNewPost(string title, string message,string imageAddr)
{
    this->posts.push_back(new Post(title, message, this->postIndex ,imageAddr));
    this->postIndex += 1;
    if(!this->isManager){
        for(auto connectUser : connectUsers)
            connectUser->addNewPostNotif(this);
    }
}

void User::deletePost(int id)
{
    for(int i=0 ; i < this->posts.size() ; i++){
        if(posts[i]->getId() == id){
			delete posts[i];
			posts.erase(posts.begin() + i);
            return;           
        }
    }
    throw NotFound();
}

string User::showPost(int postId)
{
    for(auto post : posts){
        if(post->getId() == postId)
            return post->showPost();
    }
    throw NotFound();
}

bool User::isConnectBefor(int id)
{
    for(auto user : connectUsers){
        if(user->getId() == id)
            return true;
    }
    return false;
}

void User::getConnect(User *wantedUser)
{
    this->connectUsers.push_back(wantedUser);
}

vector<string> User::ShowNotifications()
{
    if(this->notifications.size() == 0) throw Empty();
    vector<string> result;
    for(int i = notifications.size()-1 ; i>=0 ; i--){
        result.push_back(this->notifications[i]);
    }
    this->notifications.clear();
    return result;
}

void User::addNewPostNotif(User *user)
{
    string notif;
    notif = to_string(user->getId()) + " " + user->getName() + ": " + NEW_POST_NOTIFICATION ;
    this->notifications.push_back(notif);
}

void User::addNewCourseOfferingNotif(User *user)
{
    string notif;
    notif = to_string(user->getId()) + " " + user->getName() + ": " + NEW_COURSE_OFFER_NOTIFICATION;
    this->notifications.push_back(notif);
}

void User::addGetCourseNotif(User *user)
{
    string notif;
    notif = to_string(user->getId()) + " " + user->getName() + ": " + GET_COURSE_NOTIFICATION;
    this->notifications.push_back(notif);
}

void User::addDeleteCourseNotif(User *user)
{
    string notif;
    notif = to_string(user->getId()) + " " + user->getName() + ": " + DELETE_COURSE_NOTIFICATION;
    this->notifications.push_back(notif);
}

bool User::isItTeacher()
{
    return this->isTeacher;
}

bool User::isItStudent()
{
    return this->isStudent;
}

bool User::isItManager()
{
    return this->isManager;
}

void User::setProfile(string Addr)
{
    this->imageAddr = Addr;
}

void User::addNewCoursePostNotif(BeingOfferedCourse *course)
{
    string notif;
    notif = to_string(course->getId()) + " " + course->getCourseName() + ": " + NEW_COURSE_POST_NOTIFICATION;
    this->notifications.push_back(notif);
}

void User::addNewTAFormNotif(User *user)
{
    string notif;
    notif = to_string(user->getId()) + " " + user->getName() + ": " + NEW_FORM_NOTIFICATION;
    this->notifications.push_back(notif);
}

void User::getAcceptNotif(BeingOfferedCourse *targetCourse)
{
    string notif;
    notif = to_string(targetCourse->getId()) + " " + targetCourse->getCourseName() + ": " + GET_ACCEPT_NOTIFICATION;
    this->notifications.push_back(notif);
}

void User::getRejectedNotif(BeingOfferedCourse *targetCourse)
{
    string notif;
    notif = to_string(targetCourse->getId()) + " " + targetCourse->getCourseName() + ": " + GET_REJECT_NOTIFICATION;
    this->notifications.push_back(notif);
}

string User::getImageAddr()
{
    return this->imageAddr;
}

bool User::haveImage()
{
    if(this->imageAddr == "")
        return false;
    return true;
}

void User::deleteImage()
{
    this->imageAddr = "";
}

vector<Post *> User::getPosts()
{
    return posts;
}
