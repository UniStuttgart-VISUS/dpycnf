/// <copyright file="size.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 - 2018 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>


namespace visus {
namespace vvand_config {

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
        inline size(const value_type width = 0, const value_type height = 0)
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

} /* end namespace vvand_config */
} /* end namespace visus */
