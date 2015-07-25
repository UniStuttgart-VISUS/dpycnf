// test.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <tchar.h>


#include "dpycnf.h"


int _tmain(int argc, TCHAR **argv) {
    auto config = Visus::VvandConfig::DisplayConfiguration::Parse(_T("..\\vvand10.xml"));
    for (auto it = config.GetTilesBegin(); it != config.GetTilesEnd(); ++it) {
        std::wcout << it->GetName().c_str() << std::endl;
    }
    return 0;
}
