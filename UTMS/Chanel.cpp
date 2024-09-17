#include "Chanel.hpp"

Chanel::Chanel(BeingOfferedCourse* course)
{
    this->course = course;
}

void Chanel::addNewPost(Post *post,User* user)
{
    this->posts.push_back(post);
    for(auto member : members){
        if(member->getId() != user->getId()){
            member->addNewCoursePostNotif(this->course);
        }
    }
}

vector<string> Chanel::showPosts(vector<string> *result)
{
    for(int i=posts.size()-1 ; i >= 0 ; i--){
        result->push_back(posts[i]->showChanelPost());
    }
    return *result;
}

Post *Chanel::findPostById(int postId)
{
    for(auto post : posts){
        if(post->getId() == postId) 
            return post;
    }
    throw NotFound();
}

vector<string> Chanel::showPost(int postId, vector<string> *result)
{
    Post* targetPost = this->findPostById(postId);
    result->push_back(targetPost->showFullChanelPost());
    return *result;
}

void Chanel::addNewMember(User *user)
{
    this->members.push_back(user);
}

void Chanel::removeMember(User *user)
{
    for(int i=0 ; i < this->members.size() ; i++){
        if(members[i]->getId() == user->getId()){
			members.erase(members.begin() + i);
            return;           
        }
    }
}
