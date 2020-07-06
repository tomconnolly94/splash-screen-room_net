#pragma once
#include "../../cppwebserver/CppWebServer/CppWebServer/HttpRequest.h"

//forward declarations
class Index {
public:
	static void HandleRequest(CppWebServer::http_request* r);
	static void ConfigureServer();
};
