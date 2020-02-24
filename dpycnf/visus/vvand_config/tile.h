/// <copyright file="tile.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2015 - 2020 Christoph M�ller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>

#pragma once

#include <cinttypes>
#include <string>

#include "visus/vvand_config/offset.h"
#include "visus/vvand_config/size.h"
#include "visus/vvand_config/stereo_channel.h"


namespace visus {
namespace vvand_config {

    /* Forward declarations. */
    namespace detail { template<class> class vvand_config_parser; }


    /// <summary>
    /// Represents a single tile of the display that is driven by a specific
    /// <see cref="visus::vvand_config::machine" />.
    /// </summary>
    template<class T> class tile {

    public:

        typedef T char_type;
        typedef visus::vvand_config::offset offset_type;
        typedef visus::vvand_config::size size_type;
        typedef visus::vvand_config::stereo_channel stereo_channel_type;
        typedef std::basic_string<T> string_type;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        tile(void) : _channel(stereo_channel_type::mono), _position(nullptr) { }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~tile(void);

        /// <summary>
        /// Gets the stereo channel that is displayed on the tile.
        /// </summary>
        inline stereo_channel_type channel(void) const {
            return this->_channel;
        }

        /// <summary>
        /// Gets the user-defined name of the tile.
        /// </summary>
        inline const string_type& name(void) const {
            return this->_name;
        }

        /// <summary>
        /// Gets the offset of the tile from the origin of the tiled display.
        /// </summary>
        inline const offset_type& offset(void) const {
            return this->_offset;
        }

        /// <summary>
        /// Gets the (optional) position of the window on the desktop of the
        /// machine.
        /// </summary>
        inline const offset_type *position(void) const {
            return this->_position;
        }

        /// <summary>
        /// Gets the size of the tile.
        /// </summary>
        inline const size_type& size(void) const {
            return this->_size;
        }

    private:

        stereo_channel_type _channel;
        string_type _name;
        offset_type _offset;
        size_type _size;
        offset_type *_position;

        friend class detail::vvand_config_parser<T>;
    };

} /* end namespace vvand_config */
} /* end namespace visus */

#include "visus/vvand_config/tile.inl"
