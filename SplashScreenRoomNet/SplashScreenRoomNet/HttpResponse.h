#pragma once

//external includes
#include <string>
#include <vector>

//internal includes
#include "Properties.h"

class HttpResponse
{
public:
	HttpResponse();
	HttpResponse(int responseCode, std::string responseContent, std::string _contentType);

	void SetStatusCode(int statusCode);
	int GetStatusCode();

	void SetContent(std::string content);
	std::string GetContent();

	void SetContentType(Properties::CONTENT_TYPE contentType);
	std::string GetContentType();

	bool ResponseSuccessful();
	void SetError(int responseCode = 500, std::string errorMessage = "Undefined Error");

protected:
	int _statusCode;
	std::string _content;
	std::string _contentType;
	static std::vector<int> _successCodeList;
};