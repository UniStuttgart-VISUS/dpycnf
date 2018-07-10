/// <copyright file="sax_parser.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2014 - 2018 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>
/*
 * sax_parser.h
 *
 * Copyright (C) 2009 by Christoph Müller. Alle Rechte vorbehalten.
 */


/*
 * visus::vvand_config::detail::sax_parser<T>::sax_parser
 */
template<class T>
visus::vvand_config::detail::sax_parser<T>::sax_parser(const size_t bufferSize)
        : buffer(bufferSize) {
    this->parser = ::XML_ParserCreate(nullptr);
    ::XML_SetUserData(this->parser, this);
    ::XML_SetStartElementHandler(this->parser, sax_parser::start_element);
    ::XML_SetEndElementHandler(this->parser, sax_parser::end_element);
    ::XML_SetCharacterDataHandler(this->parser, sax_parser::characters);
}


/*
 * visus::vvand_config::detail::sax_parser<T>::~sax_parser
 */
template<class T>
visus::vvand_config::detail::sax_parser<T>::~sax_parser(void) {
    ::XML_ParserFree(this->parser);
}


/*
 * visus::vvand_config::detail::sax_parser<T>::parse_file
 */
template<class T>
void visus::vvand_config::detail::sax_parser<T>::parse_file(
        const string_type& path) {
    DWORD bytesRead = 0;

    /* Sanity checks. */
    if (this->buffer.empty()) {
        this->buffer.resize(sax_parser::default_buffer_size);
    }

    // TODO: only works with ASCII build
    auto hFile = ::CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ,
        nullptr, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
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
            throw xml_exception<char_type>(::XML_GetErrorCode(this->parser),
                ::XML_GetErrorLineNumber(this->parser),
                ::XML_GetErrorColumnNumber(this->parser),
                __FILE__, __LINE__);
        }
    } while (bytesRead != 0);
}


/*
 * visus::vvand_config::detail::sax_parser<T>::parse_text
 */
template<class T>
void visus::vvand_config::detail::sax_parser<T>::parse_text(
        const string_type& text) {
    auto status = ::XML_Parse(this->parser,
        reinterpret_cast<const byte_type *>(text.c_str()),
        static_cast<int>(text.size() * sizeof(char_type)), 1);
    if (status == XML_STATUS_ERROR) {
        throw xml_exception<char_type>(::XML_GetErrorCode(this->parser),
            ::XML_GetErrorLineNumber(this->parser),
            ::XML_GetErrorColumnNumber(this->parser),
            __FILE__, __LINE__);
    }
}


/*
 * visus::vvand_config::detail::sax_parser<T>::are_strings_equal
 */
template<class T>
bool visus::vvand_config::detail::sax_parser<T>::are_strings_equal(
        const char_type *s1, const char_type *s2, const bool isCaseSensitive) {
    if (s1 == s2) {
        return true;

    } else {
        string_type l(s1);
        string_type r(s2);

        if (!isCaseSensitive) {
            std::transform(l.begin(), l.end(), l.begin(), ::tolower);
            std::transform(r.begin(), r.end(), r.begin(), ::tolower);
        }

        return (l == r);
    }
}


/*
 * visus::vvand_config::detail::sax_parser<T>::on_characters
 */
template<class T>
void visus::vvand_config::detail::sax_parser<T>::on_characters(
        const char_type *s, const int len) {
    // Do nothing.
}


/*
 * visus::vvand_config::detail::sax_parser<T>::on_end_element
 */
template<class T>
void visus::vvand_config::detail::sax_parser<T>::on_end_element(
        const char_type *name) {
    // Do nothing.
}


/*
 * visus::vvand_config::detail::sax_parser<T>::on_start_element
 */
template<class T>
void visus::vvand_config::detail::sax_parser<T>::on_start_element(
        const char_type *name, const char_type **atts) {
    // Do nothing.
}
