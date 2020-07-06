#pragma once

//internal includes
#include "Properties.h"
#include "HttpResponse.h"

class StaticFileServer
{
public:
	static HttpResponse* ServeImage(std::string requestedImage);
	static HttpResponse* ServeFile(std::string requestedPage, Properties::CONTENT_TYPE contentType);
	static HttpResponse* ServeExternalLibFile(std::string requestedPage, Properties::CONTENT_TYPE contentType);
	static std::string CreateHtmlOutputForBinary(const std::string& fullPath);
};
