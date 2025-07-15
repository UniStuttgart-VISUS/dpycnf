// <copyright file="dpycnf.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2015 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_DPYCNF_H)
#define _DPYCNF_H
#pragma once


/// <summary>
/// A helper for implementing <see cref="DPYCNF_CONCAT" />.
/// </summary>
#define _DPYCNF_CONCAT(l, r) l ##r

/// <summary>
/// Concatenates two preprocessor symbols.
/// </summary>
/// <param name="l">The left-hand side operand.</param>
/// <param name="r">The right-hand side operand.</param>
#define DPYCNF_CONCAT(l, r) _DPYCNF_CONCAT(l, r)



#include "visus/vvand_config/display_configuration.h"
#include "visus/vvand_config/machine.h"
#include "visus/vvand_config/offset.h"
#include "visus/vvand_config/tile.h"
#include "visus/vvand_config/size.h"

#endif /* !defined(_DPYCNF_H) */
