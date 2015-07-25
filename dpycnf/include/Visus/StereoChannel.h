/// <copyright file="StereoChannel.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2015 Christoph M�ller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>

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
