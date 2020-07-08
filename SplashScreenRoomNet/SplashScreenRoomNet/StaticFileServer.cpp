
//external includes
#include <sstream>

//internal includes
#include "StaticFileServer.h"
#include "SplashScreenRoomNetUtil.h"
#include "../../cppcommontproj/CppCommonTProj/FileInterface.h"

HttpResponse* StaticFileServer::ServeImage(std::string requestedImage)
{
    std::string targetFile = Properties::directoryMappings[Properties::DIRECTORY::imagesDir] + requestedImage;

    Properties::CONTENT_TYPE contentType = Properties::extensionContentTypeMappings[SplashScreenRoomNetUtil::GetExtension(requestedImage)];

    if (!SplashScreenRoomNetUtil::FileExists(targetFile))
    {
        return new HttpResponse(500, "Requested file does not exist.", Properties::contentTypeMappings[Properties::CONTENT_TYPE::plaintext]);
    }

    return new HttpResponse(202, CreateHtmlOutputForBinary(targetFile.c_str()), Properties::contentTypeMappings[contentType]);
}

HttpResponse* StaticFileServer::ServeFile(std::string requestedPage, Properties::CONTENT_TYPE contentType)
{
    Properties::DIRECTORY targetDir = Properties::contentTypeDirectoryMappings[contentType];
    std::string targetFile = Properties::directoryMappings[targetDir] + requestedPage;

    if (!SplashScreenRoomNetUtil::FileExists(targetFile))
    {
        return new HttpResponse(500, "Requested file does not exist.", Properties::contentTypeMappings[Properties::CONTENT_TYPE::plaintext]);
    }

    return new HttpResponse(202, CreateHtmlOutputForBinary(targetFile.c_str()), Properties::contentTypeMappings[contentType]);
}

HttpResponse* StaticFileServer::ServeExternalLibFile(std::string requestedPage, Properties::CONTENT_TYPE contentType)
{
    std::string fileExtension = SplashScreenRoomNetUtil::GetExtension(requestedPage);
    std::string fileNameWithoutExtension = requestedPage.substr(0, requestedPage.size() - fileExtension.size() - 1);
    std::vector<std::string> possibleTargetDirs;
    possibleTargetDirs.push_back(Properties::directoryMappings[Properties::DIRECTORY::nodeModulesDir] + fileNameWithoutExtension + "/dist/" + fileExtension + "/");
    possibleTargetDirs.push_back(Properties::directoryMappings[Properties::DIRECTORY::nodeModulesDir] + fileNameWithoutExtension + "/dist/");


    std::string fullFileWithPath;
    bool fileFound = false;

    for (std::string targetDir : possibleTargetDirs)
    {
        if (SplashScreenRoomNetUtil::FileExists(targetDir + requestedPage))
        {
            fileFound = true;
            fullFileWithPath = targetDir + fileNameWithoutExtension + "." + fileExtension;
        }
    }

    if (!fileFound)
    {
        return new HttpResponse(404, "Requested file does not exist.", Properties::contentTypeMappings[Properties::CONTENT_TYPE::plaintext]);
    }

    HttpResponse* httpResponse = new HttpResponse();

    httpResponse->SetContent(FileInterface::ReadStringFromFile(fullFileWithPath.c_str()));
    httpResponse->SetStatusCode(200);

    if (fileExtension == "js")
    {
        httpResponse->SetContentType(Properties::CONTENT_TYPE::appJs);
    }
    else if (fileExtension == "css")
    {
        httpResponse->SetContentType(Properties::CONTENT_TYPE::textCss);
    }
    else {
        httpResponse->SetError();
    }
    return httpResponse;
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