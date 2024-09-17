#ifndef UTMS_HPP
#define UTMS_HPP

#include <iostream>
#include <string>
#include <vector>
#include "BadRequest.hpp"
#include "Empty.hpp"
#include "NotFound.hpp"
#include "PermissionDenied.hpp"
#include "Student.hpp"
#include "Professor.hpp"
#include "Major.hpp"
#include "Course.hpp"
#include "Manager.hpp"
#include "beingOfferedCourses.hpp"
#include "Date.hpp"
#include "Time.hpp"

using namespace std;
class BeingOfferedCourse;
class Professor;
class Student;
class TAForm;

class UTMS
{
private:

    Manager* manager;
    vector<Student*> students;
    vector<Professor*> professors;
    vector<Course*> courses;
    vector<Major*> majors;
    vector<BeingOfferedCourse*> beingOfferedCourses;
    int offeredCourseIndex;
    vector<TAForm*> TAForms;
    User* targetUserForShowingInformation;
    
public:

    User* currentUser;
    UTMS(string majorsPath,string studentsPath,string coursesPath,string ProfessorsPath);
    Major* findMajorById(int major_id);
    bool isLoginBefor();
    void login(string id , string password);
    bool isIdExist(int id);
    bool isPassCorrect(int id , string password);
    void logout();
    BeingOfferedCourse* findCourseByID(int course_id);
    vector<BeingOfferedCourse*> getBeingOfferedCourses();
    string getBeingOfferedCourse(int courseId);
    void addNewPost(string title,string message,string imageAddr);
    void deletePost(int id);
    vector<string> showPage(string id);
    User* findUserById(int id);
    vector<string> getPost(int id, int postId);
    void connectWith(int id);
    vector<string> SowNotification();
    void sendNewPostNotif(User* manager);
    void sendNewCourseOfferingNotif(User* manager);
    Course* giveCourseByID(int courseId);
    Professor* giveProfessorByID(int professorId);
    void addNewCourse(string courseId , string professorId, string capacity ,string classTime ,string examDate ,string classNumber);
    void getNewCourse(string courseId);
    void deleteFromCourses(string id);
    vector<string> ShowingCourses();
    void setProfile(string Addr);
    void addNewCoursePost(int id,string title,string message, string image);
    vector<string> getCourseChanel(int id);
    vector<string> getCoursePost(int id,int postId);
    void addNewTAForm(int course_id , string message);
    TAForm* getTAFormRequests(int id);
    void deleteFromTAForm(TAForm* targetTAForm);
    void addNewTAReq(int professor_id , int form_id);
    bool isNaturalNumber(const std::string& str);
    void findTargetUserForShowingInformation(string ID);
    User* getTargetUserForShowingInformation();
    
};

#endif