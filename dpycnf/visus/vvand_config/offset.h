// <copyright file="offset.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2015 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_DPYCNF_VISUS_VVAND_CONFIG_OFFSET_H)
#define _DPYCNF_VISUS_VVAND_CONFIG_OFFSET_H
#pragma once

#include <cinttypes>

#include "visus/vvand_config/api.h"


DPYCNF_NAMESPACE_BEGIN

/// <summary>
/// Defines offsets of tiles.
/// </summary>
/// <typeparam name="TValue">The type to measure the offset on one axis.
/// </typeparam>
template<class TValue> class basic_offset final {

public:

    /// <summary>
    /// The type to measure the offset on one axis.
    /// </summary>
    typedef TValue value_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="left">The left offset of the tile.</param>
    /// <param name="top">The top offset of the tile.</param>
    inline basic_offset(const value_type left = static_cast<value_type>(0),
            const value_type top = static_cast<value_type>(0)) noexcept
        : left(left), top(top) { }

    /// <summary>
    /// The left offset.
    /// </summary>
    value_type left;

    /// <summary>
    /// The top offset.
    /// </summary>
    value_type top;
};


/// <summary>
/// Defines offsets of tiles.
/// </summary>
typedef basic_offset<std::uint32_t> offset;


/// <summary>
/// Initialises a new offset object.
/// </summary>
/// <typeparam name="TValue">The type to measure the offset on one axis.
/// </typeparam>
/// <param name="left">The left offset of the tile.</param>
/// <param name="top">The top offset of the tile.</param>
/// <returns>The newly created object.</returns>
template<class TValue>
inline basic_offset<TValue> make_offset(const TValue width,
        const TValue height) noexcept {
    return basic_offset<TValue>(width, height);
}


#if defined(NLOHMANN_JSON_VERSION_MAJOR)
/// <summary>
/// Converts an offset to JSON.
/// </summary>
/// <typeparam name="TValue">The type to measure the offset on one axis.
/// </typeparam>
/// <param name="json"></param>
/// <param name="value"></param>
template<class TValue>
inline void to_json(nlohmann::json& json, const basic_offset<TValue>& value);

/// <summary>
/// Restores an offset from JSON.
/// </summary>
/// <typeparam name="TValue">The type to measure the offset on one axis.
/// </typeparam>
/// <param name="json"></param>
/// <param name="value"></param>
template<class TValue>
inline void from_json(const nlohmann::json& json, basic_offset<TValue>& value);
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */

DPYCNF_NAMESPACE_END

#include "visus/vvand_config/offset.inl"

#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_OFFSET_H) */
