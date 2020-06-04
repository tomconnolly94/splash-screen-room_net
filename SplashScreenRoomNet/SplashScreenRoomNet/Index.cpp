//external includes
#include <numeric>

//internal includes
#include "Index.h"
#include "../../cppcommontproj/CppCommonTProj/FileInterface.h"

//forward declarations
class Socket {};

void Index::HandleRequest(WebServer::http_request* r)
{
    Socket s = *(r->s_);
    PAGE requestedPage;
    std::map<std::string, std::string> templateValues;
    std::map<PAGE, std::string> pageMappings = { 
        {PAGE::index, "index.html"}, 
        {PAGE::error, "error.html"} 
    };
    std::vector<std::string> pageSections;

    if (r->path_ == "/") 
    {
        requestedPage = PAGE::index;
        templateValues["avalue"] = "tom";
    }
    else 
    {
        requestedPage = PAGE::error;
    }

    //add page sections to vector
    pageSections.push_back(FileInterface::ReadStringFromFile("html/header.html"));
    pageSections.push_back(FileInterface::ReadStringFromFile(("html/" + pageMappings[requestedPage]).c_str()));
    pageSections.push_back(FileInterface::ReadStringFromFile("html/footer.html"));

    //concatenate page Sections and pass them into the templating engine
    Jinja2CppLight::Template pageTemplate(std::accumulate(pageSections.begin(), pageSections.end(), std::string("")));
    Index::InsertTemplateValues(&pageTemplate, templateValues);
    
    //assign page response
    r->answer_ = pageTemplate.render();;
}

void Index::InsertTemplateValues(Jinja2CppLight::Template* jinjaTemplate, std::map<std::string, std::string> values)
{
    for (auto const& value : values) 
    {
        jinjaTemplate->setValue(value.first, value.second);
    }
}