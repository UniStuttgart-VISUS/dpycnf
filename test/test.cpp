// test.cpp : Defines the entry point for the console application.
//

#include <tchar.h>

#include "dpycnf.h"


int _tmain(int argc, TCHAR **argv) {
    auto config = Visus::VvandConfig::DisplayConfiguration::Parse(_T("..\\vvand10.xml"));
    return 0;
}
