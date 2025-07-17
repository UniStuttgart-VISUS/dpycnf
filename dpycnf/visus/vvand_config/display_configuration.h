// <copyright file="display_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2015 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_DPYCNF_VISUS_VVAND_CONFIG_DISPLAY_CONFIGURATION_H)
#define _DPYCNF_VISUS_VVAND_CONFIG_DISPLAY_CONFIGURATION_H
#pragma once

#include <iostream>
#include <iterator>
#include <vector>

#include "visus/vvand_config/equals.h"
#include "visus/vvand_config/literal.h"
#include "visus/vvand_config/machine.h"


DPYCNF_NAMESPACE_BEGIN

/// <summary>
/// Represents the whole configuration of a tiled display.
/// </summary>
/// <typeparam name="TChar">The character type used in the configuration.
/// </typeparam>
template<class TChar> class display_configuration {

public:

    /// <summary>
    /// The character type used in the configuration.
    /// </summary>
    typedef TChar char_type;

    /// <summary>
    /// The main iterator type returned by the configuration object, which
    /// is an iterator over the machines used in the configuration.
    /// </summary>
    typedef typename std::vector<machine<TChar>>::const_iterator iterator_type;

    /// <summary>
    /// The type representing a single machine.
    /// </summary>
    typedef machine<TChar> machine_type;

    /// <summary>
    /// The string type used in the configuration.
    /// </summary>
    typedef std::basic_string<TChar> string_type;

    /// <summary>
    /// The type representing a single display tile.
    /// </summary>
    typedef typename machine<TChar>::tile_type tile_type;

    /// <summary>
    /// An iterator which enables iterating all tiles of the tiled display
    /// regardless of the machine that is driving it.
    /// </summary>
    class recursive_tile_iterator : public std::iterator<
            std::forward_iterator_tag, const tile_type> {

        typedef std::iterator<std::forward_iterator_tag, const tile_type>
            base;

    public:

        typedef typename base::difference_type difference_type;
        typedef typename base::iterator_category iterator_category;
        typedef typename base::pointer pointer;
        typedef typename base::reference reference;
        typedef typename base::value_type value_type;

        /// <summary>
        /// Pre-increment.
        /// </summary>
        recursive_tile_iterator& operator ++(void);

        /// <summary>
        /// Post-increment.
        /// </summary>
        inline recursive_tile_iterator operator ++(int) {
            auto retval = *this;
            ++(*this);
            return retval;
        }

        /// <summary>
        /// Test for equality.
        /// </summary>
        bool operator ==(const recursive_tile_iterator& rhs) const;

        /// <summary>
        /// Test for inequality.
        /// </summary>
        inline bool operator !=(const recursive_tile_iterator& rhs) const {
            return !(*this == rhs);
        }

        /// <summary>
        /// Dereference.
        /// </summary>
        inline reference operator *(void) const {
            return this->tit.operator *();
        }

        /// <summary>
        /// Element access.
        /// </summary>
        inline pointer operator ->(void) const {
            return this->tit.operator ->();
        }

    private:

        typedef std::vector<machine_type> collection_type;
        typedef typename display_configuration::iterator_type
            machine_iterator;
        typedef typename machine_type::iterator_type tile_iterator;

        recursive_tile_iterator(const collection_type& machines,
            const bool isBegin);

        const collection_type& machines;
        machine_iterator mit;
        tile_iterator tit;

        friend class display_configuration;
    };

    /// <summary>
    /// Parses the display configuration from the given file.
    /// </summary>
    /// <param name="path">The path to an XML file.</param>
    /// <exception cref="std::system_error">If an I/O error occurred while
    /// reading the input file.</exception>
    /// <exception cref="xml_exception{T}">If an XML syntax error was found
    /// in the file.</exception>
    static display_configuration load(const string_type& path);

    /// <summary>
    /// Parses the display configuration from the given text.
    /// </summary>
    /// <param name="text">The XML text of the configuration.</param>
    /// <exception cref="xml_exception{T}">If an XML syntax error was found
    /// in the text.</exception>
    static display_configuration parse(const string_type& text);

    /// <summary>
    /// Gets an iterator for the begin of the machine list.
    /// </summary>
    iterator_type begin(void) const noexcept {
        return this->_machines.begin();
    }

    /// <summary>
    /// Gets an iterator for the end of the machine list.
    /// </summary>
    iterator_type end(void) const noexcept {
        return this->_machines.end();
    }

    /// <summary>
    /// Searches a machine by its identity string.
    /// </summary>
    iterator_type find_machine(const string_type& identity,
        const bool caseSensitive = false) const;

    /// <summary>
    /// Searches the machine the process is running on by its name,
    /// </summary>
    //MachineCollectionType::const_iterator FindMachine(void) const;

    /// <summary>
    /// Gets the user-defined name of the tiled display.
    /// </summary>
    const string_type& name(void) const noexcept {
        return this->_name;
    }

    /// <summary>
    /// Gets the bounding box of all tiles of the tiled display.
    /// </summary>
    bool range(offset& outBegin, offset& outEnd) const;

    /// <summary>
    /// Gets the configured overall size of the tiled display.
    /// </summary>
    const visus::vvand_config::size& size(void) const noexcept {
        return this->_size;
    }

    /// <summary>
    /// Gets an iterator that enumerates all tiles on all machines.
    /// </summary>
    recursive_tile_iterator tiles_begin(void) const {
        return recursive_tile_iterator(this->_machines, true);
    }

    /// <summary>
    /// Gets the end of the all-tile enumeration.
    /// </summary>
    recursive_tile_iterator tiles_end(void) const {
        return recursive_tile_iterator(this->_machines, false);
    }

    /// <summary>
    /// Answer the XML string representation of the configuration.
    /// </summary>
    inline string_type to_string(void) const {
        std::basic_ostringstream<char_type> retval;
        retval << *this;
        return retval.str();
    }

    /// <summary>
    /// Write the XML representation of the configuration to the given
    /// stream.
    /// </summary>
    friend std::basic_ostream<TChar>& operator <<(std::basic_ostream<TChar>& lhs,
            const display_configuration<TChar>& rhs) {
        // Cf. http://www.parashift.com/c++-faq-lite/templates.html%23faq-35.16
        lhs << DPYCNF_TPL_LITERAL(TChar, "<?xml version=\"1.0\" encoding=\"utf-8\"?>");
        lhs << DPYCNF_TPL_LITERAL(TChar, "<TiledDisplay ");
        lhs << DPYCNF_TPL_LITERAL(TChar, "xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\" ");
        lhs << DPYCNF_TPL_LITERAL(TChar, "xmlns=\"http://www.visus.uni-stuttgart.de/vvand/2012/description\">");

        lhs << DPYCNF_TPL_LITERAL(TChar, "<Machines>");
        for (auto& m : rhs._machines) {
            lhs << DPYCNF_TPL_LITERAL(TChar, "<Machine>");

            lhs << DPYCNF_TPL_LITERAL(TChar, "<Identity>");
            lhs << m.identity();
            lhs << DPYCNF_TPL_LITERAL(TChar, "</Identity>");

            lhs << DPYCNF_TPL_LITERAL(TChar, "<Tiles>");
            for (auto t = m.begin(), end = m.end(); t != end; ++t) {
                lhs << DPYCNF_TPL_LITERAL(TChar, "<LeftOffset>");
                lhs << t->offset().left;
                lhs << DPYCNF_TPL_LITERAL(TChar, "</LeftOffset>");

                lhs << DPYCNF_TPL_LITERAL(TChar, "<Name>");
                lhs << t->name();
                lhs << DPYCNF_TPL_LITERAL(TChar, "</Name>");

                lhs << DPYCNF_TPL_LITERAL(TChar, "<StereoChannel>");
                switch (t->channel()) {
                    case stereo_channel::right:
                        lhs << DPYCNF_TPL_LITERAL(TChar, "Right");
                        break;

                    default:
                        lhs << DPYCNF_TPL_LITERAL(TChar, "Left");
                        break;
                }
                lhs << DPYCNF_TPL_LITERAL(TChar, "</StereoChannel>");

                lhs << DPYCNF_TPL_LITERAL(TChar, "<TopOffset>");
                lhs << t->offset().top;
                lhs << DPYCNF_TPL_LITERAL(TChar, "</TopOffset>");

                lhs << DPYCNF_TPL_LITERAL(TChar, "<WindowHeight>");
                lhs << t->size().height;
                lhs << DPYCNF_TPL_LITERAL(TChar, "</WindowHeight>");

                lhs << DPYCNF_TPL_LITERAL(TChar, "<WindowWidth>");
                lhs << t->size().width;
                lhs << DPYCNF_TPL_LITERAL(TChar, "</WindowWidth>");

                if (t->position() != nullptr) {
                    lhs << DPYCNF_TPL_LITERAL(TChar, "<WindowLeft>");
                    lhs << t->position()->left;
                    lhs << DPYCNF_TPL_LITERAL(TChar, "</WindowLeft>");

                    lhs << DPYCNF_TPL_LITERAL(TChar, "<WindowTop>");
                    lhs << t->position()->top;
                    lhs << DPYCNF_TPL_LITERAL(TChar, "</WindowTop>");
                }
            }
            lhs << DPYCNF_TPL_LITERAL(TChar, "</Tiles>");

            lhs << DPYCNF_TPL_LITERAL(TChar, "</Machine>");
        }
        lhs << DPYCNF_TPL_LITERAL(TChar, "</Machines>");

        lhs << DPYCNF_TPL_LITERAL(TChar, "<Name>");
        lhs << rhs._name;
        lhs << DPYCNF_TPL_LITERAL(TChar, "</Name>");

        lhs << DPYCNF_TPL_LITERAL(TChar, "<Width>");
        lhs << rhs._size.width;
        lhs << DPYCNF_TPL_LITERAL(TChar, "</Width>");

        lhs << DPYCNF_TPL_LITERAL(TChar, "<Height>");
        lhs << rhs._size.height;
        lhs << DPYCNF_TPL_LITERAL(TChar, "</Height>");

        lhs << DPYCNF_TPL_LITERAL(TChar, "</TiledDisplay>");

        return lhs;
    }

private:

    std::vector<machine_type> _machines;
    string_type _name;
    visus::vvand_config::size _size;

    friend class detail::vvand_config_parser<TChar>;
    template<class T> friend void to_json(nlohmann::json&,
        const display_configuration<T>&);
    template<class T> friend void from_json(const nlohmann::json&,
        display_configuration<T>&);
};


#if defined(NLOHMANN_JSON_VERSION_MAJOR)
/// <summary>
/// Converts a display configuration to JSON.
/// </summary>
/// <param name="json"></param>
/// <param name="value"></param>
template<class TChar>
void to_json(nlohmann::json& json, const display_configuration<TChar>& value);

/// <summary>
/// Restores a display configuration from JSON.
/// </summary>
/// <param name="json"></param>
/// <param name="value"></param>
template<class TChar>
void from_json(const nlohmann::json& json, display_configuration<TChar>& value);
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */

DPYCNF_NAMESPACE_END

#include "visus/vvand_config/vvand_config_parser.h"
#include "visus/vvand_config/display_configuration.inl"

#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_DISPLAY_CONFIGURATION_H) */
