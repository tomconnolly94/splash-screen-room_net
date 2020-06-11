
//internal includes
#include "PageServer.h"
#include "HtmlPageServer.h"
#include "../../cppwebserver/CppWebServer/CppWebServer/WebServer.h"


void PageServer::ServePage(std::string requestPath, WebServer::http_request::http_response& httpResponse) 
{


	std::vector<std::string> urlSections = InterpretUrlSections(requestPath);



    if (urlSections.size() > 1)
    {
        std::string urlSection1 = urlSections[0];

        if (urlSection1 == "images")
        {
            if (!FileExists(httpRequest, imagesDir + urlSections[1]))
            {
                return;
            }
            httpRequest->response_.text_ = CreateHtmlOutputForBinary((imagesDir + urlSections[1]).c_str());
            httpRequest->response_.content_type_ = "image/png";

            return;
        }
        else if (urlSection1 == "css")
        {
            if (!FileExists(httpRequest, cssDir + urlSections[1]))
            {
                return;
            }
            std::string cssFileContent = FileInterface::ReadStringFromFile((cssDir + urlSections[1]).c_str());
            httpRequest->response_.text_ = cssFileContent;
            httpRequest->response_.content_type_ = "text/css";
            return;
        }
        else if (urlSection1 == "js")
        {
            if (!FileExists(httpRequest, jsDir + urlSections[1]))
            {
                return;
            }
            std::string jsFileContent = FileInterface::ReadStringFromFile((jsDir + urlSections[1]).c_str());
            httpRequest->response_.text_ = jsFileContent;
            httpRequest->response_.content_type_ = "application/javascript";
            return;
        }
        else if (urlSection1 == "node-modules")
        {
            std::string file = urlSections[1];
            std::string fileExtension = SplashScreenRoomNetUtil::GetExtension(file);
            std::string fileNameWithoutExtension = file.substr(0, file.size() - fileExtension.size() - 1);
            std::string targetDir = nodeModulesDir + fileNameWithoutExtension + "/dist/" + fileExtension + "/";
            std::string fileLocation = targetDir + fileNameWithoutExtension;

            if (!FileExists(httpRequest, targetDir + file))
            {
                return;
            }

            std::string fileContent = FileInterface::ReadStringFromFile((fileLocation + "." + fileExtension).c_str());
            httpRequest->response_.text_ = fileContent;

            if (fileExtension == "js")
            {
                httpRequest->response_.content_type_ = "application/javascript";
                return;
            }
            else if (fileExtension == "css")
            {
                httpRequest->response_.content_type_ = "text/css";
                return;
            }
            else {
                FileNotFoundError(httpRequest);
                return;
            }
        }
        else
        {
            FileNotFoundError(httpRequest);
            return;
        }
    }
    else {
        //only accept requests to "/"
        if (requestPath == "/")
        {
            requestedPage = PAGE::index;

            HtmlPageServer::serveHtmlPage(requestPath, *);
        }
        else if (httpRequest->path_ == "/favicon.ico")
        {
            if (!FileExists(httpRequest, imagesDir + "favicon.ico"))
            {
                return;
            }
            httpRequest->response_.text_ = CreateHtmlOutputForBinary((imagesDir + "/favicon.ico").c_str());
            httpRequest->response_.content_type_ = "image/x-icon";

            return;
        }
        else
        {
            requestedPage = PAGE::error;
        }

}

std::vector<std::string> PageServer::InterpretUrlSections(std::string urlPath)
{
    //access sections of request path
    std::string delimiter = "/";
    std::vector<std::string> sectionsOfUrl;

    size_t pos = 0;
    std::string urlSection;
    while ((pos = urlPath.find(delimiter)) != std::string::npos) {
        urlSection = urlPath.substr(0, pos);
        if (urlSection != "") sectionsOfUrl.push_back(urlSection);
        urlPath.erase(0, pos + delimiter.length());
    }

    if (urlSection != "") sectionsOfUrl.push_back(urlPath);

    return sectionsOfUrl;
}