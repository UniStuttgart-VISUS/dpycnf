/// <copyright file="XmlException.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2014 - 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>
/*
 * XmlException.h
 *
 * Copyright (C) 2009 by Christoph Müller. Alle Rechte vorbehalten.
 */

#ifndef XMLEXCEPTION_H_INCLUDED
#define XMLEXCEPTION_H_INCLUDED
#if (defined(_MSC_VER) && (_MSC_VER > 1000))
#pragma once
#endif /* (defined(_MSC_VER) && (_MSC_VER > 1000)) */
#if defined(_WIN32) && defined(_MANAGED)
#pragma managed(push, off)
#endif /* defined(_WIN32) && defined(_MANAGED) */

#include "expat.h"

#include <string>
#include <stdexcept>


/// <summary>
/// This exception represents an XML parsing error.
/// </summary>
class XmlException : public std::exception {

public:

    /// <summary>
    /// Create a new exception that represents the Expat error
    /// <paramref name="errorCode" />.
    /// </summary>
    XmlException(const XML_Error errorCode, const XML_Size xmlLine,
        const XML_Size xmlColumn, const char *file, const int line);

    /// <summary>
    /// Create a new exception with a custom error message.
    /// </summary>
    XmlException(const XML_Char *customMsg, const XML_Size xmlLine,
        const XML_Size xmlColumn, const char *file, const int line);

    /// <summary>
    /// Dtor.
    /// </summary>
    virtual ~XmlException(void);

    /// <summary>
    /// </summary>
    inline XML_Error GetErrorCode(void) const {
        return this->errorCode;
    }

    /// <summary>
    /// </summary>
    inline const char *GetErrorMessage(void) const {
        return this->what();
    }

    /// <summary>
    /// </summary>
    inline const std::string& GetFile(void) const {
        return this->file;
    }

    /// <summary>
    /// </summary>
    inline int GetLine(void) const {
        return this->line;
    }

    /// <summary>
    /// </summary>
    inline XML_Size GetXmlColumn(void) const {
        return this->xmlColumn;
    }

    /// <summary>
    /// </summary>
    inline XML_Size GetXmlLine(void) const {
        return this->xmlLine;
    }

private:

    /// <summary>
    /// Base class type.
    /// </summary>
    typedef std::exception Base;

    /// <summary>
    /// Gets a string description for an Expat error code.
    /// </summary>
    static inline std::string toString(const XML_Error errorCode) {
        return XmlException::toString(::XML_ErrorString(errorCode));
    }

    /// <summary>
    /// Gets an std::string for an Expat string.
    /// </summary>
    static std::string toString(const XML_Char *errorMsg);

    /// <summary>
    /// The XML error code.
    /// </summary>
    XML_Error errorCode;

    /// <summary>
    /// The file in which the exception ocurred.
    /// </summary>
    std::string file;

    /// <summary>
    /// The line in which the exception ocurred.
    /// </summary>
    int line;

    /// <summary>
    /// The column the error occurred in.
    /// </summary>
    XML_Size xmlColumn;

    /// <summary>
    /// The line the error occurred in.
    /// </summary>
    XML_Size xmlLine;

};

#if defined(_WIN32) && defined(_MANAGED)
#pragma managed(pop)
#endif /* defined(_WIN32) && defined(_MANAGED) */
#endif /* XMLEXCEPTION_H_INCLUDED */
