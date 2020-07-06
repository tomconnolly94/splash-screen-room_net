
//internal includes
#include "PageServer.h"
#include "HTMLPageServer.h"
#include "Properties.h"
#include "StaticFileServer.h"

HttpResponse* PageServer::ServePage(std::string requestPath) 
{
	std::vector<std::string> urlSections = InterpretUrlSections(requestPath);

    if (urlSections.size() > 1)
    {
        std::string urlSection1 = urlSections[0];

        if (urlSection1 == "images")
        {
            return StaticFileServer::ServeImage(urlSections[0]);
        }
        else if (urlSection1 == "css")
        {
            return StaticFileServer::ServeFile(urlSections[0], Properties::CONTENT_TYPE::textCss);
        }
        else if (urlSection1 == "js")
        {
            return StaticFileServer::ServeFile(urlSections[0], Properties::CONTENT_TYPE::appJs);
        }
        else if (urlSection1 == "node-modules")
        {
            return StaticFileServer::ServeExternalLibFile(urlSections[0], Properties::CONTENT_TYPE::appJs);
        }
    }
    else {
        //only accept requests to "/"
        if (requestPath == "/")
        {
            return HtmlPageServer::ServeHtmlPage(requestPath);
        }
        else if (std::find(specialPaths.begin(), specialPaths.end(), "abc") != specialPaths.end())
        {
            return StaticFileServer::ServeImage(requestPath);
        }
    }
    return new HttpResponse{};
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
