/// <copyright file="machine.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 - 2018 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include <vector>

#include "visus/vvand_config/tile.h"


namespace visus {
namespace vvand_config {

    /// <summary>
    /// Represents a machine that drives one or more tiles.
    /// </summary>
    template<class T> class machine {

    public:

        typedef T char_type;
        typedef typename std::vector<tile<T>>::const_iterator iterator_type;
        typedef std::basic_string<T> string_type;
        typedef tile<T> tile_type;

        /// <summary>
        /// Answer the begin of the range of tiles on this machine.
        /// </summary>
        iterator_type begin(void) const {
            return this->_tiles.begin();
        }

        /// <summary>
        /// Answer the end of the range of tiles on this machine.
        /// </summary>
        iterator_type end(void) const {
            return this->_tiles.end();
        }

        /// <summary>
        /// Answer the configured identity of the machine.
        /// </summary>
        const string_type& identity(void) const {
            return this->_identity;
        }

    private:

        string_type _identity;
        std::vector<tile_type> _tiles;

        friend class detail::vvand_config_parser<T>;
    };

} /* end namespace vvand_config */
} /* end namespace visus */
