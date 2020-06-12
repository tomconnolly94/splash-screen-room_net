
//external includes
#include <vector>
#include <numeric>

//internal includes
#include "HtmlPageServer.h"
#include "../../cppcommontproj/CppCommonTProj/FileInterface.h"
#include "../../Jinja2CppLight/src/Jinja2CppLight.h"
#include "../../cppwebserver/CppWebServer/CppWebServer/WebServer.h"

void HtmlPageServer::ServeHtmlPage(std::string requestPath, WebServer::http_request::http_response& http_response)
{
    std::vector<std::string> pageSections;
    PAGE requestedPage = GetRequestedPage(requestPath);
    std::map<std::string, std::string> templateValues = GetPageTemplateValues(requestedPage);

    //add page sections to vector
    pageSections.push_back(FileInterface::ReadStringFromFile((directoryMappings[DIRECTORY::htmlDir] + "header.html").c_str()));
    pageSections.push_back(FileInterface::ReadStringFromFile((directoryMappings[DIRECTORY::htmlDir] + pageMappings[requestedPage]).c_str()));
    pageSections.push_back(FileInterface::ReadStringFromFile((directoryMappings[DIRECTORY::htmlDir] + "footer.html").c_str()));

    //concatenate page Sections and pass them into the templating engine
    Jinja2CppLight::Template pageTemplate(std::accumulate(pageSections.begin(), pageSections.end(), std::string("")));
    InsertTemplateValues(&pageTemplate, templateValues);

    //assign page response
    http_response.text_ = pageTemplate.render();
    http_response.content_type_ = contentTypeMappings[CONTENT_TYPE::textHtml];
    return;
}

void HtmlPageServer::Configure()
{
    ConfigureShared();
    HtmlPageServer::pageMappings = {
        {HtmlPageServer::PAGE::index, "index.html"},
        {HtmlPageServer::PAGE::error, "error.html"}
    };
}

void HtmlPageServer::InsertTemplateValues(Jinja2CppLight::Template* jinjaTemplate, std::map<std::string, std::string> values)
{
    for (auto const& value : values)
    {
        jinjaTemplate->setValue(value.first, value.second);
    }
}

HtmlPageServer::PAGE HtmlPageServer::GetRequestedPage(std::string requestPath)
{
    if (requestPath == "/") 
    {
        return HtmlPageServer::PAGE::index;
    }
    else
    {
        return HtmlPageServer::PAGE::error;
    }
}

std::map<std::string, std::string> HtmlPageServer::GetPageTemplateValues(HtmlPageServer::PAGE page)
{
    std::map<std::string, std::string> templateValues;

    switch (page)
    {
        case HtmlPageServer::PAGE::index:
            templateValues["avalue"] = "tom";
            break;
    }

    return templateValues;
}