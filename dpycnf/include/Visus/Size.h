/// <copyright file="Size.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include "dpycnfapi.h"


namespace Visus {

    /// <summary>
    /// Specifies a two-dimensional size.
    /// </summary>
    class DPYCNF_API Size {

    public:

        /// <summary>
        /// The type to measure width and height.
        /// </summary>
        typedef unsigned int SizeType;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline Size(const SizeType width = 0, const SizeType height = 0)
            : Width(width), Height(height) { }

        /// <summary>
        /// The width of the area.
        /// </summary>
        SizeType Width;

        /// <summary>
        /// The height of the area.
        /// </summary>
        SizeType Height;

    };

}
