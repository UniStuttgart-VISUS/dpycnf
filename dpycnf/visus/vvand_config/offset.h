/// <copyright file="offset.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 - 2018 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>


namespace visus {
namespace vvand_config {

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
        inline offset(const value_type left = 0, const value_type top = 0)
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

} /* end namespace vvand_config */
} /* end namespace visus */
