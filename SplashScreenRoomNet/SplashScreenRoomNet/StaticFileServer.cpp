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

HttpResponse* StaticFileServer::ServeExternalLibFile(std::string requestedFile, Properties::CONTENT_TYPE contentType)
{
    std::string fullFileWithPath = FindExistingFile(requestedFile);

    if (fullFileWithPath == "")
    {
        return new HttpResponse(404, "Requested file does not exist.", Properties::contentTypeMappings[Properties::CONTENT_TYPE::plaintext]);
    }

    HttpResponse* httpResponse = new HttpResponse();
    httpResponse->SetContent(FileInterface::ReadStringFromFile(fullFileWithPath.c_str()));
    httpResponse->SetStatusCode(200);
    std::string fileExtension = SplashScreenRoomNetUtil::GetExtension(requestedFile);

    if (fileExtension == "js")
    {
        httpResponse->SetContentType(Properties::CONTENT_TYPE::appJs);
    }
    else if (fileExtension == "css")
    {
        httpResponse->SetContentType(Properties::CONTENT_TYPE::textCss);
    }
    else if (fileExtension == "map")
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

std::string StaticFileServer::FindExistingFile(std::string requestedFile)
{
    std::string fileExtension = SplashScreenRoomNetUtil::GetExtension(requestedFile, false);
    std::vector<std::string> possibleSubDirs = { "", "/js", "/css" };
    std::vector<std::string> possibleTargetDirs;
    std::string fileNameWithoutExtension = requestedFile.substr(0, requestedFile.size() - fileExtension.size() - 1);

    for (std::string subDir : possibleSubDirs)
    {
        possibleTargetDirs.push_back(Properties::directoryMappings[Properties::DIRECTORY::nodeModulesDir] + fileNameWithoutExtension + "/dist" + subDir + "/");
    }

    std::string fullFileWithPath;

    for (std::string targetDir : possibleTargetDirs)
    {
        std::string possibleFileLocation = targetDir + requestedFile;
        if (SplashScreenRoomNetUtil::FileExists(possibleFileLocation))
        {
            return possibleFileLocation;
        }
    }
    return "";
}