//external include
#include <algorithm>

//internal includes
#include "HttpResponse.h"

//initialise private static members
std::vector<int> HttpResponse::_successCodeList = {
	200,
	201,
	202
};

HttpResponse::HttpResponse()
{
	new HttpResponse(500, "", "text/plain");
}

HttpResponse::HttpResponse(int statusCode, std::string content, std::string contentType)
	: _statusCode(statusCode), //validate to make sure the provided code is in a list of codes (maybe enum)?
	_content(content),
	_contentType(contentType) //validate this as above
{
}

void HttpResponse::SetStatusCode(int statusCode)
{
	_statusCode = statusCode;
}

int  HttpResponse::GetStatusCode()
{
	return _statusCode;
}

void HttpResponse::SetContent(std::string content)
{
	_content = content;
}

std::string HttpResponse::GetContent()
{
	return _content;
}

void HttpResponse::SetContentType(Properties::CONTENT_TYPE contentType)
{
	_contentType = Properties::contentTypeMappings[contentType];
}

std::string HttpResponse::GetContentType()
{
	return _contentType;
}

bool HttpResponse::ResponseSuccessful()
{
	return (std::find(_successCodeList.begin(), _successCodeList.end(), _statusCode) != _successCodeList.end());
}

void HttpResponse::SetError(int responseCode, std::string errorMessage)
{
	_statusCode = responseCode;
	_content = errorMessage;
	_contentType = "text/plain";
}