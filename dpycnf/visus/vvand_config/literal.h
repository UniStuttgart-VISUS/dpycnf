// <copyright file="literal.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright © 2017 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_DPYCNF_VISUS_VVAND_CONFIG_LITERAL_H)
#define _DPYCNF_VISUS_VVAND_CONFIG_LITERAL_H
#pragma once


#if defined(XML_UNICODE) && (defined(T2W))
#define T2XML T2W
#endif /* defined(XML_UNICODE) && (defined(T2W)) */

#if defined(XML_UNICODE) && (defined(W2T))
#define XML2T W2T
#endif /* defined(XML_UNICODE) && (defined(W2T)) */

#if !defined(XML_UNICODE) && (defined(T2A))
#define T2XML T2A
#endif /* !defined(XML_UNICODE) && (defined(T2A)) */

#if !defined(XML_UNICODE) && (defined(A2T))
#define XML2T A2T
#endif /* !defined(XML_UNICODE) && (defined(A2T)) */


DPYCNF_DETAIL_NAMESPACE_BEGIN

template<class TChar> struct literal_selector {
    typedef TChar char_type;
};

template<> struct literal_selector<char> {
    typedef char char_type;
    static constexpr char_type select(const char n,
            const wchar_t) noexcept {
        return n;
    }
    static constexpr const char_type *select(const char *n,
            const wchar_t *) noexcept {
        return n;
    }
};

template<> struct literal_selector<wchar_t> {
    typedef wchar_t char_type;
    static constexpr char_type select(const char,
            const wchar_t w) noexcept {
        return w;
    }
    static constexpr const char_type *select(const char *,
            const wchar_t *w) noexcept {
        return w;
    }
};

DPYCNF_DETAIL_NAMESPACE_END


#define DPYCNF_TPL_LITERAL(TChar, l) DPYCNF_DETAIL_NAMESPACE::literal_selector<TChar>::select(l, L##l)


#ifdef XML_UNICODE
#define DPYCNF_XML_LITERAL(s) L##s
#else /* XML_UNICODE */
#define DPYCNF_XML_LITERAL(s) s
#endif /* XML_UNICODE */

#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_LITERAL_H) */
