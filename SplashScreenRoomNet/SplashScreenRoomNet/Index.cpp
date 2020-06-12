//external includes
#include <numeric>
#include <iostream>
#include <sstream>
#include <iterator>
#include <numeric>

//internal includes
#include "Index.h"
#include "../../cppcommontproj/CppCommonTProj/FileInterface.h"
#include "SplashScreenRoomNetUtil.h"
#include "PageServer.h"
#include "HtmlPageServer.h"
#include "../../cppwebserver/CppWebServer/CppWebServer/WebServer.h"

//forward declarations
class Socket {};

void Index::ConfigureServer()
{
    //PageServer::Configure();
    HtmlPageServer::Configure();
}

void Index::HandleRequest(WebServer::http_request* httpRequest)
{
    Socket s = *(httpRequest->s_);
    //PAGE requestedPage;
    std::string requestPath = httpRequest->path_;

    PageServer::ServePage(requestPath, httpRequest->response_);
}

void Index::FileNotFoundError(WebServer::http_request* httpReq)
{
    httpReq->status_ = "404 Not Found";
}

//bool Index::FileExists(WebServer::http_request* httpReq, std::string fileWithPath)
//{
//    if (!SplashScreenRoomNetUtil::FileExists(fileWithPath))
//    {
//        FileNotFoundError(httpReq);
//        return false;
//    }
//    return true;
//}
