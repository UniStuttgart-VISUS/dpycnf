// test.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <tchar.h>


#include "dpycnf.h"

#define _X(s) DPYCNF_XML_LITERAL(s)


int _tmain(int argc, TCHAR **argv) {
    try {
        auto config = visus::vvand_config::display_configuration<XML_Char>::load(_X("..\\vvand10.xml"));

        // Recursively iterate all tiles.
        for (auto it = config.tiles_begin(), end = config.tiles_end(); it != end; ++it) {
            std::cout << it->name() << std::endl;
        }

        // Iterate all machines and their respective tiles.
        for (auto& m : config) {
            for (auto& t : m) {
                std::cout << t.name() << std::endl;
            }
        }

        // Dump the XML configuration into a stream.
        std::cout << config << std::endl;

    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        auto text = _X("<TiledDisplay xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns=\"http://www.visus.uni-stuttgart.de/vvand/2012/description\"><Machines><Machine><Identity>keshiki01</Identity><Tiles><Tile><LeftOffset>0</LeftOffset><Name>(0, 0), [2400, 4096] auf Maschine keshiki01</Name><StereoChannel>Left</StereoChannel><TopOffset>0</TopOffset><WindowHeight>4096</WindowHeight><WindowWidth>2400</WindowWidth></Tile></Tiles></Machine></Machines></TiledDisplay>");
        auto config = visus::vvand_config::display_configuration<XML_Char>::parse(text);

        // Recursively iterate all tiles.
        for (auto it = config.tiles_begin(), end = config.tiles_end(); it != end; ++it) {
            std::cout << it->name() << std::endl;
        }

        // Iterate all machines and their respective tiles.
        for (auto& m : config) {
            for (auto& t : m) {
                std::cout << t.name() << std::endl;
            }
        }

        // Dump the XML configuration into a stream.
        std::cout << config << std::endl;

    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
