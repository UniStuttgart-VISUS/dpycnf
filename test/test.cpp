// <copyright file="test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2015 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <iostream>
#include <tchar.h>

#include <nlohmann/json.hpp>


#include "dpycnf.h"

#define _X(s) DPYCNF_XML_LITERAL(s)


/// <summary>
/// Entry point for the test application.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(int argc, TCHAR **argv) {
    typedef visus::vvand_config::display_configuration<XML_Char> config_type;
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    try {
        auto config = config_type::load(_X("..\\vvand10.xml"));

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

        // Convert the configuration to JSON.
        nlohmann::json json = config;
        std::cout << json << std::endl;

        // Convert back from JSON.
        auto config2 = json.template get<config_type>();

    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        auto text = _X("<TiledDisplay xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns=\"http://www.visus.uni-stuttgart.de/vvand/2012/description\"><Machines><Machine><Identity>keshiki01</Identity><Tiles><Tile><LeftOffset>0</LeftOffset><Name>(0, 0), [2400, 4096] auf Maschine keshiki01</Name><StereoChannel>Left</StereoChannel><TopOffset>0</TopOffset><WindowHeight>4096</WindowHeight><WindowWidth>2400</WindowWidth></Tile></Tiles></Machine></Machines></TiledDisplay>");
        auto config = config_type::parse(text);

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

        // Search a specific machine and tile.
        {
            auto mit = config.find_machine("keshiki01");
            if (mit != config.end()) {
                auto tit = mit->find_tile("(0, 0), [2400, 4096] auf Maschine keshiki01");
                std::cout << "\"" << tit->name() << "\" on \"" << mit->identity() << "\"" << std::endl;
            }
        }

        // Dump the XML configuration into a stream.
        std::cout << config << std::endl;

    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
