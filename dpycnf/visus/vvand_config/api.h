// <copyright file="api.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_DPYCNF_VISUS_VVAND_CONFIG_API_H)
#define _DPYCNF_VISUS_VVAND_CONFIG_API_H
#pragma once


/******************************************************************************\
 * Update the ABI version (i.e. if something in the interface changes) here:  *
\******************************************************************************/
#define DPYCNF_ABI_MAJOR 1
#define DPYCNF_ABI_MINOR 1


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


/// <summary>
/// Creates the full ABI versison string.
/// </summary>
/// <param name="mj">The major version of the ABI.</param>
/// <param name="mn">The minor version of the ABI.</param>
#define DPYCNF_ABI_VERSION(mj, mn) DPYCNF_CONCAT(mj, DPYCNF_CONCAT(_, mn))


/// <summary>
/// Creates the name of the namespace for the specified ABI version.
/// </summary>
/// <param name="mj">The major version of the ABI.</param>
/// <param name="mn">The minor version of the ABI.</param>
#define DPYCNF_ABI_NAMESPACE(mj, mn) \
DPYCNF_CONCAT(v, DPYCNF_ABI_VERSION(mj, mn))


/// <summary>
/// Creates the name of the current ABI namespace.
/// </summary>
/// <remarks>
/// Use this macro when defining implementations in cpp or inline files.
/// </remarks>
#define DPYCNF_NAMESPACE visus::vvand_config::\
DPYCNF_ABI_NAMESPACE(DPYCNF_ABI_MAJOR, DPYCNF_ABI_MINOR)


/// <summary>
/// Creates the name of the namespace for the implementation details.
/// </summary>
/// <remarks>
/// Use this macro when defining implementations in cpp or inline files.
/// </remarks>
#define DPYCNF_DETAIL_NAMESPACE DPYCNF_NAMESPACE::detail


/// <summary>
/// Helper for opening the namespace <paramref name="n" />.
/// </summary>
#define _DPYCNF_NAMESPACE_BEGIN(n) namespace n {


/// <summary>
/// Marks the begin of the current ABI namespace.
/// </summary>
#define DPYCNF_NAMESPACE_BEGIN \
_DPYCNF_NAMESPACE_BEGIN(visus)\
_DPYCNF_NAMESPACE_BEGIN(vvand_config)\
inline _DPYCNF_NAMESPACE_BEGIN(\
    DPYCNF_ABI_NAMESPACE(DPYCNF_ABI_MAJOR, DPYCNF_ABI_MINOR))

/// <summary>
/// Marks the end of the current ABI namespace.
/// </summary>
#define DPYCNF_NAMESPACE_END } } }


/// <summary>
/// Marks the begin of the namespace for implementation details.
/// </summary>
#define DPYCNF_DETAIL_NAMESPACE_BEGIN \
DPYCNF_NAMESPACE_BEGIN _DPYCNF_NAMESPACE_BEGIN(detail)

/// <summary>
/// Marks the end of the namespace for implementation details.
/// </summary>
#define DPYCNF_DETAIL_NAMESPACE_END } DPYCNF_NAMESPACE_END

#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_API_H) */
