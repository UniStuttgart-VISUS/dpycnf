// test.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <tchar.h>


#include "dpycnf.h"


int _tmain(int argc, TCHAR **argv) {
    try {
        auto config = Visus::VvandConfig::DisplayConfiguration::Load(_T("..\\vvand10.xml"));
        for (auto it = config.GetTilesBegin(); it != config.GetTilesEnd(); ++it) {
            std::wcout << it->GetName().c_str() << std::endl;
        }
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        std::basic_string<TCHAR> text = _T("<TiledDisplay xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns=\"http://www.visus.uni-stuttgart.de/vvand/2012/description\"><Machines><Machine><Identity>keshiki01</Identity><Tiles><Tile><LeftOffset>0</LeftOffset><Name>(0, 0), [2400, 4096] auf Maschine keshiki01</Name><StereoChannel>Left</StereoChannel><TopOffset>0</TopOffset><WindowHeight>4096</WindowHeight><WindowWidth>2400</WindowWidth></Tile></Tiles></Machine></Machines></TiledDisplay>");
        auto config = Visus::VvandConfig::DisplayConfiguration::Parse(text);
        for (auto it = config.GetTilesBegin(); it != config.GetTilesEnd(); ++it) {
            std::wcout << it->GetName().c_str() << std::endl;
        }
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
