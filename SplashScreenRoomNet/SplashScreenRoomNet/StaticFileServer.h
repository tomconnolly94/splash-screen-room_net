#pragma once

//internal includes
#include "SubPageServer.h"

//forward declarations
class WebServer
{
	struct http_request
	{
		struct http_response;
	};
};

class StaticFileServer : public SubPageServer
{
public:
	static bool ServeImage(std::string requestedImage, WebServer::http_request::http_response &response);
	static bool ServeFile(std::string requestedPage, WebServer::http_request::http_response &response, SubPageServer::CONTENT_TYPE contentType);
	static bool ServeExternalLibFile(std::string requestedPage, WebServer::http_request::http_response &response, SubPageServer::CONTENT_TYPE contentType);
	static std::string CreateHtmlOutputForBinary(const std::string& fullPath);
};