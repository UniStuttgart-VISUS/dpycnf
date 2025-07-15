// <copyright file="vvand_config_parser.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2015 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::parse_file
 */
template<class TChar>
typename DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::configuration_type
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::parse_file(
        const string_type& path) {
    base::parse_file(path);
    return this->currentConfig;
}


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::parse_text
 */
template<class TChar>
typename DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::configuration_type
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::parse_text(
        const string_type& text) {
    base::parse_text(text);
    return this->currentConfig;
}


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::on_characters
 */
template<class TChar>
void DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::on_characters(
        const char_type *s, const int len) {
    this->cdata.append(s, len);
}


/*
 * visus::vvand_config:detail:::vvand_config_parser<T>::on_end_element
 */
template<class TChar>
void DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::on_end_element(
        const char_type *name) {
#define THROW_UNEXPECTED_TAG(tag)                                              \
    /*throw exception_type(_X("Closing tag \"") tag _X("\" is unexpected here."),*/\
    throw exception_type(DPYCNF_TPL_LITERAL(TChar, "Closing tag is unexpected here."),\
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

    } else if (base::are_strings_equal(name, tag_window_left, false)) {
        if (this->currentScope == scope::tile) {
            if (this->currentTile._position == nullptr) {
                this->currentTile._position = new offset(0, 0);
            }
            this->currentTile._position->left = std::stoi(this->cdata);
        }

    } else if (base::are_strings_equal(name, tag_window_top, false)) {
        if (this->currentScope == scope::tile) {
            if (this->currentTile._position == nullptr) {
                this->currentTile._position = new offset(0, 0);
            }
            this->currentTile._position->top = std::stoi(this->cdata);
        }

    }

#undef THROW_UNEXPECTED_TAG
}


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::on_start_element
 */
template<class TChar>
void DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::on_start_element(
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
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_height
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_height
= DPYCNF_XML_LITERAL("Height");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_left_offset
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_left_offset
= DPYCNF_XML_LITERAL("LeftOffset");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_identity
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_identity
= DPYCNF_XML_LITERAL("Identity");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_machine
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_machine
= DPYCNF_XML_LITERAL("Machine");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_machines
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_machines
= DPYCNF_XML_LITERAL("Machines");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_name
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_name
= DPYCNF_XML_LITERAL("Name");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_stereo_channel
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_stereo_channel
= DPYCNF_XML_LITERAL("StereoChannel");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_tile
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_tile
= DPYCNF_XML_LITERAL("Tile");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_tiled_display
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_tiled_display
= DPYCNF_XML_LITERAL("TiledDisplay");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_tiles
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_tiles
= DPYCNF_XML_LITERAL("Tiles");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_top_offset
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_top_offset
= DPYCNF_XML_LITERAL("TopOffset");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_width
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_width
= DPYCNF_XML_LITERAL("Width");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_window_height
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_window_height
= DPYCNF_XML_LITERAL("WindowHeight");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_window_width
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_window_width
= DPYCNF_XML_LITERAL("WindowWidth");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_window_left
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_window_left
= DPYCNF_XML_LITERAL("WindowLeft");


/*
 * DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<T>::tag_window_top
 */
template<class TChar> const XML_Char *
DPYCNF_DETAIL_NAMESPACE::vvand_config_parser<TChar>::tag_window_top
= DPYCNF_XML_LITERAL("WindowTop");
