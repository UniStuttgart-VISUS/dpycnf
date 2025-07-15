// <copyright file="sax_parser.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2014 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>
/*
 * sax_parser.h
 *
 * Copyright (C) 2009 by Christoph Müller. Alle Rechte vorbehalten.
 */

#if !defined(_DPYCNF_VISUS_VVAND_CONFIG_SAX_PARSER_H)
#define _DPYCNF_VISUS_VVAND_CONFIG_SAX_PARSER_H
#if (defined(_MSC_VER) && (_MSC_VER > 1000))
#pragma once
#endif /* (defined(_MSC_VER) && (_MSC_VER > 1000)) */
#if defined(_WIN32) && defined(_MANAGED)
#pragma managed(push, off)
#endif /* defined(_WIN32) && defined(_MANAGED) */

#include <algorithm>
#include <cinttypes>
#include <fstream>
#include <string>
#include <vector>

#include <expat.h>
#include <tchar.h>
#include <Windows.h>

#include "visus/vvand_config/xml_exception.h"


DPYCNF_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// This is the super class for SAX XML parsers. It wraps the expat library.
/// Special parsers should inherit from this class and implement the On*()
/// event handler methods as appropriate.
/// </summary>
template<class TChar> class sax_parser {

public:

    /// <summary>
    /// Representation of a single byte.
    /// </summary>
    typedef char byte_type;

    /// <summary>
    /// The type of characters that the parser processes.
    /// </summary>
    typedef TChar char_type;

    /// <summary>
    /// The exception type to represent parsing errors.
    /// </summary>
    typedef xml_exception<TChar> exception_type;

    /// <summary>
    /// The type for sizes and positions in the XML parser.
    /// </summary>
    typedef ::XML_Size size_type;

    /// <summary>
    /// The type of strings that the parser processes.
    /// </summary>
    typedef std::basic_string<TChar> string_type;

    /// <summary>
    /// Default size of the read buffer.
    /// </summary>
    static const size_t default_buffer_size = 4 * 1024;

    /// <summary>
    /// Create a new parser with the specified read buffer size.
    /// </summary>
    /// <remarks>
    /// Note that a parser that parses from a file needs a non-zero read
    /// buffer.
    /// </remarks>
    /// <param name="bufferSize">The size of the read buffer that is
    /// allocated for sequential reads.</param>
    /// <exception cref="std::bad_alloc">If the buffer could not be
    /// allocated.</exception>
    sax_parser(const size_t bufferSize = default_buffer_size);

    sax_parser(const sax_parser&) = delete;

    /// <summary>
    /// Dtor.
    /// </summary>
    virtual ~sax_parser(void) noexcept;

    /// <summary>
    /// Parse XML from the file <paramref name="file" />.
    /// </summary>
    /// <param name="path">The path to an XML file.</param>
    /// <exception cref="std::ios::failure">If an I/O error occurred while
    /// reading the input file.</exception>
    /// <exception cref="xml_exception">If an XML syntax error was found in
    /// the file.</exception>
    void parse_file(const string_type& path);

    /// <summary>
    /// Parse XML text <paramref name="text" />.
    /// </summary>
    /// <param name="text">The XML text to be parsed.</param>
    /// <exception cref="xml_exception">If an XML syntax error was found in
    /// the file.</exception>
    void parse_text(const string_type& text);

    sax_parser& operator =(const sax_parser&) = delete;

protected:

    /// <summary>
    /// Helper for comparing two XML strings for equality.
    /// </summary>
    /// <param name="s1">The first string.</param>
    /// <param name="s2">The second string.</param>
    /// <param name="isCaseSensitve">witch between case-sensitive and 
    /// case-insensitive compare.</param>
    /// <returns>true if 's1' and 's2' are equal.</returns>
    static bool are_strings_equal(const char_type *s1,
        const char_type *s2, const bool isCaseSensitive = true);

    /// <summary>
    /// Gets the number of the column the parser is currently processing.
    /// </summary>
    /// <returns></returns>
    inline size_type current_column_number(void) const {
        return ::XML_GetCurrentColumnNumber(this->parser);
    }

    /// <summary>
    /// Gets the number of the line the parser is currently processing.
    /// </summary>
    /// <returns></returns>
    inline size_type current_line_number(void) const {
        return ::XML_GetCurrentLineNumber(this->parser);
    }

    /// <summary>
    /// Overwrite this method to process text between tags.
    /// </summary>
    /// <param name="s"> Pointer to <paramref name="len" /> characters.
    /// </param>
    /// <param name="len">The number of characters starting at
    /// <paramref name="s" />.</returns>
    virtual void on_characters(const char_type *s, const int len);

    /// <summary>
    /// Overwrite this method to process closing tags.
    /// </summary>
    /// <param name="name">The name of the tag.</param>
    virtual void on_end_element(const char_type *name);

    /// <summary>
    /// Overwrite this method to process opening tags.
    /// </summary>
    /// <remarks>
    /// Attributes in <paramref name="atts" /> can be processed as follows:
    /// <code>
    /// for (int i = 0; atts[i] != nullptr; i += 2) {
    ///     // atts[i] is the attribute name.
    ///     // atts[i + 1] is the attribute value.
    /// }
    /// </code>
    /// </remarks>
    /// <param name="name">The name of the tag.</param>
    /// <param name="atts">An array of alternating attribute names and values.
    /// The array ends with a nullptr guard entry.< / param>
    virtual void on_start_element(const char_type *name,
        const char_type **atts);

private:

    /// <summary>
    /// Text callback.
    /// </summary>
    /// <param name="userData">Pointer to sax_parser instance.</param>
    /// <param name="s"></param>
    /// <param name="len"></param>
    static inline void XMLCALL characters(void *userData,
            const char_type *s, int len) {
        static_cast<sax_parser *>(userData)->on_characters(s, len);
    }

    /// <summary>
    /// End of tag callback.
    /// </summary>
    /// <param name="userData">Pointer to sax_parser instance.</param>
    /// <param name="name"></param>
    static inline void XMLCALL end_element(void *userData,
            const char_type *name) {
        static_cast<sax_parser *>(userData)->on_end_element(name);
    }

    /// <summary>
    /// Begin of tag callback.
    /// </summary>
    /// <param name="userData">Pointer to sax_parser instance.</param>
    /// <param name="name"></param>
    /// <param name="atts"></param>
    static inline void XMLCALL start_element(void *userData,
            const XML_Char *name, const XML_Char **atts) {
        static_cast<sax_parser *>(userData)->on_start_element(name, atts);
    }

    std::vector<byte_type> buffer;
    XML_Parser parser;
};

DPYCNF_DETAIL_NAMESPACE_END

#include "visus/vvand_config/sax_parser.inl"

#if defined(_WIN32) && defined(_MANAGED)
#pragma managed(pop)
#endif /* defined(_WIN32) && defined(_MANAGED) */
#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_SAX_PARSER_H) */
