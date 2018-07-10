/// <copyright file="vvand_config_parser.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 - 2018 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include "visus/vvand_config/display_configuration.h"
#include "visus/vvand_config/sax_parser.h"


namespace visus {
namespace vvand_config {
namespace detail {

    /// <summary>
    /// Parser for the original VISUS Vvand configuration file.
    /// </summary>
    template<class T> class vvand_config_parser : public sax_parser<T> {

        typedef sax_parser<T> base;

    public:

        typedef base::byte_type byte_type;
        typedef display_configuration<T> configuration_type;
        typedef base::char_type char_type;
        typedef base::exception_type exception_type;
        typedef machine<T> machine_type;
        typedef base::size_type size_type;
        typedef base::string_type string_type;
        typedef tile<T> tile_type;

        vvand_config_parser(void);

        virtual ~vvand_config_parser(void);

        configuration_type parse_file(const string_type& path);

        configuration_type parse_text(const string_type& text);

    protected:

        virtual void on_characters(const char_type *s, const int len);

        virtual void on_end_element(const char_type *name);

        virtual void on_start_element(const char_type *name,
            const char_type **atts);

    private:

        enum class scope {
            unknown,
            tiled_display,
            machines,
            machine,
            tiles,
            tile
        };

        string_type cdata;
        configuration_type currentConfig;
        machine_type currentMachine;
        scope currentScope;
        tile_type currentTile;
    };

} /* end namespace detail */
} /* end namespace vvand_config */
} /* end namespace visus */

#include "visus/vvand_config/vvand_config_parser.inl"
