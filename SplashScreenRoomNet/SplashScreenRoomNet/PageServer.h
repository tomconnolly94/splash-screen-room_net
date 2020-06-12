#pragma once
//external includes
#include <string>
#include <vector>

#include "../../cppwebserver/CppWebServer/CppWebServer/WebServer.h"

//forward declarations
class WebServer
{
	struct http_request
	{
		struct http_response;
	};
};

class PageServer {
public:
	//functions
	static bool ServePage(std::string requestPath, WebServer::http_request::http_response &httpResponse);
	static std::vector<std::string> InterpretUrlSections(std::string urlPath);
	static void Configure();
	//properties
	static std::vector<std::string> specialPaths;
};