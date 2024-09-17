#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include <map>
#include <string>

#include "../server/server.hpp"
#include "UTMS.hpp"


class LoginHandler : public RequestHandler {
private:
    UTMS* utms;
public:
    LoginHandler(UTMS* utms);
    Response* callback(Request*) override;
};

class HomeHandler : public RequestHandler {
private:
    UTMS* utms;
public:
    HomeHandler(UTMS* utms);
    Response* callback(Request*) override;   
};

class addPostHandler : public RequestHandler {
private:
    UTMS* utms;
public:
    addPostHandler(UTMS* utms);
    Response* callback(Request*) override;
};

class changeProfileHandler : public RequestHandler {
private:
    UTMS* utms;
public:
    changeProfileHandler(UTMS* utms);
    Response* callback(Request*) override;
};

class deleteProfileHandler : public RequestHandler {
private:
    UTMS* utms;
public:
    deleteProfileHandler(UTMS* utms);
    Response* callback(Request*) override;
};

class showAllCoursesHandler : public RequestHandler {
private:
    UTMS* utms;
public:
    showAllCoursesHandler(UTMS* utms);
    Response* callback(Request*) override;   
};

class getPageHandler : public RequestHandler {
private:
    UTMS* utms;
public:
    getPageHandler(UTMS* utms);
    Response* callback(Request*) override;
};

class showPageHandler : public RequestHandler {
private:
    UTMS* utms;
public:
    showPageHandler(UTMS* utms);
    Response* callback(Request*) override;   
};

class getNewCourseHandler : public RequestHandler {
private:
    UTMS* utms;
public:
    getNewCourseHandler(UTMS* utms);
    Response* callback(Request*) override;
};

class deleteCourseHandler : public RequestHandler {
private:
    UTMS* utms;
public:
    deleteCourseHandler(UTMS* utms);
    Response* callback(Request*) override;
};

class showCoursesHandler : public RequestHandler {
private:
    UTMS* utms;
public:
    showCoursesHandler(UTMS* utms);
    Response* callback(Request*) override;   
};

class addOfferedCourseHandler : public RequestHandler {
private:
    UTMS* utms;
public:
    addOfferedCourseHandler(UTMS* utms);
    Response* callback(Request*) override;
};

class LogoutHandler : public RequestHandler {
private:
    UTMS* utms;
public:
    LogoutHandler(UTMS* utms);
    Response* callback(Request*) override;
};

class ImageHandler : public RequestHandler {
public:
    Response* callback(Request*) override;
};

#endif
