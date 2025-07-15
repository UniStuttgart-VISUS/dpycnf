// <copyright file="xml_exception.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2014 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>
/*
 * XmlException.cpp
 *
 * Copyright (C) 2009 by Christoph Müller. Alle Rechte vorbehalten.
 */


/*
 * DPYCNF_NAMESPACE::xml_exception<T>::xml_exception
 */
template<class TChar>
DPYCNF_NAMESPACE::xml_exception<TChar>::xml_exception(
        const error_type errorCode,
        const size_type xmlLine,
        const size_type xmlColumn,
        const char *file,
        const int line)
    : base(to_string(errorCode).c_str()),
        _error_code(errorCode),
        _file(file),
        _line(line),
        _xml_column(xmlColumn),
        _xml_line(xmlLine) { }


/*
 * DPYCNF_NAMESPACE::xml_exception<T>::xml_exception
 */
template<class TChar>
DPYCNF_NAMESPACE::xml_exception<TChar>::xml_exception(
        const char_type *customMsg,
        const size_type xmlLine,
        const size_type xmlColumn,
        const char *file,
        const int line)
    : base(to_string(customMsg).c_str()),
        _error_code(XML_ERROR_NONE),
        _file(file),
        _line(line),
        _xml_column(xmlColumn),
        _xml_line(xmlLine) { }
