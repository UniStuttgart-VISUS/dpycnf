/// <copyright file="StereoChannel.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include "dpycnfapi.h"


namespace Visus {

    /// <summary>
    /// Defines offsets of tiles.
    /// </summary>
    class DPYCNF_API Offset {

    public:

        /// <summary>
        /// The type to measure the offset on one axis.
        /// </summary>
        typedef unsigned int OffsetType;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline Offset(const OffsetType left = 0, const OffsetType top = 0)
            : Left(left), Top(top) { }

        /// <summary>
        /// The left offset.
        /// </summary>
        OffsetType Left;

        /// <summary>
        /// The top offset.
        /// </summary>
        OffsetType Top;
    };

}
