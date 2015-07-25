/// <copyright file="StereoChannel.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include "dpycnfapi.h"


namespace Visus {

    /// <summary>
    /// Defines possible stereo channels.
    /// </summary>
    enum class DPYCNF_API StereoChannel {
        MONO = 0,
        LEFT,
        RIGHT
    };

}
