// <copyright file="tile.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2015 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_DPYCNF_VISUS_VVAND_CONFIG_TILE_H)
#define _DPYCNF_VISUS_VVAND_CONFIG_TILE_H
#pragma once

#include <cinttypes>
#include <memory>
#include <string>


#include "visus/vvand_config/offset.h"
#include "visus/vvand_config/size.h"
#include "visus/vvand_config/stereo_channel.h"
#include "visus/vvand_config/xmljson.h"


DPYCNF_NAMESPACE_BEGIN

/* Forward declarations. */
namespace detail { template<class> class vvand_config_parser; }


/// <summary>
/// Represents a single tile of the display that is driven by a specific
/// <see cref="visus::vvand_config::machine" />.
/// </summary>
template<class TChar> class tile {

public:

    typedef TChar char_type;
    typedef visus::vvand_config::offset offset_type;
    typedef visus::vvand_config::size size_type;
    typedef visus::vvand_config::stereo_channel stereo_channel_type;
    typedef std::basic_string<TChar> string_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline tile(void) noexcept
        : _channel(stereo_channel_type::mono),
        _position(nullptr) { }

    /// <summary>
    /// Clone <paramref name="rhs" />.
    /// </summary>
    inline tile(const tile& rhs) : _position(nullptr) {
        *this = rhs;
    }

    /// <summary>
    /// Move <paramref name="rhs" />.
    /// </summary>
    inline tile(tile&& rhs) noexcept : _position(nullptr) {
        *this = std::move(rhs);
    }

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~tile(void) noexcept;

    /// <summary>
    /// Gets the stereo channel that is displayed on the tile.
    /// </summary>
    inline stereo_channel_type channel(void) const noexcept {
        return this->_channel;
    }

    /// <summary>
    /// Gets the user-defined name of the tile.
    /// </summary>
    inline const string_type& name(void) const noexcept {
        return this->_name;
    }

    /// <summary>
    /// Gets the offset of the tile from the origin of the tiled display.
    /// </summary>
    inline const offset_type& offset(void) const noexcept {
        return this->_offset;
    }

    /// <summary>
    /// Gets the (optional) position of the window on the desktop of the
    /// machine.
    /// </summary>
    inline const offset_type *position(void) const noexcept {
        return this->_position;
    }

    /// <summary>
    /// Gets the size of the tile.
    /// </summary>
    inline const size_type& size(void) const noexcept {
        return this->_size;
    }

    /// <summary>
    /// Assign <paramref name="rhs" />.
    /// </summary>
    tile& operator =(const tile& rhs);

    /// <summary>
    /// Move <paramref name="rhs" />.
    /// </summary>
    tile& operator =(tile&& rhs) noexcept;

private:

    stereo_channel_type _channel;
    string_type _name;
    offset_type _offset;
    offset_type *_position;
    size_type _size;

    friend class detail::vvand_config_parser<TChar>;

#if defined(NLOHMANN_JSON_VERSION_MAJOR)
    template<class T> friend void to_json(nlohmann::json&, const tile<T>&);
    template<class T> friend void from_json(const nlohmann::json&, tile<T>&);
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */
};


#if defined(NLOHMANN_JSON_VERSION_MAJOR)
/// <summary>
/// Converts a tile to JSON.
/// </summary>
/// <param name="json"></param>
/// <param name="value"></param>
template<class TChar>
void to_json(nlohmann::json& json, const tile<TChar>& value);

/// <summary>
/// Restores a tile from JSON.
/// </summary>
/// <param name="json"></param>
/// <param name="value"></param>
template<class TChar>
void from_json(const nlohmann::json& json, tile<TChar>& value);
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */

DPYCNF_NAMESPACE_END

#include "visus/vvand_config/tile.inl"

#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_TILE_H) */
