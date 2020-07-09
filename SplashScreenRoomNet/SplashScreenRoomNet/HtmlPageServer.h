#pragma once

//external includes
#include <string>
#include <map>
#include "../../Jinja2CppLight/src/Jinja2CppLight.h"

//internal includes
#include "Properties.h"
#include "HttpResponse.h"

class HtmlPageServer
{
public:
	//functions
	static HttpResponse* ServeHtmlPage(std::string requestPath);
	//properties
private:
	//functions
	static Properties::PAGE GetRequestedPage(std::string requestPath);
	static std::map<std::string, std::string> GetPageTemplateValues(Properties::PAGE);
	//properties
	static std::map<Properties::PAGE, std::string> pageMappings;
	static std::string htmlDir;
	static void InsertTemplateValues(Jinja2CppLight::Template* jinjaTemplate, std::map<std::string, std::string> values);
};