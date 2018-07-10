/// <copyright file="vvand_config_parser.inl" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 - 2018 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>


#ifdef XML_UNICODE
#define _X(s) L##s
#else /* XML_UNICODE */
#define _X(s) s
#endif /* XML_UNICODE */

#define _XML_TAG_TILEDDISPLAY _X("TiledDisplay")
#define _XML_TAG_MACHINES _X("Machines")
#define _XML_TAG_MACHINE _X("Machine")
#define _XML_TAG_IDENTITY _X("Identity")
#define _XML_TAG_TILES _X("Tiles")
#define _XML_TAG_TILE _X("Tile")
#define _XML_TAG_LEFTOFFSET _X("LeftOffset")
#define _XML_TAG_TOPOFFSET _X("TopOffset")
#define _XML_TAG_WINDOWWIDTH _X("WindowWidth")
#define _XML_TAG_WINDOWHEIGHT _X("WindowHeight")
#define _XML_TAG_STEREOCHANNEL _X("StereoChannel")
#define _XML_TAG_WIDTH _X("Width")
#define _XML_TAG_HEIGHT _X("Height")
#define _XML_TAG_NAME _X("Name")


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
    throw exception_type(_X("Closing tag \"") tag _X("\" is unexpected here."),\
        this->current_line_number(), this->current_column_number(),            \
        __FILE__, __LINE__)


    if (base::are_strings_equal(name, _XML_TAG_TILEDDISPLAY, false)) {
        if (this->currentScope == scope::tiled_display) {
            this->currentScope = scope::unknown;
        } else {
            THROW_UNEXPECTED_TAG(_XML_TAG_TILEDDISPLAY);
        }

    } else if (base::are_strings_equal(name, _XML_TAG_MACHINES, false)) {
        if (this->currentScope == scope::machines) {
            this->currentScope = scope::tiled_display;
        } else {
            THROW_UNEXPECTED_TAG(_XML_TAG_MACHINES);
        }

    } else if (base::are_strings_equal(name, _XML_TAG_MACHINE, false)) {
        if (this->currentScope == scope::machine) {
            this->currentScope = scope::machines;
            this->currentConfig._machines.push_back(this->currentMachine);
        } else {
            THROW_UNEXPECTED_TAG(_XML_TAG_MACHINE);
        }

    } else if (base::are_strings_equal(name, _XML_TAG_IDENTITY, false)) {
        if (this->currentScope == scope::machine) {
            this->currentMachine._identity = this->cdata;
        } else {
            THROW_UNEXPECTED_TAG(_XML_TAG_IDENTITY);
        }

    } else if (base::are_strings_equal(name, _XML_TAG_TILES, false)) {
        if (this->currentScope == scope::tiles) {
            this->currentScope = scope::machine;
        } else {
            THROW_UNEXPECTED_TAG(_XML_TAG_TILES);
        }

    } else if (base::are_strings_equal(name, _XML_TAG_TILE, false)) {
        if (this->currentScope == scope::tile) {
            this->currentScope = scope::tiles;
            this->currentMachine._tiles.push_back(this->currentTile);
        } else {
            THROW_UNEXPECTED_TAG(_XML_TAG_TILE);
        }

    } else if (base::are_strings_equal(name, _XML_TAG_LEFTOFFSET, false)) {
        if (this->currentScope == scope::tile) {
            int tmp = std::stoi(this->cdata);
            //this->currentTile.offset.Left = std::min<int>(tmp,
            //    this->currentTile.offset.Left);
            this->currentTile._offset.left = tmp;
        }

    } else if (base::are_strings_equal(name, _XML_TAG_TOPOFFSET, false)) {
        if (this->currentScope == scope::tile) {
            int tmp = std::stoi(this->cdata);
            //this->currentTile.offset.Top = std::min<int>(tmp, 
            //    this->currentTile.offset.Top);
            this->currentTile._offset.top = tmp;
        }

    } else if (base::are_strings_equal(name, _XML_TAG_WINDOWWIDTH, false)) {
        if (this->currentScope == scope::tile) {
            auto tmp = std::stoi(this->cdata);
            this->currentTile._size.width = std::max<int>(tmp, 0);
        }

    } else if (base::are_strings_equal(name, _XML_TAG_WINDOWHEIGHT, false)) {
        if (this->currentScope == scope::tile) {
            auto tmp = std::stoi(this->cdata);
            this->currentTile._size.height = std::max<int>(tmp, 0);
        }


    } else if (base::are_strings_equal(name, _XML_TAG_STEREOCHANNEL, false)) {
        if (base::are_strings_equal(this->cdata.c_str(), _X("right"), false)) {
            this->currentTile._channel = stereo_channel::right;

        } else if (base::are_strings_equal(this->cdata.c_str(), _X("left"),
                false)) {
            this->currentTile._channel = stereo_channel::left;

        } else {
            this->currentTile._channel = stereo_channel::mono;
        }

    } else if (base::are_strings_equal(name, _XML_TAG_WIDTH, false)) {
        if (this->currentScope == scope::tiled_display) {
            int tmp = std::stoi(this->cdata);
            this->currentConfig._size.width = std::max<int>(tmp, 0);
        }

    } else if (base::are_strings_equal(name, _XML_TAG_HEIGHT, false)) {
        if (this->currentScope == scope::tiled_display) {
            int tmp = std::stoi(this->cdata);
            this->currentConfig._size.height = std::max<int>(tmp, 0);
        }

    } else if (base::are_strings_equal(name, _XML_TAG_NAME, false)) {
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

    if (base::are_strings_equal(name, _XML_TAG_TILEDDISPLAY, false)) {
        this->currentScope = scope::tiled_display;
        this->currentConfig = configuration_type();

    } else if (base::are_strings_equal(name, _XML_TAG_MACHINES, false)) {
        this->currentScope = scope::machines;

    } else if (base::are_strings_equal(name, _XML_TAG_MACHINE, false)) {
        this->currentScope = scope::machine;
        this->currentMachine = machine_type();

    } else if (base::are_strings_equal(name, _XML_TAG_IDENTITY, false)) {
        // Nothing to do

    } else if (base::are_strings_equal(name, _XML_TAG_TILES, false)) {
        this->currentScope = scope::tiles;

    } else if (base::are_strings_equal(name, _XML_TAG_TILE, false)) {
        this->currentScope = scope::tile;
        this->currentTile = tile_type();

    } else if (base::are_strings_equal(name, _XML_TAG_LEFTOFFSET, false)) {
        // Nothing to do.

    } else if (base::are_strings_equal(name, _XML_TAG_TOPOFFSET, false)) {
        // Nothing to do.

    } else if (base::are_strings_equal(name, _XML_TAG_WINDOWWIDTH, false)) {
        // Nothing to do.

    } else if (base::are_strings_equal(name, _XML_TAG_WINDOWHEIGHT, false)) {
        // Nothing to do.

    } else if (base::are_strings_equal(name, _XML_TAG_STEREOCHANNEL, false)) {
        // Nothing to do.

    } else if (base::are_strings_equal(name, _XML_TAG_WIDTH, false)) {
        // Nothing to do.

    } else if (base::are_strings_equal(name, _XML_TAG_HEIGHT, false)) {
        // Nothing to do.

    } else if (base::are_strings_equal(name, _XML_TAG_NAME, false)) {
        // Nothing to do.

    }
}
