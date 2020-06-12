#pragma once

//internal includes
#include "SubPageServer.h"

class StaticFileServer : public SubPageServer
{
public:
	static bool ServeImage(std::string requestedPage, WebServer::http_request::http_response& http_response);
	static bool ServeFile(std::string requestedPage, WebServer::http_request::http_response& http_response, SubPageServer::CONTENT_TYPE contentType);
	static bool ServeExternaLibFile(std::string requestedPage, WebServer::http_request::http_response& response, SubPageServer::CONTENT_TYPE contentType);
	static std::string CreateHtmlOutputForBinary(const std::string& fullPath);
};