// <copyright file="equals.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2020 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_DPYCNF_VISUS_VVAND_CONFIG_EQUALS_H)
#define _DPYCNF_VISUS_VVAND_CONFIG_EQUALS_H
#pragma once

#include <cctype>

#include "visus/vvand_config/api.h"


DPYCNF_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Test for equality of two strings, possible case-insensitive.
/// </summary>
template<class TChar>
bool equals(const std::basic_string<TChar>& lhs,
        const std::basic_string<TChar>& rhs,
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

DPYCNF_DETAIL_NAMESPACE_END

#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_EQUALS_H) */
