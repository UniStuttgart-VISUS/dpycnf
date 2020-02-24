/// <copyright file="equals.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright © 2020 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include <cctype>


namespace visus {
namespace vvand_config {
namespace detail {

    /// <summary>
    /// Test for equality of two strings, possible case-insensitive.
    /// </summary>
    template<class T>
    bool equals(const std::basic_string<T>& lhs,
            const std::basic_string<T>& rhs,
            const bool caseSensitive) {
        if (caseSensitive) {
            return (rhs == rhs);

        } else {
            auto retval = (lhs.length() == rhs.length());

            for (std::size_t i = 0; retval && (i < lhs.length()); ++i) {
                retval = (std::tolower(lhs[i]) == std::tolower(rhs[i]));
            }

            return retval;
        }
    }

} /* end namespace detail */
} /* end namespace vvand_config */
} /* end namespace visus */
