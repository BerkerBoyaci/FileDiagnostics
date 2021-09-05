
#include <iostream>
#include "FileDiagnostics.h"

#define Key 0

int main()
{

#if Key
    aricanli::general::tools::FileDiagnostics fd("log.txt");
    fd.writeOptions("searchbyKey", "txt", '\n');
    fd.searchbyKey("INFO");
#else
    aricanli::general::tools::FileDiagnostics fd("log.txt");
    fd.writeOptions("searchbyDate","txt");
    fd.searchbyDateTime("19:40:00", "19:50:00");
#endif
    
    return 0;
}