#ifndef User_HPP
#define User_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Post.hpp"
#include "NotFound.hpp"
#include "Empty.hpp"

using namespace std;
class BeingOfferedCourse;
class User
{
protected:

    int id;
    string name;
    string password;
    string imageAddr;
    vector<Post*> posts;
    vector<User*> connectUsers;
    vector<string> notifications;
    int postIndex;
    bool isTeacher;
    bool isStudent;
    bool isManager;

public:

    User(int id, string password, string name);
    int getId();
    string getName();
    virtual string getPass();
    void addNewPost(string title,string message,string imageAddr);
    void sendNotif();
    void deletePost(int id);
    virtual vector<vector<string>> showPosts() = 0;
    virtual vector<string> showInfo() = 0;
    string showPost(int postId);
    bool isConnectBefor(int id);
    void getConnect(User* wantedUser);
    vector<string> ShowNotifications();
    void addNewPostNotif(User* user);
    void addNewCourseOfferingNotif(User *user);
    void addGetCourseNotif(User *user);
    void addDeleteCourseNotif(User *user);
    bool isItTeacher();
    bool isItStudent();
    bool isItManager();
    void setProfile(string Addr);
    virtual bool haveAccessToCourseChanel(int CourseId) = 0;
    virtual bool haveAccessToGetCourseChanel(int CourseId) = 0;
    void addNewCoursePostNotif(BeingOfferedCourse* course);
    void addNewTAFormNotif(User* user);
    void getAcceptNotif(BeingOfferedCourse* targetCourse);
    void getRejectedNotif(BeingOfferedCourse* targetCourse);
    string getImageAddr();
    bool haveImage();
    void deleteImage();
    vector<Post*> getPosts();
};

#endif