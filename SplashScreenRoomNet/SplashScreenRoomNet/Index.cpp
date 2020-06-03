//internal includes
#include "Index.h"

//forward declarations
class Socket {};

void Index::HandleRequest(WebServer::http_request* r)
{
    Socket s = *(r->s_);

    std::string title;
    std::string body;
    std::string bgcolor = "#ffffff";

    if (r->path_ == "/") {
        title = "Web Server Example";
        body = "<h1>Welcome to the base Web Server</h1>"
            "<p>This is the defaut main function, please extend this server with a client application</p>";
    }
    else {
        r->status_ = "404 Not Found";
        title = "Wrong URL";
        body = "<h1>Wrong URL</h1>";
        body += "Path is : &gt;" + r->path_ + "&lt;";
    }

    r->answer_ = "<html><head><title>";
    r->answer_ += title;
    r->answer_ += "</title></head><body bgcolor='" + bgcolor + "'>";
    r->answer_ += body;
    r->answer_ += "</body></html>";
}