/// <copyright file="xml_exception.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2014 - 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>
/*
 * XmlException.cpp
 *
 * Copyright (C) 2009 by Christoph Müller. Alle Rechte vorbehalten.
 */


/*
 * visus::vvand_config::xml_exception<T>::xml_exception
 */
template<class T>
visus::vvand_config::xml_exception<T>::xml_exception(const error_type errorCode,
        const size_type xmlLine, const size_type xmlColumn, const char *file,
        const int line)
    : base(to_string(errorCode).c_str()), _error_code(errorCode), _file(file),
        _line(line), _xml_column(xmlColumn), _xml_line(xmlLine) { }


/*
 * visus::vvand_config::xml_exception<T>::xml_exception
 */
template<class T>
visus::vvand_config::xml_exception<T>::xml_exception(const char_type *customMsg,
        const size_type xmlLine, const size_type xmlColumn, const char *file,
        const int line)
    : base(to_string(customMsg).c_str()), _error_code(XML_ERROR_NONE),
        _file(file), _line(line), _xml_column(xmlColumn), _xml_line(xmlLine) { }


/*
 * visus::vvand_config::xml_exception<T>::~xml_exception
 */
template<class T>
visus::vvand_config::xml_exception<T>::~xml_exception(void) { }
