
//internal includes
#include "StaticFileServer.h"
#include "SplashScreenRoomNetUtil.h"
#include "../../cppwebserver/CppWebServer/CppWebServer/WebServer.h"
#include "../../cppcommontproj/CppCommonTProj/FileInterface.h"

bool StaticFileServer::ServeImage(std::string requestedPage, WebServer::http_request::http_response& response)
{
    std::string targetFile = directoryMappings[DIRECTORY::imagesDir] + requestedPage;

    if (!SplashScreenRoomNetUtil::FileExists(targetFile))
    {
        return false;
    }
    response.text_ = CreateHtmlOutputForBinary(targetFile.c_str());
    response.content_type_ = "image/png";

    return true;
}


bool StaticFileServer::ServeFile(std::string requestedPage, WebServer::http_request::http_response& response, SubPageServer::CONTENT_TYPE contentType)
{
    DIRECTORY targetDir = contentTypeDirectoryMappings[contentType];
    std::string targetFile = directoryMappings[targetDir] + requestedPage;

    if (!SplashScreenRoomNetUtil::FileExists(targetFile))
    {
        return false;
    }
    response.text_ = FileInterface::ReadStringFromFile(targetFile.c_str());
    response.content_type_ = "image/png";

    return true;
}



bool StaticFileServer::ServeExternaLibFile(std::string requestedPage, WebServer::http_request::http_response& response, SubPageServer::CONTENT_TYPE contentType)
{
    std::string fileExtension = SplashScreenRoomNetUtil::GetExtension(requestedPage);
    std::string fileNameWithoutExtension = requestedPage.substr(0, requestedPage.size() - fileExtension.size() - 1);
    std::string targetDir = directoryMappings[DIRECTORY::nodeModulesDir] + fileNameWithoutExtension + "/dist/" + fileExtension + "/";
    std::string fileLocation = targetDir + fileNameWithoutExtension;

    if (!SplashScreenRoomNetUtil::FileExists(targetDir + requestedPage))
    {
        return false;
    }

    std::string fileContent = FileInterface::ReadStringFromFile((fileLocation + "." + fileExtension).c_str());
    response.text_ = fileContent;

    if (fileExtension == "js")
    {
        response.content_type_ = "application/javascript";
        return;
    }
    else if (fileExtension == "css")
    {
        response.content_type_ = "text/css";
        return;
    }
    else {
        //FileNotFoundError(httpRequest);
        return false;
    }
}

std::string StaticFileServer::CreateHtmlOutputForBinary(const std::string& fullPath)
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