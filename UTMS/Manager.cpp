#include "Manager.hpp"

Manager::Manager(int id, string password): User(id , password , MANAGER_USERNAME){
    this->isManager = true;
}

vector<vector<string>> Manager::showPosts()
{
    vector<vector<string>> result;
    for(auto post : posts){
        vector<string> Post;
        Post.push_back(post->getImageAddr());
        Post.push_back(" " + to_string(post->getId()) +"  \""+post->getTitle()+"\" "+" \""+post->getMessage()+"\"");
        result.push_back(Post);
    }
    return result;
}

vector<string> Manager::showInfo()
{
    vector<string> result;
    result.push_back("name : " + this->name);
    result.push_back("User type : Manager");
    return result;
}

bool Manager::haveAccessToCourseChanel(int courseId)
{
    return false;
}

bool Manager::haveAccessToGetCourseChanel(int CourseId)
{
    return false;
}
