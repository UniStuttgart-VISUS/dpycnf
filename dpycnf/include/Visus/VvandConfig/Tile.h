/// <copyright file="Tile.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include "dpycnfapi.h"

#include <string>
#include <vector>

#include "Visus/Offset.h"
#include "Visus/Size.h"
#include "Visus/StereoChannel.h"


// Make instantiation available in DLL interface.
template class DPYCNF_API std::basic_string<wchar_t>;


namespace Visus {
namespace VvandConfig {

    /// <summary>
    /// Represents a single tile of the display that is driven by a specific
    /// <see cref="Visus::VvandConfig::Machine" />.
    /// </summary>
    class DPYCNF_API Tile {

    public:

        typedef std::basic_string<wchar_t> StringType;

        Tile(void);

        ~Tile(void);

        /// <summary>
        /// Gets the user-defined name of the tile.
        /// </summary>
        inline const StringType& GetName(void) const {
            return this->name;
        }

        /// <summary>
        /// Gets the offset of the tile from the origin of the tiled display.
        /// </summary>
        inline const Offset& GetOffset(void) const {
            return this->offset;
        }

        /// <summary>
        /// Gets the size of the tile.
        /// </summary>
        inline const Size& GetSize(void) const {
            return this->size;
        }

        /// <summary>
        /// Gets the stereo channel that is displayed on the tile.
        /// </summary>
        inline StereoChannel GetStereoChannel(void) const {
            return this->stereoChannel;
        }

    private:

        StringType name;
        Offset offset;
        Size size;
        StereoChannel stereoChannel;

        friend class VvandConfigParser;
    };

}
}
