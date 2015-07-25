/// <copyright file="XmlException.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2014 - 2015 Christoph M�ller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>
/*
 * XmlException.cpp
 *
 * Copyright (C) 2009 by Christoph M�ller. Alle Rechte vorbehalten.
 */

#include "stdafx.h"
#include "XmlException.h"

#include <codecvt>
#include <string>


/*
 * XmlException::XmlException
 */
XmlException::XmlException(const XML_Error errorCode,
        const XML_Size xmlLine, const XML_Size xmlColumn, const char *file,
        const int line)
    : Base(toString(errorCode).c_str()), errorCode(errorCode), file(file),
    line(line), xmlColumn(xmlColumn), xmlLine(xmlLine) { }


/*
 * XmlException::XmlException
 */
XmlException::XmlException(const XML_Char *customMsg, const XML_Size xmlLine,
        const XML_Size xmlColumn, const char *file, const int line)
    : Base(toString(customMsg).c_str()), errorCode(XML_ERROR_NONE), file(file),
        line(line), xmlColumn(xmlColumn), xmlLine(xmlLine) { }


/*
 * XmlException::~XmlException
 */
XmlException::~XmlException(void) { }


/*
 * XmlException::toString
 */
std::string XmlException::toString(const XML_Char *errorMsg) {
#ifdef XML_UNICODE
    typedef std::codecvt_utf8<XML_Char> ConverterType;
    typedef std::basic_string<XML_Char> StringType;
    std::wstring_convert<ConverterType, XML_Char> converter;
    return converter.to_bytes(StringType(errorMsg));
#else /* XML_UNICODE */
    return errorMsg;
#endif /* XML_UNICODE */
}
