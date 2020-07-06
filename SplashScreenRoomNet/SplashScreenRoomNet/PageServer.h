#pragma once

//external includes
#include <string>
#include <vector>

//internal includes
#include "HttpResponse.h"

class PageServer {
public:
	//functions
	static HttpResponse* ServePage(std::string requestPath);
	static std::vector<std::string> InterpretUrlSections(std::string urlPath);
	static void Configure();
	//properties
	static std::vector<std::string> specialPaths;
};
