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
    PAGE requestedPage;
    std::string requestPath = httpRequest->path_;
    std::string htmlDir = "web/html/";
    std::string cssDir = "web/css/";
    std::string jsDir = "web/js/";
    std::string imagesDir = "web/images/";
    std::string nodeModulesDir = "web/node_modules/";

    PageServer::ServePage(requestPath, httpRequest->http_response);




}

void Index::FileNotFoundError(WebServer::http_request* httpReq)
{
    httpReq->status_ = "404 Not Found";
}

bool Index::FileExists(WebServer::http_request* httpReq, std::string fileWithPath)
{
    if (!SplashScreenRoomNetUtil::FileExists(fileWithPath))
    {
        FileNotFoundError(httpReq);
        return false;
    }
    return true;
}

std::string Index::CreateHtmlOutputForBinary(const std::string& fullPath)
{
    const char* file_name = fullPath.c_str();

    FILE* file_stream = fopen(file_name, "rb");

    std::string file_str;

    size_t file_size;


    if (file_stream != nullptr)
    {
        std::vector<char> buffer;
        fseek(file_stream, 0, SEEK_END);
        long file_length = ftell(file_stream);
        rewind(file_stream);

        buffer.resize(file_length);

        file_size = fread(&buffer[0], 1, file_length, file_stream);
            
        std::stringstream ss;
        for (size_t i = 0; i < buffer.size(); ++i)
        {
            ss << buffer[i];
        }
        std::string s = ss.str();
        return s;
    }
    else
    {
        printf("file_stream is null! file name -> %s\n", file_name);
    }
    return ""; //html;
}