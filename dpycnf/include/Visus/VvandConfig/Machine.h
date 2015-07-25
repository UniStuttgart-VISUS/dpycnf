/// <copyright file="VvandConfig.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include "Visus/VvandConfig/Tile.h"


#ifndef DPYCNF_STATIC
// Make instantiation available in DLL interface.
template class DPYCNF_API std::vector<Visus::VvandConfig::Tile>;
#endif /* !DPYCNF_STATIC */


namespace Visus {
namespace VvandConfig {

    /// <summary>
    /// Represents a machine that drives one or more tiles.
    /// </summary>
    class DPYCNF_API Machine {

    public:

        typedef std::basic_string<wchar_t> StringType;
        typedef std::vector<Tile> TileCollectionType;

        const StringType& GetIdentity(void) const {
            return this->identity;
        }

        TileCollectionType::const_iterator GetTilesBegin(void) const {
            return this->tiles.begin();
        }

        TileCollectionType::const_iterator GetTilesEnd(void) const {
            return this->tiles.end();
        }

    private:

#pragma warning(push)
#pragma warning(disable: 4251)
        StringType identity;
#pragma warning(pop)
        TileCollectionType tiles;

        friend class VvandConfigParser;
    };

}
}
