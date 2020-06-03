#include "Index.h"

int main()
{
    WebServer(8080, Index::HandleRequest);
}