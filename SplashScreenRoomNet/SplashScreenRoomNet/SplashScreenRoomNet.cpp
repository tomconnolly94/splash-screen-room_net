#include "Index.h"

int main()
{
    Index::ConfigureServer();
    WebServer(8080, Index::HandleRequest);
}