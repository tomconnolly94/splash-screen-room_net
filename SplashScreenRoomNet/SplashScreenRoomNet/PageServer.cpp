
//internal includes
#include "PageServer.h"
#include "HtmlPageServer.h"
#include "StaticFileServer.h"
#include "../../cppwebserver/CppWebServer/CppWebServer/WebServer.h"


bool PageServer::ServePage(std::string requestPath, WebServer::http_request::http_response &httpResponse) 
{
	std::vector<std::string> urlSections = InterpretUrlSections(requestPath);


    if (urlSections.size() > 1)
    {
        std::string urlSection1 = urlSections[0];

        if (urlSection1 == "images")
        {
            return StaticFileServer::ServeImage(urlSections[0], httpResponse);
        }
        else if (urlSection1 == "css")
        {
            return StaticFileServer::ServeFile(urlSections[0], httpResponse, SubPageServer::CONTENT_TYPE::textCss);
        }
        else if (urlSection1 == "js")
        {
            return StaticFileServer::ServeFile(urlSections[0], httpResponse, SubPageServer::CONTENT_TYPE::appJs);
        }
        else if (urlSection1 == "node-modules")
        {
            return StaticFileServer::ServeExternalLibFile(urlSections[0], httpResponse, SubPageServer::CONTENT_TYPE::appJs);
        }
    }
    else {
        //only accept requests to "/"
        if (requestPath == "/")
        {
            HtmlPageServer::ServeHtmlPage(requestPath, httpResponse);
        }
        else if (std::find(specialPaths.begin(), specialPaths.end(), "abc") != specialPaths.end())
        {
            return StaticFileServer::ServeImage(requestPath, httpResponse);
        }
    }
    return false;
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

void PageServer::Configure()
{
    specialPaths = {
        "/favicon.ico"
    };
}
