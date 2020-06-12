//external includes

//internal includes
#include "Index.h"
#include "PageServer.h"
#include "HtmlPageServer.h"
#include "../../cppwebserver/CppWebServer/CppWebServer/WebServer.h"
#include "../../Jinja2CppLight/src/Jinja2CppLight.h"

//forward declarations
class Socket {};

void Index::ConfigureServer()
{
    PageServer::Configure();
    HtmlPageServer::Configure();
}

void Index::HandleRequest(WebServer::http_request* httpRequest)
{
    Socket s = *(httpRequest->s_);
    std::string requestPath = httpRequest->path_;

    bool responseSuccess = PageServer::ServePage(requestPath, httpRequest->response_);

    if (!responseSuccess)
    {
        httpRequest->status_ = "404 Not Found";
    }
}

void Index::FileNotFoundError(WebServer::http_request* httpReq)
{
    httpReq->status_ = "404 Not Found";
}