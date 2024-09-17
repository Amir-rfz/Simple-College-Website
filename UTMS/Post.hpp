#ifndef Post_HPP
#define Post_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Post
{
private:

    int id;
    string title;
    string message;
    string imageAddr;
    string author_name;

public:

    Post(string title, string message ,int id,string imageAddr);
    Post(string title, string message ,int id,string imageAddr,string author_name);
    Post(string title, string message ,int id);
    int getId();
    virtual string showPostSummery();
    string getTitle();
    virtual string showPost();
    string showChanelPost();
    string showFullChanelPost();
    string getMessage();
    string getImageAddr();
    
};

#endif