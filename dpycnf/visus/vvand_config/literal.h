/// <copyright file="literal.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright © 2017 - 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

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


namespace visus {
namespace vvand_config {
namespace detail {

    template<class T> struct literal_selector {
        typedef T char_type;
    };

    template<> struct literal_selector<char> {
        typedef char char_type;
        static const char_type select(const char n, const wchar_t w) {
            return n;
        }
        static const char_type *select(const char *n, const wchar_t *w) {
            return n;
        }
    };

    template<> struct literal_selector<wchar_t> {
        typedef wchar_t char_type;
        static const char_type select(const char n, const wchar_t w) {
            return w;
        }
        static const char_type *select(const char *n, const wchar_t *w) {
            return w;
        }
    };

} /* end namespace detail */
} /* end namespace vvand_config */
} /* end namespace visus */

#define DPYCNF_TPL_LITERAL(T, l) visus::vvand_config::detail::literal_selector<T>::select(l, L##l)
