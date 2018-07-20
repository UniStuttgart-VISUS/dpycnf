/// <copyright file="vvand_config_parser.inl" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 - 2018 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::vvand_config_parser
 */
template<class T>
visus::vvand_config::detail::vvand_config_parser<T>::vvand_config_parser(
    void) { }


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::~vvand_config_parser
 */
template<class T>
visus::vvand_config::detail::vvand_config_parser<T>::~vvand_config_parser(
    void) { }


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::parse_file
 */
template<class T>
typename visus::vvand_config::detail::vvand_config_parser<T>::configuration_type
visus::vvand_config::detail::vvand_config_parser<T>::parse_file(
        const string_type& path) {
    base::parse_file(path);
    return this->currentConfig;
}


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::parse_text
 */
template<class T>
typename visus::vvand_config::detail::vvand_config_parser<T>::configuration_type
visus::vvand_config::detail::vvand_config_parser<T>::parse_text(
        const string_type& text) {
    base::parse_text(text);
    return this->currentConfig;
}


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::on_characters
 */
template<class T>
void visus::vvand_config::detail::vvand_config_parser<T>::on_characters(
        const char_type *s, const int len) {
    this->cdata.append(s, len);
}


/*
 * visus::vvand_config:detail:::vvand_config_parser<T>::on_end_element
 */
template<class T>
void visus::vvand_config::detail::vvand_config_parser<T>::on_end_element(
        const char_type *name) {
#define THROW_UNEXPECTED_TAG(tag)                                              \
    /*throw exception_type(_X("Closing tag \"") tag _X("\" is unexpected here."),*/\
    throw exception_type(DPYCNF_TPL_LITERAL(T, "Closing tag is unexpected here."),\
        this->current_line_number(), this->current_column_number(),            \
        __FILE__, __LINE__)


    if (base::are_strings_equal(name, tag_tiled_display, false)) {
        if (this->currentScope == scope::tiled_display) {
            this->currentScope = scope::unknown;
        } else {
            THROW_UNEXPECTED_TAG(tag_tiled_display);
        }

    } else if (base::are_strings_equal(name, tag_machines, false)) {
        if (this->currentScope == scope::machines) {
            this->currentScope = scope::tiled_display;
        } else {
            THROW_UNEXPECTED_TAG(tag_machines);
        }

    } else if (base::are_strings_equal(name, tag_machine, false)) {
        if (this->currentScope == scope::machine) {
            this->currentScope = scope::machines;
            this->currentConfig._machines.push_back(this->currentMachine);
        } else {
            THROW_UNEXPECTED_TAG(tag_machine);
        }

    } else if (base::are_strings_equal(name, tag_identity, false)) {
        if (this->currentScope == scope::machine) {
            this->currentMachine._identity = this->cdata;
        } else {
            THROW_UNEXPECTED_TAG(tag_identity);
        }

    } else if (base::are_strings_equal(name, tag_tiles, false)) {
        if (this->currentScope == scope::tiles) {
            this->currentScope = scope::machine;
        } else {
            THROW_UNEXPECTED_TAG(tag_tiles);
        }

    } else if (base::are_strings_equal(name, tag_tile, false)) {
        if (this->currentScope == scope::tile) {
            this->currentScope = scope::tiles;
            this->currentMachine._tiles.push_back(this->currentTile);
        } else {
            THROW_UNEXPECTED_TAG(tag_tile);
        }

    } else if (base::are_strings_equal(name, tag_left_offset, false)) {
        if (this->currentScope == scope::tile) {
            int tmp = std::stoi(this->cdata);
            //this->currentTile.offset.Left = std::min<int>(tmp,
            //    this->currentTile.offset.Left);
            this->currentTile._offset.left = tmp;
        }

    } else if (base::are_strings_equal(name, tag_top_offset, false)) {
        if (this->currentScope == scope::tile) {
            int tmp = std::stoi(this->cdata);
            //this->currentTile.offset.Top = std::min<int>(tmp, 
            //    this->currentTile.offset.Top);
            this->currentTile._offset.top = tmp;
        }

    } else if (base::are_strings_equal(name, tag_window_width, false)) {
        if (this->currentScope == scope::tile) {
            auto tmp = std::stoi(this->cdata);
            this->currentTile._size.width = std::max<int>(tmp, 0);
        }

    } else if (base::are_strings_equal(name, tag_window_height, false)) {
        if (this->currentScope == scope::tile) {
            auto tmp = std::stoi(this->cdata);
            this->currentTile._size.height = std::max<int>(tmp, 0);
        }


    } else if (base::are_strings_equal(name, tag_stereo_channel, false)) {
        if (base::are_strings_equal(this->cdata.c_str(),
                DPYCNF_XML_LITERAL("right"), false)) {
            this->currentTile._channel = stereo_channel::right;

        } else if (base::are_strings_equal(this->cdata.c_str(), 
                DPYCNF_XML_LITERAL("left"), false)) {
            this->currentTile._channel = stereo_channel::left;

        } else {
            this->currentTile._channel = stereo_channel::mono;
        }

    } else if (base::are_strings_equal(name, tag_width, false)) {
        if (this->currentScope == scope::tiled_display) {
            int tmp = std::stoi(this->cdata);
            this->currentConfig._size.width = std::max<int>(tmp, 0);
        }

    } else if (base::are_strings_equal(name, tag_height, false)) {
        if (this->currentScope == scope::tiled_display) {
            int tmp = std::stoi(this->cdata);
            this->currentConfig._size.height = std::max<int>(tmp, 0);
        }

    } else if (base::are_strings_equal(name, tag_name, false)) {
        if (this->currentScope == scope::tile) {
            this->currentTile._name = this->cdata;
        } else if (this->currentScope == scope::tiled_display) {
            this->currentConfig._name = this->cdata;
        }

    }

#undef THROW_UNEXPECTED_TAG
}


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::on_start_element
 */
template<class T>
void visus::vvand_config::detail::vvand_config_parser<T>::on_start_element(
        const char_type *name, const char_type **atts) {
    // Clear old CDATA
    this->cdata.clear();

    if (base::are_strings_equal(name, tag_tiled_display, false)) {
        this->currentScope = scope::tiled_display;
        this->currentConfig = configuration_type();

    } else if (base::are_strings_equal(name, tag_machines, false)) {
        this->currentScope = scope::machines;

    } else if (base::are_strings_equal(name, tag_machine, false)) {
        this->currentScope = scope::machine;
        this->currentMachine = machine_type();

    } else if (base::are_strings_equal(name, tag_identity, false)) {
        // Nothing to do

    } else if (base::are_strings_equal(name, tag_tiles, false)) {
        this->currentScope = scope::tiles;

    } else if (base::are_strings_equal(name, tag_tile, false)) {
        this->currentScope = scope::tile;
        this->currentTile = tile_type();

    } else if (base::are_strings_equal(name, tag_left_offset, false)) {
        // Nothing to do.

    } else if (base::are_strings_equal(name, tag_top_offset, false)) {
        // Nothing to do.

    } else if (base::are_strings_equal(name, tag_window_width, false)) {
        // Nothing to do.

    } else if (base::are_strings_equal(name, tag_window_height, false)) {
        // Nothing to do.

    } else if (base::are_strings_equal(name, tag_stereo_channel, false)) {
        // Nothing to do.

    } else if (base::are_strings_equal(name, tag_width, false)) {
        // Nothing to do.

    } else if (base::are_strings_equal(name, tag_height, false)) {
        // Nothing to do.

    } else if (base::are_strings_equal(name, tag_name, false)) {
        // Nothing to do.

    }
}


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::tag_height
 */
template<class T> const XML_Char *
visus::vvand_config::detail::vvand_config_parser<T>::tag_height
= DPYCNF_XML_LITERAL("Height");


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::tag_left_offset
 */
template<class T> const XML_Char *
visus::vvand_config::detail::vvand_config_parser<T>::tag_left_offset
= DPYCNF_XML_LITERAL("LeftOffset");


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::tag_identity
 */
template<class T> const XML_Char *
visus::vvand_config::detail::vvand_config_parser<T>::tag_identity
= DPYCNF_XML_LITERAL("Identity");


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::tag_machine
 */
template<class T> const XML_Char *
visus::vvand_config::detail::vvand_config_parser<T>::tag_machine
= DPYCNF_XML_LITERAL("Machine");


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::tag_machines
 */
template<class T> const XML_Char *
visus::vvand_config::detail::vvand_config_parser<T>::tag_machines
= DPYCNF_XML_LITERAL("Machines");


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::tag_name
 */
template<class T> const XML_Char *
visus::vvand_config::detail::vvand_config_parser<T>::tag_name
= DPYCNF_XML_LITERAL("Name");


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::tag_stereo_channel
 */
template<class T> const XML_Char *
visus::vvand_config::detail::vvand_config_parser<T>::tag_stereo_channel
= DPYCNF_XML_LITERAL("StereoChannel");


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::tag_tile
 */
template<class T> const XML_Char *
visus::vvand_config::detail::vvand_config_parser<T>::tag_tile
= DPYCNF_XML_LITERAL("Tile");


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::tag_tiled_display
 */
template<class T> const XML_Char *
visus::vvand_config::detail::vvand_config_parser<T>::tag_tiled_display
= DPYCNF_XML_LITERAL("TiledDisplay");


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::tag_tiles
 */
template<class T> const XML_Char *
visus::vvand_config::detail::vvand_config_parser<T>::tag_tiles
= DPYCNF_XML_LITERAL("Tiles");


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::tag_top_offset
 */
template<class T> const XML_Char *
visus::vvand_config::detail::vvand_config_parser<T>::tag_top_offset
= DPYCNF_XML_LITERAL("TopOffset");


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::tag_width
 */
template<class T> const XML_Char *
visus::vvand_config::detail::vvand_config_parser<T>::tag_width
= DPYCNF_XML_LITERAL("Width");


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::tag_window_height
 */
template<class T> const XML_Char *
visus::vvand_config::detail::vvand_config_parser<T>::tag_window_height
= DPYCNF_XML_LITERAL("WindowHeight");


/*
 * visus::vvand_config::detail::vvand_config_parser<T>::tag_window_width
 */
template<class T> const XML_Char *
visus::vvand_config::detail::vvand_config_parser<T>::tag_window_width
= DPYCNF_XML_LITERAL("WindowWidth");
