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
class offset {

public:

    /// <summary>
    /// The type to measure the offset on one axis.
    /// </summary>
    typedef unsigned int value_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="left">The left offset of the tile.</param>
    /// <param name="top">The top offset of the tile.</param>
    inline offset(const value_type left = 0,
            const value_type top = 0) noexcept
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


#if defined(NLOHMANN_JSON_VERSION_MAJOR)
/// <summary>
/// Converts an offset to JSON.
/// </summary>
/// <param name="json"></param>
/// <param name="value"></param>
inline void to_json(nlohmann::json& json, const offset& value);

/// <summary>
/// Restores an offset from JSON.
/// </summary>
/// <param name="json"></param>
/// <param name="value"></param>
inline void from_json(const nlohmann::json& json, offset& value);
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */

DPYCNF_NAMESPACE_END

#include "visus/vvand_config/offset.inl"

#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_OFFSET_H) */
