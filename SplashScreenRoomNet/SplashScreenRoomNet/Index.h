#pragma once
#include "../../cppwebserver/CppWebServer/CppWebServer/WebServer.h"
#include "../../Jinja2CppLight/src/Jinja2CppLight.h"


class Index {
public:
	static void HandleRequest(WebServer::http_request* r);
private:
	static void InsertTemplateValues(Jinja2CppLight::Template* jinjaTemplate, std::map<std::string, std::string> values);
	enum class PAGE {
		index,
		error
	};
	static std::vector<std::string> InterpretUrlSections(std::string urlPath);
	static void FileNotFoundError(WebServer::http_request* r);
	static bool FileExists(WebServer::http_request* httpReq, std::string fileWithPath);
	static std::string CreateHtmlOutputForBinary(const std::string& fullPath);
};