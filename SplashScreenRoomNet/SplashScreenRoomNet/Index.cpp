//external includes
#include <numeric>
#include <iostream>
#include <sstream>
#include <iterator>
#include <numeric>

//internal includes
#include "Index.h"
#include "../../cppcommontproj/CppCommonTProj/FileInterface.h"
#include "SplashScreenRoomNetUtil.h"

//forward declarations
class Socket {};

void Index::HandleRequest(WebServer::http_request* r)
{
    Socket s = *(r->s_);
    PAGE requestedPage;
    std::string requestPath = r->path_;
    std::string htmlDir = "web/html/";
    std::string cssDir = "web/css/";
    std::string jsDir = "web/js/";
    std::string imagesDir = "web/images/";

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
            r->response_.text_ = CreateHtmlOutputForBinary( imagesDir + "weeknd.png");
            r->response_.content_type_ = "image/png";
            
            return;
        }
        else if (urlSection1 == "css")
        {
            if (!FileExists(r, cssDir + urlSections[1]))
            {
                return;
            }
            std::string cssFileContent = FileInterface::ReadStringFromFile((cssDir + urlSections[1]).c_str());
            r->response_.text_ = cssFileContent;
            r->response_.content_type_ = "text/css";
            return;
        }
        else if (urlSection1 == "js")
        {
            if (!FileExists(r, jsDir + urlSections[1]))
            {
                return;
            }
            std::string jsFileContent = FileInterface::ReadStringFromFile((jsDir + urlSections[1]).c_str());
            r->response_.text_ = jsFileContent;
            r->response_.content_type_ = "application/javascript";
            return;
        }
    }
    else {
        //only accept requests to "/"
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
        pageSections.push_back(FileInterface::ReadStringFromFile((htmlDir + "header.html").c_str()));
        pageSections.push_back(FileInterface::ReadStringFromFile((htmlDir + pageMappings[requestedPage]).c_str()));
        pageSections.push_back(FileInterface::ReadStringFromFile((htmlDir + "footer.html").c_str()));

        //concatenate page Sections and pass them into the templating engine
        Jinja2CppLight::Template pageTemplate(std::accumulate(pageSections.begin(), pageSections.end(), std::string("")));
        Index::InsertTemplateValues(&pageTemplate, templateValues);

        //assign page response
        r->response_.text_ = pageTemplate.render();
        r->response_.content_type_ = "text/html";
        return;
    }
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

void Index::FileNotFoundError(WebServer::http_request* httpReq)
{
    httpReq->status_ = "404 Not Found";
}

bool Index::FileExists(WebServer::http_request* httpReq, std::string fileWithPath)
{
    if (!SplashScreenRoomNetUtil::FileExists(fileWithPath))
    {
        FileNotFoundError(httpReq);
        return false;
    }
    return true;
}

std::string Index::CreateHtmlOutputForBinary(const std::string& fullPath)
{
    const char* file_name = fullPath.c_str();

    FILE* file_stream = fopen(file_name, "rb");

    std::string file_str;

    size_t file_size;


    if (file_stream != nullptr)
    {
        std::vector<char> buffer;

        //... other code here

        if (file_stream != nullptr)
        {
            fseek(file_stream, 0, SEEK_END);
            long file_length = ftell(file_stream);
            rewind(file_stream);

            buffer.resize(file_length);

            file_size = fread(&buffer[0], 1, file_length, file_stream);

            const char* s;
            std::string delimiter = "";
            copy(buffer.begin(), buffer.end(), std::ostream_iterator<int>(s, delimiter.c_str()));
            return s;
        }
    }
    else
    {
        printf("file_stream is null! file name -> %s\n", file_name);
    }
    return ""; //html;
}