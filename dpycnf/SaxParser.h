/// <copyright file="SaxParser.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2014 - 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>
/*
 * SaxParser.h
 *
 * Copyright (C) 2009 by Christoph Müller. Alle Rechte vorbehalten.
 */

#ifndef SAXPARSER_H_INCLUDED
#define SAXPARSER_H_INCLUDED
#if (defined(_MSC_VER) && (_MSC_VER > 1000))
#pragma once
#endif /* (defined(_MSC_VER) && (_MSC_VER > 1000)) */
#if defined(_WIN32) && defined(_MANAGED)
#pragma managed(push, off)
#endif /* defined(_WIN32) && defined(_MANAGED) */

#include "expat.h"

#include <cinttypes>
#include <string>
#include <vector>


/// <summary>
/// This is the super class for SAX XML parsers. It wraps the expat library.
/// Special parsers should inherit from this class and implement the On*()
/// event handler methods as appropriate.
/// </summary>
class SaxParser {

public:

    /// <summary>
    /// The type of strings that the parser processes.
    /// </summary>
    typedef std::basic_string<XML_Char> StringType;

    /// <summary>
    /// Default size of the read buffer.
    /// </summary>
    static const size_t DFT_BUFFER_SIZE;

    /**
     * Create a new parser with the specified read buffer size.
     *
     * Note that a parser that parses from a file needs a non-zero read 
     * buffer.
     *
     * @param bufferSize The size of the read buffer that is allocated.
     *
     * @throws std::bad_alloc If the buffer could not be allocated.
     */

    /// <summary>
    /// </summary>
    SaxParser(const size_t bufferSize = DFT_BUFFER_SIZE);

    /// <summary>
    /// Dtor.
    /// </summary>
    virtual ~SaxParser(void);

    /**
     * Parse XML from the open file 'file'. The parser starts at the current
     * position in the file. The file must be open. The parser will parse
     * until the end of the file was reached. The parser will NOT close the
     * file afterwards.
     *
     * @param file An open file.
     *
     * @throws vislib::IllegalStateException If the parser has been created
     *                                       without a read buffer, i. e.
     *                                       ('bufferSize' == 0).
     * @throws vislib::sys::SystemException  If reading from 'file' failed.
     * @throws XmlException                  If an XML syntax error was found.
     */

    /// <summary>
    /// </summary>
    void Parse(const StringType& path);

protected:

    /// <summary>
    /// Helper for comparing two XML strings for equality.
    /// </summary>
    /// <param name="s1">The first string.</param>
    /// <param name="s2">The second string.</param>
    /// <param name="isCaseSensitve">witch between case-sensitive and 
    /// case-insensitive compare.</param>
    /// <returns>true if 's1' and 's2' are equal.</returns>
    static bool AreStringsEqual(const XML_Char *s1,
        const XML_Char *s2, const bool isCaseSensitive = true);

    /// <summary>
    /// Gets the number of the column the parser is currently processing.
    /// </summary>
    /// <returns></returns>
    inline XML_Size GetCurrentColumnNumber(void) const {
        return ::XML_GetCurrentColumnNumber(this->parser);
    }

    /// <summary>
    /// Gets the number of the line the parser is currently processing.
    /// </summary>
    /// <returns></returns>
    inline XML_Size GetCurrentLineNumber(void) const {
        return ::XML_GetCurrentLineNumber(this->parser);
    }

    /// <summary>
    /// Overwrite this method to process text between tags.
    /// </summary>
    /// <param name="s"> Pointer to <paramref name="len" /> characters.</param>
    /// <param name="len">The number of characters starting at
    /// <paramref name="s" />.</returns>
    virtual void OnCharacters(const XML_Char *s, const int len);

    /// <summary>
    /// Overwrite this method to process closing tags.
    /// </summary>
    /// <param name="name">The name of the tag.</param>
    virtual void OnEndElement(const XML_Char *name);

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
    virtual void OnStartElement(const XML_Char *name,
        const XML_Char **atts);

private:

    /// <summary>
    /// Text callback.
    /// </summary>
    /// <param name="userData">Pointer to SaxParser instance.</param>
    /// <param name="s"></param>
    /// <param name="len"></param>
    static inline void XMLCALL characters(void *userData, const XML_Char *s,
            int len) {
        static_cast<SaxParser *>(userData)->OnCharacters(s, len);
    }

    /// <summary>
    /// End of tag callback.
    /// </summary>
    /// <param name="userData">Pointer to SaxParser instance.</param>
    /// <param name="name"></param>
    static inline void XMLCALL endElement(void *userData,
            const XML_Char *name) {
        static_cast<SaxParser *>(userData)->OnEndElement(name);
    }

    /// <summary>
    /// Begin of tag callback.
    /// </summary>
    /// <param name="userData">Pointer to SaxParser instance.</param>
    /// <param name="name"></param>
    /// <param name="atts"></param>
    static inline void XMLCALL startElement(void *userData,
            const XML_Char *name, const XML_Char **atts) {
        static_cast<SaxParser *>(userData)->OnStartElement(name, atts);
    }

    /// <summary>
    /// Input buffer for parsing from a file.
    /// </summary>
    std::vector<char> buffer;

    /// <summary>
    /// The Expat XML parser.
    /// </summary>
    XML_Parser parser;
};

#if defined(_WIN32) && defined(_MANAGED)
#pragma managed(pop)
#endif /* defined(_WIN32) && defined(_MANAGED) */
#endif /* SAXPARSER_H_INCLUDED */
