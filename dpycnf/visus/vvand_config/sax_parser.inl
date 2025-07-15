// <copyright file="sax_parser.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2014 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>
/*
 * sax_parser.h
 *
 * Copyright (C) 2009 by Christoph Müller. Alle Rechte vorbehalten.
 */


/*
 * DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::sax_parser
 */
template<class TChar>
DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::sax_parser(const size_t bufferSize)
        : buffer(bufferSize) {
    this->parser = ::XML_ParserCreate(nullptr);
    ::XML_SetUserData(this->parser, this);
    ::XML_SetStartElementHandler(this->parser, sax_parser::start_element);
    ::XML_SetEndElementHandler(this->parser, sax_parser::end_element);
    ::XML_SetCharacterDataHandler(this->parser, sax_parser::characters);
}


/*
 * DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::~sax_parser
 */
template<class TChar>
DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::~sax_parser(void) noexcept {
    ::XML_ParserFree(this->parser);
}


/*
 * DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::parse_file
 */
template<class TChar>
void DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::parse_file(
        const string_type& path) {
    std::size_t bytesRead = 0;

    /* Sanity checks. */
    if (this->buffer.empty()) {
        this->buffer.resize(sax_parser::default_buffer_size);
    }

    /* Create a stream and make it throw on I/O errors. */
    std::ifstream stream;
    stream.exceptions(stream.exceptions() | std::ios::failbit);
    stream.open(xml_exception<TChar>::to_string(path.c_str()),
        std::ifstream::binary);
    stream.exceptions(stream.exceptions() & ~std::ios::failbit);

    /* Parse the file incrementally. */
    while (!stream.eof()) {
        stream.read(this->buffer.data(), this->buffer.size());
        auto status = ::XML_Parse(this->parser, buffer.data(),
            static_cast<int>(stream.gcount()), stream.eof());
        if (status == XML_STATUS_ERROR) {
            throw xml_exception<char_type>(::XML_GetErrorCode(this->parser),
                ::XML_GetErrorLineNumber(this->parser),
                ::XML_GetErrorColumnNumber(this->parser),
                __FILE__, __LINE__);
        }
    };
}


/*
 * DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::parse_text
 */
template<class TChar>
void DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::parse_text(
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
 * DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::are_strings_equal
 */
template<class TChar>
bool DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::are_strings_equal(
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
 * DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::on_characters
 */
template<class TChar>
void DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::on_characters(
        const char_type *s, const int len) {
    // Do nothing.
}


/*
 * DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::on_end_element
 */
template<class TChar>
void DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::on_end_element(
        const char_type *name) {
    // Do nothing.
}


/*
 * DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::on_start_element
 */
template<class TChar>
void DPYCNF_DETAIL_NAMESPACE::sax_parser<TChar>::on_start_element(
        const char_type *name, const char_type **atts) {
    // Do nothing.
}
