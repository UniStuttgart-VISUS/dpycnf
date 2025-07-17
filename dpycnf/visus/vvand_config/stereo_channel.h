// <copyright file="stereo_channel.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2015 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_DPYCNF_VISUS_VVAND_CONFIG_STEREO_CHANNEL_H)
#define _DPYCNF_VISUS_VVAND_CONFIG_STEREO_CHANNEL_H
#pragma once

#include "visus/vvand_config/api.h"


DPYCNF_NAMESPACE_BEGIN

/// <summary>
/// Defines possible stereo channels.
/// </summary>
enum class stereo_channel {
    /// <summary>
    /// There is only one channel.
    /// </summary>
    mono = 0,

    /// <summary>
    /// The channel for the left eye.
    /// </summary>
    left,

    /// <summary>
    /// The channel for the right eye.
    /// </summary>
    right
};


#if defined(NLOHMANN_JSON_VERSION_MAJOR)
/// <summary>
/// Converts a stereo channel to JSON.
/// </summary>
/// <param name="json"></param>
/// <param name="value"></param>
inline void to_json(nlohmann::json& json, const stereo_channel value);

/// <summary>
/// Restores a stereo channel from JSON.
/// </summary>
/// <param name="json"></param>
/// <param name="value"></param>
inline void from_json(const nlohmann::json& json, stereo_channel& value);
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */

DPYCNF_NAMESPACE_END

#include "visus/vvand_config/stereo_channel.inl"

#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_STEREO_CHANNEL_H) */
