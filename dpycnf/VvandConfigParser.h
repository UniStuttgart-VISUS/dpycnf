/// <copyright file="VvandConfigParser.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include "SaxParser.h"

#include "Visus/VvandConfig/DisplayConfiguration.h"
#include "Visus/VvandConfig/Tile.h"
#include "Visus/VvandConfig/Machine.h"


namespace Visus {
namespace VvandConfig {

    /// <summary>
    /// Parser for the original VISUS Vvand configuration file.
    /// </summary>
    class VvandConfigParser : public SaxParser {

    public:

        VvandConfigParser(void);

        virtual ~VvandConfigParser(void);

        Visus::VvandConfig::DisplayConfiguration Parse(const StringType& path);

    protected:

        virtual void OnCharacters(const XML_Char *s, const int len);

        virtual void OnEndElement(const XML_Char *name);

        virtual void OnStartElement(const XML_Char *name,
            const XML_Char **atts);

    private:

        typedef SaxParser Base;

        enum class Scope {
            UNKNOWN,
            TILED_DISPLAY,
            MACHINES,
            MACHINE,
            TILES,
            TILE
        };

        StringType cdata;
        Visus::VvandConfig::DisplayConfiguration currentConfig;
        Visus::VvandConfig::Machine currentMachine;
        Scope currentScope;
        Visus::VvandConfig::Tile currentTile;
    };

}
}
