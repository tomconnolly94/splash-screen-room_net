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
    std::string requestPath = r->path_;

    std::map<std::string, std::string> templateValues;
    std::map<PAGE, std::string> pageMappings = { 
        {PAGE::index, "index.html"}, 
        {PAGE::error, "error.html"} 
    };
    std::vector<std::string> pageSections;

    std::vector<std::string> urlSections = Index::InterpretUrlSections(requestPath);

    if (urlSections.size() > 1)
    {
        std::string urlSection1 = urlSections[0];

        if (urlSection1 == "images")
        {
            //std::string encoded_png;
            //Mat img; // Load an image here

            //std::vector<std::uchar> buf;
            //cv::imencode(".png", img, buf);
            //auto base64_png = reinterpret_cast<const unsigned char*>(buf.data());
            //encoded_png = "data:image/jpeg;base64," + std::base64_encode(base64_png, buf.size());
            r->answer_ = FileInterface::ReadStringFromFile("image.txt");
            r->content_type_ = "image/jpeg";
            
            return;
        }
        else if (urlSection1 == "css")
        {

        }
        else if (urlSection1 == "js")
        {

        }
    }
    else {
        if (r->path_ == "/") 
        {
            requestedPage = PAGE::index;
            templateValues["avalue"] = "tom";
        }
        else 
        {
            requestedPage = PAGE::error;
        }
    }


    //add page sections to vector
    std::string htmlDir = "web/html/";
    pageSections.push_back(FileInterface::ReadStringFromFile((htmlDir + "header.html").c_str()));
    pageSections.push_back(FileInterface::ReadStringFromFile((htmlDir + pageMappings[requestedPage]).c_str()));
    pageSections.push_back(FileInterface::ReadStringFromFile((htmlDir + "footer.html").c_str()));

    //concatenate page Sections and pass them into the templating engine
    Jinja2CppLight::Template pageTemplate(std::accumulate(pageSections.begin(), pageSections.end(), std::string("")));
    Index::InsertTemplateValues(&pageTemplate, templateValues);
    
    //assign page response
    r->answer_ = pageTemplate.render();;
}

std::vector<std::string> Index::InterpretUrlSections(std::string urlPath)
{
    //access sections of request path
    std::string delimiter = "/";
    std::vector<std::string> sectionsOfUrl;

    size_t pos = 0;
    std::string urlSection;
    while ((pos = urlPath.find(delimiter)) != std::string::npos) {
        urlSection = urlPath.substr(0, pos);
        if(urlSection != "") sectionsOfUrl.push_back(urlSection);
        urlPath.erase(0, pos + delimiter.length());
    }

    if (urlSection != "") sectionsOfUrl.push_back(urlPath);

    return sectionsOfUrl;
}

void Index::InsertTemplateValues(Jinja2CppLight::Template* jinjaTemplate, std::map<std::string, std::string> values)
{
    for (auto const& value : values) 
    {
        jinjaTemplate->setValue(value.first, value.second);
    }
}