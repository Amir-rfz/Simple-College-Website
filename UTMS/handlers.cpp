#include "handlers.hpp"

#include <cstdlib>
#include <iostream>
#include "Error.hpp"
#include <ctime>

LoginHandler::LoginHandler(UTMS* utms)
    : utms(utms) {}

Response* LoginHandler::callback(Request* req) {
    std::string username = req->getBodyParam("username");
    std::string password = req->getBodyParam("password");
    std::cout << "username: " << username << ", password: " << password << std::endl;
    try{
        utms->login(username, password);
    }
    catch (Error& error){
        Response* resp;
        if(error.show() == "Bad Request"){
            resp = Response::redirect("/badRequest");
        }
        else if(error.show() == "Not Found"){
            resp = Response::redirect("/notFound");
        }
        else{
            resp = Response::redirect("/permissionDenied");
        }
        return resp;
    }
    Response* res = Response::redirect("/Home");
    res->setSessionId(username);
    return res;
}

HomeHandler::HomeHandler(UTMS* utms)
    : utms(utms) {}

Response* HomeHandler::callback(Request* req) {
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    std::string body;
    int targetUserId = stoll(req->getSessionId());
    User* targetUser = utms->findUserById(targetUserId);

    body += "<!DOCTYPE html>";
    body += "<html lang=\"en\">";

    body += "<head>";
    body += "  <meta charset=\"UTF-8\">";
    body += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    body += "  <title>UTMS</title>";
    body += "<style>";
    body += "  body {font-family: 'Arial', sans-serif;background-color: #f4f4f4;margin: 0;padding: 20px;color: #333;}";
    body += "  h1 {color: #81daf8;}img {border-radius: 50%;margin: 20px 0;}";
    body += "  p {font-size: 18px;}";
    body += "  a {display: inline-block;margin: 10px;padding: 10px 20px;background-color: #81daf8;color: white;text-decoration: none;border-radius: 5px;transition: background-color 0.3s ease;}";
    body += "  a:hover {background-color: #6ccbe5;}";
    body += "  .logout-btn {position: absolute;top: 10px;right: 10px;padding: 10px 20px;}";
    body += "  #menu {position: absolute;top: 10px;left: 10px;cursor: pointer;font-size: 26px;padding: 13px;}";
    body += "  .sidebar {position: fixed;left: -250px;top: 0;width: 250px;height: 100%;background-color: #333;overflow-x: hidden;transition: 0.5s;padding-top: 60px;}";
    body += "  .sidebar a {padding: 10px 15px;text-decoration: none;font-size: 20px;color: #818181;display: block;transition: 0.3s;}";
    body += "  .sidebar a:hover {color: #f1f1f1;}";
    body += "  .sidebar .closebtn {position: absolute;top: 0;right: 5px;font-size: 18px;margin-left: 50px;}";

    
    body += "</style>";
    body += "</head>";

    body += "<body style=\"text-align: center;\">";
    body += "  <h1>WELCOME TO UTMS</h1>";
    if(targetUser->haveImage()){
        body += "<img src=\"/" + targetUser->getImageAddr() + "\" alt=\"Profile\" style=\"width:8%;\"><br>";
    }
    else{
        body += "<img src=\"/defaultPic.png\" alt=\"Profile\" style=\"width:8%;\"><br>";
    }
    body += "  <p>name : " + targetUser->getName() + "</p>";
    if(!targetUser->isItManager()){
        if(targetUser->isItStudent()){
            Student* targetStudent = dynamic_cast<Student*>(targetUser);
            body += "  <p>major : " + targetStudent->major->getMajor() + "</p>";
            body += "  <p>Student id : " + to_string(targetStudent->getId()) + "</p>";
        }
        if(targetUser->isItTeacher()){
            Professor* targetTeacher = dynamic_cast<Professor*>(targetUser);
            body += "  <p>major : " + targetTeacher->major->getMajor() + "</p>";
            body += "  <p>Teacher id : " + to_string(targetTeacher->getId()) + "</p>";        
        }

        body += "  <div id=\"menu\" onclick=\"toggleSidebar()\">☰ Menu</div>";
        body += "  <div id=\"mySidebar\" class=\"sidebar\">";
        body += "     <a href=\"javascript:void(0)\" class=\"closebtn\"";
        body += "  onclick=\"toggleSidebar()\">×</a>";

        body += "  <a href=\"/AddPost\">Send Post</a><br>";
        body += "  <a href=\"/changeProfile\">Change Profile</a><br>";
        body += "  <a href=\"/showAllCourses\">Show all courses</a><br>";
        body += "  <a href=\"/getPage\">Show personal page</a><br>";
        if(targetUser->isItStudent()){
            body += "  <a href=\"/getNewCourse\">Enroll in course</a><br>";
            body += "  <a href=\"/deleteCourse\">Disenroll in course</a><br>";
            body += "  <a href=\"/showCourses\">Show taken courses</a><br>";
        }
        body += "  </div>";
    }
    else{
        body += "  <div id=\"menu\" onclick=\"toggleSidebar()\">☰ Menu</div>";
        body += "  <div id=\"mySidebar\" class=\"sidebar\">";
        body += "     <a href=\"javascript:void(0)\" class=\"closebtn\"";
        body += "  onclick=\"toggleSidebar()\">×</a>";

        body += "  <a href=\"/addOfferedCourse\">Add new offered course</a><br>";
        body += "  <a href=\"/changeProfile\">Change Profile</a><br>";
        body += "  <a href=\"/showAllCourses\">Show all courses</a><br>";
        body += "  </div>";
    }
    body += "  <a href=\"/logout\" class=\"logout-btn\">logout</a>";

    body += "  <script>";
    body += "  function toggleSidebar() {";
    body += "  var sidebar = document.getElementById(\"mySidebar\");";
    body += "  if (sidebar.style.left === \"-250px\") {sidebar.style.left = \"0\";}";
    body += "  else {sidebar.style.left = \"-250px\";}}";
    body += "  </script>";

    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
}


addPostHandler::addPostHandler(UTMS* utms)
    : utms(utms) {}

Response* addPostHandler::callback(Request* req) {
    std::string title = req->getBodyParam("title");
    std::string message = req->getBodyParam("message");

    std::time_t t = std::time(0);
    std::string file = req->getBodyParam("file");
    std::string imageAddr = "upload/" + to_string(t) + ".png";
    if(file == ""){
        imageAddr = "";
    }
    utils::writeToFile(file, imageAddr);
    
    try{
        utms->addNewPost(title , message , imageAddr);
    }
    catch (Error& error){
        Response* resp;
        if(error.show() == "Bad Request"){
            resp = Response::redirect("/badRequest");
        }
        else if(error.show() == "Not Found"){
            resp = Response::redirect("/notFound");
        }
        else{
            resp = Response::redirect("/permissionDenied");
        }
        return resp;
    }
    Response* res = Response::redirect("/Home");
    return res;
}

changeProfileHandler::changeProfileHandler(UTMS* utms)
    : utms(utms) {}

Response* changeProfileHandler::callback(Request* req) {

    std::time_t t = std::time(0);
    std::string file = req->getBodyParam("file");
    std::string imageAddr = "upload/" + to_string(t) + ".png";
    utils::writeToFile(file, imageAddr);

    try{
        utms->setProfile(imageAddr);
    }
    catch (Error& error){
        Response* resp;
        if(error.show() == "Bad Request"){
            resp = Response::redirect("/badRequest");
        }
        else if(error.show() == "Not Found"){
            resp = Response::redirect("/notFound");
        }
        else{
            resp = Response::redirect("/permissionDenied");
        }
        return resp;
    }
    Response* res = Response::redirect("/Home");
    return res;
}

deleteProfileHandler::deleteProfileHandler(UTMS* utms)
    : utms(utms) {}

Response* deleteProfileHandler::callback(Request* req) {
    int targetUserId = stoll(req->getSessionId());
    User* targetUser = utms->findUserById(targetUserId);
    targetUser->deleteImage();

    Response* res = Response::redirect("/Home");
    return res;
    
}

showAllCoursesHandler::showAllCoursesHandler(UTMS* utms)
    : utms(utms) {}

Response* showAllCoursesHandler::callback(Request* req) {
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    std::string body;
    int targetUserId = stoll(req->getSessionId());
    User* targetUser = utms->findUserById(targetUserId);

    Student* targetStudent = dynamic_cast<Student*>(targetUser);
    vector<BeingOfferedCourse*> allCourses = utms->getBeingOfferedCourses();

    body += "<!DOCTYPE html>";
    body += "<html lang=\"en\">";

    body += "<head>";
    body += "  <meta charset=\"UTF-8\">";
    body += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    body += "  <title>All Courses</title>";
    body += "</head>";

    body += "<style>";
    body += "  body { font-family: 'Arial', sans-serif; background-color: #f4f4f4; margin: 0; padding: 20px; }";
    body += "  h1 { color: #81daf8; }";
    body += "  p { color: #666;}";
    body += "  a { display: inline-block; margin-top: 20px; padding: 10px 20px; background-color: #81daf8; color: white; text-decoration: none; border-radius: 5px;transition: background-color 0.3s ease; }";
    body += "  a:hover {background-color: #6ccbe5;}";
    body += "</style>";

    body += "<body style=\"text-align: center;\">";
    body += "  <h1>All Courses</h1>";

    if(allCourses.size() == 0){
        body += "  <p>No course being offered yet</p>";
        body += "  <a href=\"/Home\">back to home</a><br>";
        body += "</body>";
        body += "</html>";
    }
    else{
        for(auto course : allCourses){
            body += "<div style=\"display: flex; align-items: center; justify-content: flex-start; background-color: #e0e0e0; margin: 10px auto; padding: 10px; border-radius: 5px; width: 35%;\">";
            body += "  <div style=\"text-align: left;\">";
            body += "  <p> ID : " + to_string(course->getId()) + "</p>";
            body += "  <p> Name : " + course->getCourseName() + "</p>";
            body += "  <p> capacity : " + course->getcapacity() + "</p>";
            body += "  <p> Professor : " + course->getProfessor() + "</p>";
            body += "  </div>";
            body += "</div>";
        }
        body += "  <a href=\"/Home\">back to home</a><br>";
        body += "</body>";
        body += "</html>";
    }
    res->setBody(body);
    return res;
}

getPageHandler::getPageHandler(UTMS* utms)
    : utms(utms) {}

Response* getPageHandler::callback(Request* req) {
    std::string id = req->getBodyParam("id");
    std::cout << "id: " << id << std::endl;
    try{
        utms->findTargetUserForShowingInformation(id);
    }
    catch (Error& error){
        Response* resp;
        if(error.show() == "Bad Request"){
            resp = Response::redirect("/badRequest");
        }
        else if(error.show() == "Not Found"){
            resp = Response::redirect("/notFound");
        }
        else{
            resp = Response::redirect("/permissionDenied");
        }
        return resp;
    }
    Response* res = Response::redirect("/showPage");
    return res;
}

showPageHandler::showPageHandler(UTMS* utms)
    : utms(utms) {}

Response* showPageHandler::callback(Request* req) {
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    std::string body;
    User* targetUser = utms->getTargetUserForShowingInformation();
    vector<string> informations = targetUser->showInfo();
    vector<Post*> posts = targetUser->getPosts();

    body += "<!DOCTYPE html>";
    body += "<html lang=\"en\">";

    body += "<head>";
    body += "  <meta charset=\"UTF-8\">";
    body += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    body += "  <title>Show personal page</title>";
    body += "</head>";

    body += "<style>";
    body += "  body { font-family: Arial, sans-serif; margin: 0; padding: 0; text-align: center; background-color: #f4f4f4;}";
    body += "  h1 { color: #333; }";
    body += "  p { color: #666; }";
    body += "  a { display: inline-block; margin-top: 20px; padding: 10px 20px; background-color: #81daf8; color: white; text-decoration: none; border-radius: 5px; transition: background-color 0.3s ease;}";
    body += "  a:hover {background-color: #6ccbe5;}";
    body += "</style>";

    body += "<body style=\"text-align: center;\">";
    body += "  <h1>Informations : </h1>";
    if(targetUser->haveImage()){
        body += "<img src=\"/" + targetUser->getImageAddr() + "\" alt=\"Profile\" style=\"width:5%;border-radius: 50%;\"><br>";
    }
    else{
        body += "<img src=\"/defaultPic.png\" alt=\"Profile\" style=\"width:5%;border-radius: 50%;\"><br>";
    }

    for(auto info : informations){
        body += "  <p>" + info + "</p>";
    }
    body += "  <h1>Posts : </h1>";
    if(posts.size() == 0){
        body += "  <p>No Post being posted yet</p>";
        body += "  <a href=\"/Home\">back to home</a><br>";
        body += "</body>";
        body += "</html>";
    }
    else{
        for(auto post : posts){
            body += "<div style=\"display: flex; align-items: center; justify-content: flex-start; background-color: #e0e0e0; margin: 10px auto; padding: 10px; border-radius: 5px; width: 35%;\">";
            if(post->getImageAddr() != ""){
                body += "  <img src=\"/"  + post->getImageAddr() +  "\" alt=\"Profile\" style=\"width:14%; margin-right: 10px;\">";
            }
            body += "  <div style=\"text-align: left;\">";
            body += "  <p> ID : " + to_string(post->getId()) + "</p>";
            body += "  <p> Title : " + post->getTitle() + "</p>";
            body += "  <p> Message : " + post->getMessage() + "</p>";
            body += "  </div>";
            body += "</div>";
        }
        body += "  <a href=\"/Home\">back to home</a><br>";
        body += "</body>";
        body += "</html>";
    }
    res->setBody(body);
    return res;
}

getNewCourseHandler::getNewCourseHandler(UTMS* utms)
    : utms(utms) {}

Response* getNewCourseHandler::callback(Request* req) {
    std::string id = req->getBodyParam("id");
    std::cout << "id: " << id << std::endl;
    try{
        utms->getNewCourse(id);
    }
    catch (Error& error){
        Response* resp;
        if(error.show() == "Bad Request"){
            resp = Response::redirect("/badRequest");
        }
        else if(error.show() == "Not Found"){
            resp = Response::redirect("/notFound");
        }
        else{
            resp = Response::redirect("/permissionDenied");
        }
        return resp;
    }
    Response* res = Response::redirect("/Home");
    return res;
}

deleteCourseHandler::deleteCourseHandler(UTMS* utms)
    : utms(utms) {}

Response* deleteCourseHandler::callback(Request* req) {
    std::string id = req->getBodyParam("id");
    std::cout << "id: " << id << std::endl;
    try{
        utms->deleteFromCourses(id);
    }
    catch (Error& error){
        Response* resp;
        if(error.show() == "Bad Request"){
            resp = Response::redirect("/badRequest");
        }
        else if(error.show() == "Not Found"){
            resp = Response::redirect("/notFound");
        }
        else{
            resp = Response::redirect("/permissionDenied");
        }
        return resp;
    }
    Response* res = Response::redirect("/Home");
    return res;
}

showCoursesHandler::showCoursesHandler(UTMS* utms)
    : utms(utms) {}

Response* showCoursesHandler::callback(Request* req) {
    Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
    std::string body;
    int targetUserId = stoll(req->getSessionId());
    User* targetUser = utms->findUserById(targetUserId);
    Student* targetStudent = dynamic_cast<Student*>(targetUser);
    vector<BeingOfferedCourse*> targetCourses = targetStudent->getCourses();

    body += "<!DOCTYPE html>";
    body += "<html lang=\"en\">";

    body += "<head>";
    body += "  <meta charset=\"UTF-8\">";
    body += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    body += "  <title>Courses</title>";
    body += "</head>";

    body += "<style>";
    body += "  body { font-family: 'Arial', sans-serif; background-color: #f4f4f4; margin: 0; padding: 20px; }";
    body += "  h1 { color: #81daf8; }";
    body += "  p { color: #666;}";
    body += "  a { display: inline-block; margin-top: 20px; padding: 10px 20px; background-color: #81daf8; color: white; text-decoration: none; border-radius: 5px; transition: background-color 0.3s ease;}";
    body += "  a:hover {background-color: #6ccbe5;}";
    body += "</style>";

    body += "<body style=\"text-align: center;\">";
    body += "  <h1>Your Courses</h1>";

    if(targetCourses.size() == 0){
        body += "  <p>No course taken yet</p>";
        body += "  <a href=\"/Home\">back to home</a><br>";
        body += "</body>";
        body += "</html>";
    }
    else{
        for(auto course : targetCourses){
            body += "<div style=\"display: flex; align-items: center; justify-content: flex-start; background-color: #e0e0e0; margin: 10px auto; padding: 10px; border-radius: 5px; width: 35%;\">";
            body += "  <div style=\"text-align: left;\">";
            body += "  <p> ID : " + to_string(course->getId()) + "</p>";
            body += "  <p> Name : " + course->getCourseName() + "</p>";
            body += "  <p> capacity : " + course->getcapacity() + "</p>";
            body += "  <p> Professor : " + course->getProfessor() + "</p>";
            body += "  <p> Class Time : " + course->getClassTime() + "</p>";
            body += "  <p> Exam Date : " + course->getExamDate() + "</p>";
            body += "  <p> Class Number : " + course->getClassNum() + "</p>";
            body += "  </div>";
            body += "</div>";
        }
        body += "  <a href=\"/Home\">back to home</a><br>";
        body += "</body>";
        body += "</html>";
    }
    res->setBody(body);
    return res;
}

addOfferedCourseHandler::addOfferedCourseHandler(UTMS* utms)
    : utms(utms) {}

Response* addOfferedCourseHandler::callback(Request* req) {
    std::string courseId = req->getBodyParam("courseId");
    std::string professorId = req->getBodyParam("professorId");
    std::string capacity = req->getBodyParam("capacity");
    std::string time = req->getBodyParam("time");
    std::string examDate = req->getBodyParam("examDate");
    std::string classNumber = req->getBodyParam("classNumber");
    std::cout << "courseId: " << courseId << ", professorId: " << professorId << ", capacity: " << capacity << ", time: " << time
    << ", examDate: " << examDate << ", classNumber: " << classNumber << std::endl;
    try{
        utms->addNewCourse(courseId,professorId,capacity,time,examDate,classNumber);
    }
    catch (Error& error){
        Response* resp;
        if(error.show() == "Bad Request"){
            resp = Response::redirect("/badRequest");
        }
        else if(error.show() == "Not Found"){
            resp = Response::redirect("/notFound");
        }
        else{
            resp = Response::redirect("/permissionDenied");
        }
        return resp;
    }
    Response* res = Response::redirect("/Home");
    return res;
}

LogoutHandler::LogoutHandler(UTMS* utms)
    : utms(utms) {}

Response* LogoutHandler::callback(Request* req) {
    try{
        utms->logout();
    }
    catch (Error& error){
        Response* resp;
        if(error.show() == "Bad Request"){
            resp = Response::redirect("/badRequest");
        }
        else if(error.show() == "Not Found"){
            resp = Response::redirect("/notFound");
        }
        else{
            resp = Response::redirect("/permissionDenied");
        }
        return resp;
    }
    Response* res = Response::redirect("/");
    res->setSessionId("");
    return res;
}

Response* ImageHandler::callback(Request* req) {
    Response* res = new Response();
    string urlPath = req->getPath();
    string filePath = urlPath.substr(1, urlPath.size()-1);
    res->setHeader("Content-Type", "image/" + utils::getExtension(filePath));
    res->setBody(utils::readFile(filePath));
    return res;
}