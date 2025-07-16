// <copyright file="xml_exception.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2014 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>
/*
 * XmlException.h
 *
 * Copyright (C) 2009 by Christoph Müller. Alle Rechte vorbehalten.
 */

#if !defined(_DPYCNF_VISUS_VVAND_CONFIG_XML_EXCEPTION_H)
#define _DPYCNF_VISUS_VVAND_CONFIG_XML_EXCEPTION_H
#if (defined(_MSC_VER) && (_MSC_VER > 1000))
#pragma once
#endif /* (defined(_MSC_VER) && (_MSC_VER > 1000)) */
#if defined(_WIN32) && defined(_MANAGED)
#pragma managed(push, off)
#endif /* defined(_WIN32) && defined(_MANAGED) */

#include <cassert>
#include <codecvt>
#include <string>
#include <stdexcept>
#include <type_traits>

#include <expat.h>

#include "visus/vvand_config/api.h"


DPYCNF_NAMESPACE_BEGIN

/// <summary>
/// This exception represents an XML parsing error.
/// </summary>
template<class TChar> class xml_exception : public std::exception {

public:

    /// <summary>
    /// The type of characters that the parser processes.
    /// </summary>
    typedef TChar char_type;

    /// <summary>
    /// The type of the XML parser's error codes.
    /// </summary>
    typedef ::XML_Error error_type;

    /// <summary>
    /// The type for sizes and positions in the XML parser.
    /// </summary>
    typedef ::XML_Size size_type;

    /// <summary>
    /// The type of strings that the parser processes.
    /// </summary>
    typedef std::basic_string<TChar> string_type;

    /// <summary>
    /// Gets a string description for an Expat error code.
    /// </summary>
    static inline std::string to_string(const error_type errorCode) {
        return xml_exception::to_string(::XML_ErrorString(errorCode));
    }

    /// <summary>
    /// Gets an std::string for an Expat string.
    /// </summary>
    template<class Tp>
    static inline typename std::enable_if<std::is_same<
        std::string::value_type, Tp>::value, std::string>::type
    to_string(const Tp *errorMsg) {
        assert(errorMsg != nullptr);
        return errorMsg;
    }

    /// <summary>
    /// Gets an std::string for an Expat string.
    /// </summary>
    template<class Tp>
    static inline typename std::enable_if<!std::is_same<
        std::string::value_type, Tp>::value, std::string>::type
    to_string(const Tp *errorMsg) {
        typedef std::codecvt_utf8<Tp> c_t;
        typedef std::basic_string<Tp> s_t;
        assert(errorMsg != nullptr);
        std::wstring_convert<c_t, Tp> converter;
        return converter.to_bytes(s_t(errorMsg));
    }

    /// <summary>
    /// Gets an std::string for an Expat string.
    /// </summary>
    template<class TChar, class TTraits, class TAlloc>
    static inline std::string to_string(
            const std::basic_string<TChar, TTraits, TAlloc>& errorMsg) {
        return to_string(errorMsg.c_str());
    }

    /// <summary>
    /// Create a new exception that represents the Expat error
    /// <paramref name="errorCode" />.
    /// </summary>
    xml_exception(const error_type errorCode, const size_type xmlLine,
        const size_type xmlColumn, const char *file, const int line);

    /// <summary>
    /// Create a new exception with a custom error message.
    /// </summary>
    xml_exception(const char_type *customMsg, const size_type xmlLine,
        const size_type xmlColumn, const char *file, const int line);

    /// <summary>
    /// Dtor.
    /// </summary>
    virtual ~xml_exception(void) noexcept = default;

    /// <summary>
    /// Gets the error code encapsulated in the exception.
    /// </summary>
    inline error_type error_code(void) const {
        return this->_error_code;
    }

    /// <summary>
    /// Gets the file in which the exception was thrown.
    /// </summary>
    inline const std::string& file(void) const {
        return this->_file;
    }

    /// <summary>
    /// Gets the line in which the exception was thrown.
    /// </summary>
    inline int line(void) const {
        return this->_line;
    }

    /// <summary>
    /// Gets the column in which a parsing error occurred.
    /// </summary>
    inline size_type xml_column(void) const {
        return this->_xml_column;
    }

    /// <summary>
    /// Gets the line in which a parsing error occurred.
    /// </summary>
    inline size_type xml_line(void) const {
        return this->_xml_line;
    }

private:

    /// <summary>
    /// Base class type.
    /// </summary>
    typedef std::exception base;

    error_type _error_code;
    std::string _file;
    int _line;
    size_type _xml_column;
    size_type _xml_line;
};

DPYCNF_NAMESPACE_END

#include "visus/vvand_config/xml_exception.inl"

#if defined(_WIN32) && defined(_MANAGED)
#pragma managed(pop)
#endif /* defined(_WIN32) && defined(_MANAGED) */
#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_XML_EXCEPTION_H) */
