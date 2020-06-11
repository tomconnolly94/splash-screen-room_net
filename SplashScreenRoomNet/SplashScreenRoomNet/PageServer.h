#pragma once
//external includes
#include <string>
#include <vector>

namespace WebServer
{
	namespace http_request
	{
		class http_response;
	}
}

class PageServer {
public:
	static void ServePage(std::string requestPath, WebServer::http_request::http_response& httpResponse);
	static std::vector<std::string> InterpretUrlSections(std::string urlPath, WebServer::http_request::http_response& httpResponse);
};