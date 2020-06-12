#include "Index.h"
#include "../../cppwebserver/CppWebServer/CppWebServer/WebServer.h"

int main()
{
    Index::ConfigureServer();
    WebServer(8080, Index::HandleRequest);
}