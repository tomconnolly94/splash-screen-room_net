#pragma once

//external includes
#include <string>
#include <map>

//internal includes
#include "SubPageServer.h"

//forward declarations
namespace Jinja2CppLight 
{
	class Template;
}

namespace WebServer
{
	namespace http_request
	{
		class http_response;
	}
}

class HtmlPageServer : public SubPageServer
{
public:
	//functions
	static void ServeHtmlPage(std::string requestPath, WebServer::http_request::http_response& http_response);
	static void Configure();
private:
	//properties
	static std::string htmlDir;
	static std::map<PAGE, std::string> pageMappings;
	static void InsertTemplateValues(Jinja2CppLight::Template* jinjaTemplate, std::map<std::string, std::string> values);
	static PAGE GetRequestedPage(std::string requestPath);
	static std::map<std::string, std::string> GetPageTemplateValues(HtmlPageServer::PAGE);
};
