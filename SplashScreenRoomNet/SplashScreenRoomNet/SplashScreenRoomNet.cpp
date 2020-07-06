#include "Index.h"
#include "../../cppwebserver/CppWebServer/CppWebServer/WebServer.h"

int main()
{
    Index::ConfigureServer();
    new CppWebServer::WebServer(8080, Index::HandleRequest);
}