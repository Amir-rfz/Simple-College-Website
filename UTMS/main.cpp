#include "UTMS.hpp"

#include "../server/server.hpp"
#include "handlers.hpp"

using namespace std;

void mapServerPaths(UTMS* utms, Server& server) {
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/logincss.html"));
    server.post("/", new LoginHandler(utms));
    server.get("/permissionDenied", new ShowPage("static/permissionDenied.html"));
    server.get("/notFound", new ShowPage("static/notFound.html"));
    server.get("/badRequest", new ShowPage("static/badRequest.html"));
    server.get("/Home", new HomeHandler(utms));
    server.get("/defaultPic.png", new ShowImage("static/defaultPic.png"));
    server.get("/AddPost", new ShowPage("static/addPost.html"));
    server.post("/AddPost", new addPostHandler(utms));
    server.get("/changeProfile", new ShowPage("static/changeProfile.html"));
    server.post("/changeProfile", new changeProfileHandler(utms));
    server.post("/deleteProfile", new deleteProfileHandler(utms));
    server.get("/showAllCourses", new showAllCoursesHandler(utms));
    server.get("/getPage", new ShowPage("static/getPage.html"));
    server.post("/getPage", new getPageHandler(utms));
    server.get("/showPage", new showPageHandler(utms));
    server.get("/getNewCourse", new ShowPage("static/getNewCourse.html"));
    server.post("/getNewCourse", new getNewCourseHandler(utms));
    server.get("/deleteCourse", new ShowPage("static/deleteCourse.html"));
    server.post("/deleteCourse", new deleteCourseHandler(utms));
    server.get("/showCourses", new showCoursesHandler(utms));
    server.get("/addOfferedCourse", new ShowPage("static/addOfferedCourse.html"));
    server.post("/addOfferedCourse", new addOfferedCourseHandler(utms));
    server.get("/logout", new LogoutHandler(utms));
    server.get("/upload/*", new ImageHandler());
}

int main(int argc, char *argv[])
{
    UTMS* utms = new UTMS(argv[1], argv[2], argv[3], argv[4]);
    try {
        int port = argc > 5 ? std::stoi(argv[5]) : 5000;
        Server server(port);
        mapServerPaths(utms, server);
        std::cout << "Server running on port: " << port << std::endl;
        server.run();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const Server::Exception& e) {
        std::cerr << e.getMessage() << std::endl;
    }
    return 0;
}
