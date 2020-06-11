#pragma once
#include "../../cppwebserver/CppWebServer/CppWebServer/WebServer.h"
#include "../../Jinja2CppLight/src/Jinja2CppLight.h"

//forward declarations
namespace WebServer
{
	class http_request
	{
		class http_response;
	}
}


class Index {
public:
	static void HandleRequest(WebServer::http_request* r);
private:
	static void InsertTemplateValues(Jinja2CppLight::Template* jinjaTemplate, std::map<std::string, std::string> values);
	static std::vector<std::string> InterpretUrlSections(std::string urlPath);
	static void FileNotFoundError(WebServer::http_request* r);
	static bool FileExists(WebServer::http_request* httpReq, std::string fileWithPath);
	static std::string CreateHtmlOutputForBinary(const std::string& fullPath);
	static void ConfigureServer();
};