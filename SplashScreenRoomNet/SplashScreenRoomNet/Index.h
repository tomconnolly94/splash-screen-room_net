#pragma once
#include "../../cppwebserver/CppWebServer/CppWebServer/WebServer.h"
#include "../../Jinja2CppLight/src/Jinja2CppLight.h"

//forward declarations
namespace WebServer
{
	class http_request
	{
		class http_response;
	};
}


class Index {
public:
	static void HandleRequest(WebServer::http_request* r);
	static void ConfigureServer();
private:
	static void FileNotFoundError(WebServer::http_request* r);
	static std::string CreateHtmlOutputForBinary(const std::string& fullPath);
};