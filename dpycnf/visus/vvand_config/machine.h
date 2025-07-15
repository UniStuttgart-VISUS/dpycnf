// <copyright file="machine.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2015 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_DPYCNF_VISUS_VVAND_CONFIG_MACHINE_H)
#define _DPYCNF_VISUS_VVAND_CONFIG_MACHINE_H
#pragma once

#include <vector>

#include "visus/vvand_config/equals.h"
#include "visus/vvand_config/tile.h"


DPYCNF_NAMESPACE_BEGIN

/// <summary>
/// Represents a machine that drives one or more tiles.
/// </summary>
/// <typeparam name="TChar">The character type used in the configuration.
/// </typeparam>
template<class TChar> class machine {

public:

    typedef TChar char_type;
    typedef typename std::vector<tile<TChar>>::const_iterator iterator_type;
    typedef typename tile<TChar>::offset_type offset_type;
    typedef std::basic_string<TChar> string_type;
    typedef tile<TChar> tile_type;

    /// <summary>
    /// Answer the begin of the range of tiles on this machine.
    /// </summary>
    iterator_type begin(void) const noexcept {
        return this->_tiles.begin();
    }

    /// <summary>
    /// Answer the end of the range of tiles on this machine.
    /// </summary>
    iterator_type end(void) const noexcept {
        return this->_tiles.end();
    }

    /// <summary>
    /// Search the tile with the specified name.
    /// </summary>
    iterator_type find_tile(const string_type& name,
        const bool caseSensitive = false) const;

    /// <summary>
    /// Search the tile using the specified offset.
    /// </summary>
    iterator_type find_tile(const offset_type& offset,
        const bool windowOffset) const;

    /// <summary>
    /// Answer the configured identity of the machine.
    /// </summary>
    const string_type& identity(void) const noexcept {
        return this->_identity;
    }

private:

    string_type _identity;
    std::vector<tile_type> _tiles;

    friend class detail::vvand_config_parser<TChar>;
};

DPYCNF_NAMESPACE_END

#include "visus/vvand_config/machine.inl"

#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_MACHINE_H) */
