#pragma once

//forward declarations
struct WebServer
{
	struct http_request;
};


class Index {
public:
	static void HandleRequest(WebServer::http_request* r);
	static void ConfigureServer();
private:
	static void FileNotFoundError(WebServer::http_request* r);
};