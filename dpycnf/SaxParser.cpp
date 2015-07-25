/// <copyright file="SaxParser.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2014 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>
/*
 * SaxParser.h
 *
 * Copyright (C) 2009 by Christoph Müller. Alle Rechte vorbehalten.
 */

#include "stdafx.h"
#include "SaxParser.h"

#include "XmlException.h"

#include <algorithm>
#include <system_error>


/*
 * SaxParser::DFT_BUFFER_SIZE
 */
const size_t SaxParser::DFT_BUFFER_SIZE = 4 * 1024;


/*
 * SaxParser::SaxParser
 */
SaxParser::SaxParser(const size_t bufferSize) : buffer(bufferSize) {
    this->parser = ::XML_ParserCreate(nullptr);
    ::XML_SetUserData(this->parser, this);
    ::XML_SetStartElementHandler(this->parser, startElement);
    ::XML_SetEndElementHandler(this->parser, endElement);
    ::XML_SetCharacterDataHandler(this->parser, characters);
}


/*
 * SaxParser::~SaxParser
 */
SaxParser::~SaxParser(void) {
    ::XML_ParserFree(this->parser);
}


/*
 * SaxParser::Parse
 */
void SaxParser::Parse(const StringType& path) {
    DWORD bytesRead = 0;

    /* Sanity checks. */
    if (this->buffer.empty()) {
        this->buffer.resize(SaxParser::DFT_BUFFER_SIZE);
    }

    // TODO: only works with unicode build
    auto hFile = ::CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ,
        nullptr, OPEN_EXISTING, 0, NULL);
    if (hFile == NULL) {
        auto e = ::GetLastError();
        auto ec = std::error_code(e, std::system_category());
        throw std::system_error(ec);
    }

    /* Parse the file incrementally. */
    do {
        if (!::ReadFile(hFile, this->buffer.data(),
                static_cast<DWORD>(this->buffer.size()), &bytesRead, nullptr)) {
            auto e = ::GetLastError();
            auto ec = std::error_code(e, std::system_category());
            throw std::system_error(ec);
        }
        auto status = ::XML_Parse(this->parser, buffer.data(),
            static_cast<int>(bytesRead), (bytesRead == 0));
        if (status == XML_STATUS_ERROR) {
            throw XmlException(::XML_GetErrorCode(this->parser),
                ::XML_GetErrorLineNumber(this->parser),
                ::XML_GetErrorColumnNumber(this->parser),
                __FILE__, __LINE__);
        }
    } while (bytesRead != 0);
}


/*
 * SaxParser::AreStringsEqual
 */
bool SaxParser::AreStringsEqual(const XML_Char *s1,
        const XML_Char *s2, const bool isCaseSensitive) {
    if (s1 == s2) {
        return true;

    } else {
        StringType l(s1);
        StringType r(s2);

        if (!isCaseSensitive) {
            std::transform(l.begin(), l.end(), l.begin(), ::tolower);
            std::transform(r.begin(), r.end(), r.begin(), ::tolower);
        }

        return (l == r);
    }
}


/*
 * SaxParser::OnCharacters
 */
void SaxParser::OnCharacters(const XML_Char *s, const int len) {
    // Do nothing.
}


/*
 * SaxParser::OnEndElement
 */
void SaxParser::OnEndElement(const XML_Char *name) {
    // Do nothing.
}


/*
 * SaxParser::OnStartElement
 */
void SaxParser::OnStartElement(const XML_Char *name, const XML_Char **atts) {
    // Do nothing.
}
