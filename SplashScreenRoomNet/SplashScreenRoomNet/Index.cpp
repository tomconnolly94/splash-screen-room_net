//internal includes
#include "Index.h"
#include "PageServer.h"
#include "HttpResponse.h"
#include "HttpResponse.cpp"

void Index::HandleRequest(CppWebServer::http_request* httpRequest)
{
    std::string requestPath = httpRequest->path_;
    HttpResponse* httpResponse = PageServer::ServePage(requestPath);

    if (!httpResponse->ResponseSuccessful())
    {
        httpRequest->status_ = "404 Not Found";
    }

    httpRequest->response_ = {
        httpResponse->GetContentType(),
        httpResponse->GetContent()
    };
}