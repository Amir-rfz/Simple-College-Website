#ifndef Chanel_HPP
#define Chanel_HPP

#include <iostream>
#include <string>
#include <vector>
#include "User.hpp"

using namespace std;

class BeingOfferedCourse;
class Post;
class Chanel
{
private:
    vector<User*> members;
    vector<Post*> posts;
    BeingOfferedCourse* course;
public:
    Chanel(BeingOfferedCourse* course);
    void addNewPost(Post* post, User* user);
    vector<string> showPosts(vector<string>* result);
    Post* findPostById(int postId);
    vector<string> showPost(int postId , vector<string>* result);
    void addNewMember(User* user);
    void removeMember(User* user);
};

#endif