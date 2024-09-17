#include "Post.hpp"

Post::Post(string title, string message , int id, string imageAddr)
{
    this->message = message;
    this->title = title;
    this->id = id;
    this->imageAddr = imageAddr;
}

Post::Post(string title, string message, int id, string imageAddr, string author_name)
{
    this->message = message;
    this->title = title;
    this->id = id;
    this->imageAddr = imageAddr;
    this->author_name = author_name;
}

Post::Post(string title, string message, int id)
{
    this->message = message;
    this->title = title;
    this->id = id;
}

int Post::getId()
{
    return this->id;
}

string Post::showPostSummery()
{
    return to_string(this->getId()) + " \"" + this->getTitle() + "\"";
}

string Post::getTitle()
{
    return this->title ;
}

string Post::showPost()
{
    return to_string(this->id) + " \"" + this->title + "\" " +  "\"" + this->message + "\" ";
}

string Post::showChanelPost()
{
    return to_string(this->id) +" "+ this->author_name +" \"" + this->title + "\" ";
}

string Post::showFullChanelPost()
{
    return to_string(this->id) +" "+ this->author_name +" \"" + this->title + "\" " +  "\"" + this->message + "\" ";
}

string Post::getMessage()
{
    return this->message;
}

string Post::getImageAddr()
{
    return this->imageAddr;
}
