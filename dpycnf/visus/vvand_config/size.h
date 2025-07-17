// <copyright file="size.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2015 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_DPYCNF_VISUS_VVAND_CONFIG_SIZE_H)
#define _DPYCNF_VISUS_VVAND_CONFIG_SIZE_H
#pragma once

#include <cinttypes>

#include "visus/vvand_config/api.h"


DPYCNF_NAMESPACE_BEGIN

/// <summary>
/// Specifies a two-dimensional size.
/// </summary>
class size {

public:

    /// <summary>
    /// The type to measure width and height.
    /// </summary>
    typedef unsigned int value_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="width">The width of the area.</param>
    /// <param name="height">The height of the area.</param>
    inline size(const value_type width = 0,
            const value_type height = 0) noexcept
        : width(width), height(height) { }

    /// <summary>
    /// Answer whether the area is empty.
    /// <summary>
    /// <returns><c>true</c> if the area is empty, <c>false</c> otherwise.
    /// </returns>
    inline bool empty(void) const {
        return (this->width * this->height == 0);
    }

    /// <summary>
    /// The width of the area.
    /// </summary>
    value_type width;

    /// <summary>
    /// The height of the area.
    /// </summary>
    value_type height;
};


#if defined(NLOHMANN_JSON_VERSION_MAJOR)
/// <summary>
/// Converts a size to JSON.
/// </summary>
/// <param name="json"></param>
/// <param name="value"></param>
inline void to_json(nlohmann::json& json, const size value);

/// <summary>
/// Restores a size from JSON.
/// </summary>
/// <param name="json"></param>
/// <param name="value"></param>
inline void from_json(const nlohmann::json& json, size& value);
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */

DPYCNF_NAMESPACE_END

#include "visus/vvand_config/size.inl"

#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_SIZE_H) */
