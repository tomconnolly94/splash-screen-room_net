#pragma once
#include "../../cppwebserver/CppWebServer/CppWebServer/WebServer.h"

class Index {
public:
	static void HandleRequest(WebServer::http_request* r);
};