
//external includes
#include <vector>
#include <numeric>

//internal includes
#include "HtmlPageServer.h"
#include "../../cppcommontproj/CppCommonTProj/FileInterface.h"
#include "Properties.h"

HttpResponse* HtmlPageServer::ServeHtmlPage(std::string requestPath)
{
    std::vector<std::string> pageSections;
    Properties::PAGE requestedPage = GetRequestedPage(requestPath);
    std::map<std::string, std::string> templateValues = GetPageTemplateValues(requestedPage);

    //add page sections to vector
    pageSections.push_back(FileInterface::ReadStringFromFile((Properties::directoryMappings[Properties::DIRECTORY::htmlDir] + "header.html").c_str()));
    pageSections.push_back(FileInterface::ReadStringFromFile((Properties::directoryMappings[Properties::DIRECTORY::htmlDir] + pageMappings[requestedPage]).c_str()));
    pageSections.push_back(FileInterface::ReadStringFromFile((Properties::directoryMappings[Properties::DIRECTORY::htmlDir] + "footer.html").c_str()));

    //concatenate page Sections and pass them into the templating engine
    Jinja2CppLight::Template pageTemplate(std::accumulate(pageSections.begin(), pageSections.end(), std::string("")));
    InsertTemplateValues(&pageTemplate, templateValues);

    //assign page response
    return new HttpResponse(200, pageTemplate.render(), Properties::contentTypeMappings[Properties::CONTENT_TYPE::textHtml]);
}

void HtmlPageServer::Configure()
{
    Properties::Configure();
}

void HtmlPageServer::InsertTemplateValues(Jinja2CppLight::Template* jinjaTemplate, std::map<std::string, std::string> values)
{
    for (auto const& value : values)
    {
        jinjaTemplate->setValue(value.first, value.second);
    }
}

Properties::PAGE HtmlPageServer::GetRequestedPage(std::string requestPath)
{
    if (requestPath == "/") 
    {
        return Properties::PAGE::index;
    }
    else
    {
        return Properties::PAGE::error;
    }
}

std::map<std::string, std::string> HtmlPageServer::GetPageTemplateValues(Properties::PAGE page)
{
    std::map<std::string, std::string> templateValues;

    switch (page)
    {
        case Properties::PAGE::index:
            templateValues["avalue"] = "tom";
            break;
    }

    return templateValues;
}