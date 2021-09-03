
#include <iostream>
#include <vector>
#include <regex>
#include "FileDiagnostics.h"


#define Key 0

int main()
{

#if Key
    aricanli::general::FileDiagnostics fd("log.txt");
    fd.parseWithDelimiter('\n');
    fd.searchbyKey("INFO","searchbyKey.txt");
#else
    aricanli::general::tools::FileDiagnostics fd("log.txt");
    fd.parseWithDelimiter('\n');
    fd.searchbyDateTime("19:40:00", "19:50:00","searchbyDate.txt");
#endif
    //
    
    return 0;
}