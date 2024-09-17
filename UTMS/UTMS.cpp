#include "UTMS.hpp"
#include "CSVReader.hpp"
#include "TAForm.hpp"

vector<int> splitString(string someString, char separator)
{
    int i = 0;
    vector<int> result;
    string s;
    while (someString[i] != '\0'){
        if (someString[i] != separator){
            s += someString[i];
        }
        else{
            result.push_back(stoi(s));
            s.clear();
        }
        i++;
    }
    result.push_back(stoi(s));
    return result;
}

bool UTMS::isNaturalNumber(const std::string& str){
    if(str.empty()) return false;
    for(char c : str) {
        if(!isdigit(c)) return false;
    }
    return true;
}

UTMS::UTMS(string majorsPath,string studentsPath,string coursesPath,string ProfessorsPath){
    this->currentUser = NULL;
    this->manager = new Manager();
    this->offeredCourseIndex = 1;

    CsvReader csvReaderMajors(majorsPath);
    while (csvReaderMajors.GoToNextLine()) {
        int id = stoi(csvReaderMajors.GetNextItem());
        string name = csvReaderMajors.GetNextItem();
        this->majors.push_back(new Major(id , name));
    }
    CsvReader csvReaderCourse(coursesPath);
        while (csvReaderCourse.GoToNextLine()) {
        int cid = stoi(csvReaderCourse.GetNextItem());
        string name = csvReaderCourse.GetNextItem();
        int credit = stoi(csvReaderCourse.GetNextItem());
        int prerequisite = stoi(csvReaderCourse.GetNextItem());
        string majorsString = csvReaderCourse.GetNextItem();
        vector<int> majors_id = splitString(majorsString , ';');
        this->courses.push_back(new Course(cid, name, credit, prerequisite, majors_id));
    }
    CsvReader csvReaderStudent(studentsPath);
        while (csvReaderStudent.GoToNextLine()) {
        int sid = stoi(csvReaderStudent.GetNextItem());
        string name = csvReaderStudent.GetNextItem();
        int major_id = stoi(csvReaderStudent.GetNextItem());
        Major* targetMajor = findMajorById(major_id);
        int semester = stoi(csvReaderStudent.GetNextItem());
        string password = csvReaderStudent.GetNextItem();
        this->students.push_back(new Student(sid, name, targetMajor, semester, password));
    }
    CsvReader csvReaderProfessor(ProfessorsPath);
        while (csvReaderProfessor.GoToNextLine()) {
        int pid = stoi(csvReaderProfessor.GetNextItem());
        string name = csvReaderProfessor.GetNextItem();
        int major_id = stoi(csvReaderProfessor.GetNextItem());
        Major* targetMajor = findMajorById(major_id);
        string position = csvReaderProfessor.GetNextItem();
        string password = csvReaderProfessor.GetNextItem();
        this->professors.push_back(new Professor(pid, name, targetMajor, position, password));
    }
}

Major *UTMS::findMajorById(int major_id)
{
    for(auto major : majors){
        if(major->getId() == major_id)
            return major;
    }
    return NULL;
}

bool UTMS::isLoginBefor()
{
    if(this->currentUser == NULL)
        return false;
    return true;
}

void UTMS::login(string idString , string password)
{
    if(password == "" || idString == "") throw BadRequest();
    if (this->isLoginBefor()) throw PermissionDenied();
    if(!isNaturalNumber(idString)) throw BadRequest();
    int id = stoll(idString);
    if(isIdExist(id)){
        if(isPassCorrect(id , password)){
            for(auto student : students){
                if(student->getId() == id)
                    this->currentUser = student;
            }
            for(auto professor : professors){
                if(professor->getId() == id)
                    this->currentUser = professor;
            }
            if(this->manager->getId() == id)
                this->currentUser = this->manager;
        }
        else{
            throw PermissionDenied();
        }
    }
    else{
        throw NotFound();
    }
}

bool UTMS::isIdExist(int id)
{
    for(auto student : students){
        if(student->getId() == id)
            return true;
    }
    for(auto professor : professors){
        if(professor->getId() == id)
            return true;
    }
    if(this->manager->getId() == id){
        return true;
    }
    return false;
}

bool UTMS::isPassCorrect(int id, string password)
{
    for(auto student : students){
        if(student->getId() == id){
            if(student->getPass() == password)
                return true;
        }
    }
    for(auto professor : professors){
        if(professor->getId() == id){
            if(professor->getPass() == password)
                return true;
        }
    }
    if(this->manager->getId() == id){
        if(this->manager->getPass() == password)
            return true;
    }
    return false;
}

void UTMS::logout()
{
    if (!this->isLoginBefor()) throw PermissionDenied();
    this->currentUser = NULL;
}

BeingOfferedCourse* UTMS::findCourseByID(int course_id)
{
    for(auto course : beingOfferedCourses){
        if(course->getId() == course_id)
            return course;
    }
    throw NotFound();
}

vector<BeingOfferedCourse*> UTMS::getBeingOfferedCourses()
{
    if (!this->isLoginBefor()) throw PermissionDenied();
    return this->beingOfferedCourses;
}

string UTMS::getBeingOfferedCourse(int courseId)
{
    for(auto course : beingOfferedCourses){
        if(course->getId() == courseId)
            return course->ShowAllDetail();
    }
    throw NotFound();
}

void UTMS::addNewPost(string title, string message,string imageAddr)
{
    if(message == "" || title == "") throw BadRequest();
    if (!this->isLoginBefor()) throw PermissionDenied();
    if(this->currentUser == NULL) throw PermissionDenied();

    if(this->currentUser->isItManager())
        this->sendNewPostNotif(this->currentUser);
    
    this->currentUser->addNewPost(title,message,imageAddr);
}

void UTMS::deletePost(int id)
{
    if(this->currentUser == NULL) throw PermissionDenied();
    this->currentUser->deletePost(id);
}

User* UTMS::findUserById(int id)
{
    for(auto student : students){
        if(student->getId() == id)
            return student;
    }
    for(auto professor : professors){
        if(professor->getId() == id)
            return professor;
    }
    if(manager->getId() == id){
        return manager;
    }
    throw NotFound();
}

vector<string> UTMS::getPost(int id, int postId)
{
    vector<string> result;
    User* wantUser = this->findUserById(id);
    result = wantUser->showInfo();
    result.push_back(wantUser->showPost(postId));
    return result;
}

void UTMS::connectWith(int id)
{
    if(this->currentUser == NULL) throw PermissionDenied();
    if(this->currentUser->isConnectBefor(id) || this->currentUser->isItManager() || id == 0) throw BadRequest();
    User* wantedUser = this->findUserById(id);
    this->currentUser->getConnect(wantedUser);
    wantedUser->getConnect(this->currentUser);

}

vector<string> UTMS::SowNotification()
{
    if(this->currentUser == NULL) throw PermissionDenied();
    vector<string> result;
    result = this->currentUser->ShowNotifications();
    return result;
}

void UTMS::sendNewPostNotif(User *manager)
{
    for(auto student : students){
        student->addNewPostNotif(manager);
    }
    for(auto professor : professors){
        professor->addNewPostNotif(manager);
    }
}

void UTMS::sendNewCourseOfferingNotif(User *manager)
{
    for(auto student : students){
        student->addNewCourseOfferingNotif(manager);
    }
    for(auto professor : professors){
        professor->addNewCourseOfferingNotif(manager);
    }
}

Course *UTMS::giveCourseByID(int courseId)
{
    for(auto course : courses){
        if(course->getId() == courseId)
            return course;
    }
    throw NotFound();
}

Professor *UTMS::giveProfessorByID(int professorId)
{
    for(auto professor : professors){
        if(professor->getId() == professorId)
            return professor;
    }
    throw NotFound();
}

void UTMS::addNewCourse(string courseIdString , string professorIdString, string capacityString ,string timeString ,string examDateString ,string classNumberString)
{
    if(courseIdString == "" || professorIdString == "" || capacityString == "" || timeString == "" || examDateString == "" || classNumberString == "")throw BadRequest();
    if(!isNaturalNumber(courseIdString) || stoll(courseIdString) == 0) throw BadRequest();
    if(!isNaturalNumber(professorIdString ) || stoll(professorIdString) == 0) throw BadRequest();
    if(!isNaturalNumber(capacityString) || stoll(capacityString) == 0) throw BadRequest();
    if(!isNaturalNumber(classNumberString) || stoll(classNumberString) == 0) throw BadRequest();
    if (!this->isLoginBefor()) throw PermissionDenied();
    if(this->currentUser == NULL || !this->currentUser->isItManager()) throw PermissionDenied();

    int courseId = stoll(courseIdString);
    int professorId = stoll(professorIdString);
    int capacity = stoll(capacityString);
    Time* classTime = new Time(timeString);
    Date* examDate = new Date(examDateString);
    int classNumber = stoll(classNumberString);
    Course* wantedCourse = this->giveCourseByID(courseId);

    for(auto student : students){
        if(student->getId() == professorId || manager->getId() == professorId){
            throw PermissionDenied();
        }
    }

    Professor* wantedProfessor = this->giveProfessorByID(professorId);

    if(!wantedProfessor->ableToTakeCourse(wantedCourse)) throw PermissionDenied();
    if(wantedProfessor->haveInterferenceTime(classTime)) throw PermissionDenied();
    
    BeingOfferedCourse* newBeingOfferedCourse = new BeingOfferedCourse(wantedCourse, wantedProfessor, capacity, classTime, examDate, classNumber ,offeredCourseIndex);
    this->offeredCourseIndex += 1;
    this->beingOfferedCourses.push_back(newBeingOfferedCourse);
    wantedProfessor->addNewCourse(newBeingOfferedCourse);
    this->sendNewCourseOfferingNotif(wantedProfessor);
}

void UTMS::getNewCourse(string courseId)
{
    if(!isNaturalNumber(courseId) || stoll(courseId) == 0 || courseId == "") throw BadRequest();
    if (!this->isLoginBefor()) throw PermissionDenied();
    if(this->currentUser == NULL || !this->currentUser->isItStudent()) throw PermissionDenied();
    Student* targetStudent = dynamic_cast<Student*>(this->currentUser);
    BeingOfferedCourse* wantedCourse;
    wantedCourse = findCourseByID(stoll(courseId));
    if(targetStudent->getSemester() < wantedCourse->getPrerequisite()) throw PermissionDenied();
    if(!wantedCourse->haveMajor(targetStudent->getMajor())) throw PermissionDenied();
    if(targetStudent->haveInterference(wantedCourse)) throw PermissionDenied();
    targetStudent->getNewCourse(wantedCourse);
    wantedCourse->addNewMember(targetStudent);
}

void UTMS::deleteFromCourses(string id)
{
    if(!isNaturalNumber(id) || stoll(id) == 0 || id == "") throw BadRequest();
    if (!this->isLoginBefor()) throw PermissionDenied();
    if(this->currentUser == NULL || !this->currentUser->isItStudent()) throw PermissionDenied();
    Student* targetStudent = dynamic_cast<Student*>(this->currentUser);
    targetStudent->deleteFromCourses(stoll(id));
}

vector<string> UTMS::ShowingCourses()
{
    if (!this->isLoginBefor()) throw PermissionDenied();
    if(this->currentUser == NULL || !this->currentUser->isItStudent()) throw PermissionDenied();
    vector<string> result;
    Student* targetStudent = dynamic_cast<Student*>(this->currentUser);
    result = targetStudent->ShowCourses();
    return result;
}

void UTMS::setProfile(string Addr)
{
    if(Addr == "") throw BadRequest();
    if (!this->isLoginBefor()) throw PermissionDenied();
    if(this->currentUser == NULL) throw PermissionDenied();
    this->currentUser->setProfile(Addr);
}

void UTMS::addNewCoursePost(int id, string title, string message, string image)
{
    if(this->currentUser == NULL || this->currentUser->isItManager()) throw PermissionDenied();
    BeingOfferedCourse* targetCourse = findCourseByID(id);
    if(!this->currentUser->haveAccessToCourseChanel(id)) throw PermissionDenied();
    targetCourse->addNewPost(title, message, image, this->currentUser);
}

vector<string> UTMS::getCourseChanel(int id)
{
    vector<string> result;
    if(this->currentUser == NULL || this->currentUser->isItManager()) throw PermissionDenied();
    BeingOfferedCourse* targetCourse = findCourseByID(id);
    if(!this->currentUser->haveAccessToGetCourseChanel(id)) throw PermissionDenied();

    result = targetCourse->showChanel();
    return result;
}

vector<string> UTMS::getCoursePost(int id, int postId)
{
    vector<string> result;
    if(this->currentUser == NULL || this->currentUser->isItManager()) throw PermissionDenied();
    BeingOfferedCourse* targetCourse = findCourseByID(id);
    if(!this->currentUser->haveAccessToGetCourseChanel(id)) throw PermissionDenied();

    result = targetCourse->showPost(postId);

    return result;
}

void UTMS::addNewTAForm(int course_id, string message)
{
    if(this->currentUser == NULL || !this->currentUser->isItTeacher()) throw PermissionDenied();
    BeingOfferedCourse* targetCourse = findCourseByID(course_id);
    if(!this->currentUser->haveAccessToCourseChanel(course_id)) throw PermissionDenied();
    Professor* targetProfessor = dynamic_cast<Professor*>(this->currentUser);
    TAForm* newTaForm = targetProfessor->addNewTAForm(message , targetCourse);
    this->TAForms.push_back(newTaForm);

}

TAForm* UTMS::getTAFormRequests(int id)
{
    if(this->currentUser == NULL || !this->currentUser->isItTeacher()) throw PermissionDenied();
    Professor* targetProfessor = dynamic_cast<Professor*>(this->currentUser);
    TAForm* targetTAForm = targetProfessor->getTAForm(id);
    this->deleteFromTAForm(targetTAForm);
    targetProfessor->deletePost(targetTAForm->getId());
    return targetTAForm;
}

void UTMS::deleteFromTAForm(TAForm *targetTAForm)
{
    for(int i=0 ; i < this->TAForms.size() ; i++){
        if(TAForms[i]->getId() == targetTAForm->getId()){
			TAForms.erase(TAForms.begin() + i);
            return;           
        }
    }
    throw NotFound();
}

void UTMS::addNewTAReq(int professor_id, int form_id)
{
    if(this->currentUser == NULL || !this->currentUser->isItStudent()) throw PermissionDenied();
    Student* targetStudent = dynamic_cast<Student*>(this->currentUser);
    Professor* targetProfessor = giveProfessorByID(professor_id);
    TAForm* targetForm = targetProfessor->getTAForm(form_id);
    BeingOfferedCourse* wantedCourse = targetForm->getCourse();
    if(targetStudent->getSemester() <= wantedCourse->getPrerequisite()) throw PermissionDenied();   
    targetForm->addNewTaRequest(targetStudent);
}

void UTMS::findTargetUserForShowingInformation(string ID)
{
    if(!isNaturalNumber(ID) || stoll(ID) == 0 || ID == "") throw BadRequest();
    User* targetUser = findUserById(stoll(ID));
    this->targetUserForShowingInformation = targetUser;
}

User *UTMS::getTargetUserForShowingInformation()
{
    return this->targetUserForShowingInformation;
}
