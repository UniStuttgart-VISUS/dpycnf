// <copyright file="vvand_config_parser.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2015 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


#if !defined(_DPYCNF_VISUS_VVAND_CONFIG_VVAND_CONFIG_PARSER_H)
#define _DPYCNF_VISUS_VVAND_CONFIG_VVAND_CONFIG_PARSER_H
#pragma once

#include "visus/vvand_config/display_configuration.h"
#include "visus/vvand_config/literal.h"
#include "visus/vvand_config/sax_parser.h"


DPYCNF_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Parser for the original VISUS Vvand configuration file.
/// </summary>
template<class TChar> class vvand_config_parser : public sax_parser<TChar> {

    typedef sax_parser<TChar> base;

public:

    typedef typename base::byte_type byte_type;
    typedef display_configuration<TChar> configuration_type;
    typedef typename base::char_type char_type;
    typedef typename base::exception_type exception_type;
    typedef machine<TChar> machine_type;
    typedef typename base::size_type size_type;
    typedef typename base::string_type string_type;
    typedef tile<TChar> tile_type;

    vvand_config_parser(void) = default;

    virtual ~vvand_config_parser(void) = default;

    configuration_type parse_file(const string_type& path);

    configuration_type parse_text(const string_type& text);

protected:

    void on_characters(const char_type *s, const int len) override;

    void on_end_element(const char_type *name) override;

    void on_start_element(const char_type *name,
        const char_type **atts) override;

private:

    enum class scope {
        unknown,
        tiled_display,
        machines,
        machine,
        tiles,
        tile
    };

    static const XML_Char *tag_height;
    static const XML_Char *tag_left_offset;
    static const XML_Char *tag_identity;
    static const XML_Char *tag_machine;
    static const XML_Char *tag_machines;
    static const XML_Char *tag_name;
    static const XML_Char *tag_stereo_channel;
    static const XML_Char *tag_tile;
    static const XML_Char *tag_tiled_display;
    static const XML_Char *tag_tiles;
    static const XML_Char *tag_top_offset;
    static const XML_Char *tag_width;
    static const XML_Char *tag_window_width;
    static const XML_Char *tag_window_height;
    static const XML_Char *tag_window_left;
    static const XML_Char *tag_window_top;

    string_type cdata;
    configuration_type currentConfig;
    machine_type currentMachine;
    scope currentScope;
    tile_type currentTile;
};

DPYCNF_DETAIL_NAMESPACE_END

#include "visus/vvand_config/vvand_config_parser.inl"

#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_VVAND_CONFIG_PARSER_H) */
