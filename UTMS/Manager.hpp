#ifndef Manager_HPP
#define Manager_HPP

#include <iostream>
#include <string>
#include <vector>
#include "User.hpp"

using namespace std;
const string MANAGER_USERNAME = "UT_account";

class Manager : public User
{
private:
    
public:
    Manager(int id = 0 , string password = MANAGER_USERNAME);
    vector<vector<string>> showPosts();
    vector<string> showInfo();
    bool haveAccessToCourseChanel(int courseId);
    bool haveAccessToGetCourseChanel(int CourseId);
};

#endif