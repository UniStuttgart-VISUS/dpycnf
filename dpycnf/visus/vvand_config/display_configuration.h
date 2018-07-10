/// <copyright file="display_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 - 2018 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include <iostream>
#include <vector>

#include "visus/vvand_config/literal.h"
#include "visus/vvand_config/machine.h"


namespace visus {
namespace vvand_config {

    /// <summary>
    /// Represents the whole configuration of a tiled display.
    /// </summary>
    template<class T> class display_configuration {

    public:

        /// <summary>
        /// The character type used in the configuration.
        /// </summary>
        typedef T char_type;

        /// <summary>
        /// The main iterator type returned by the configuration object, which
        /// is an iterator over the machines used in the configuration.
        /// </summary>
        typedef typename std::vector<machine<T>>::const_iterator iterator_type;

        /// <summary>
        /// The type representing a single machine.
        /// </summary>
        typedef machine<T> machine_type;

        /// <summary>
        /// The string type used in the configuration.
        /// </summary>
        typedef std::basic_string<T> string_type;

        /// <summary>
        /// The type representing a single display tile.
        /// </summary>
        typedef typename machine<T>::tile_type tile_type;

#if false
        /// <summary>
        /// An iterator which enables iterating all tiles of the tiled display
        /// regardless of the machine that is driving it.
        /// </summary>
        class RecursiveTileIterator : public std::iterator<
                std::forward_iterator_tag, const Tile> {

        public:

            /// <summary>
            /// Pre-increment.
            /// </summary>
            RecursiveTileIterator& operator ++(void);

            /// <summary>
            /// Post-increment.
            /// </summary>
            inline RecursiveTileIterator operator ++(int) {
                auto retval = *this;
                ++(*this);
                return retval;
            }

            /// <summary>
            /// Test for equality.
            /// </summary>
            bool operator ==(const RecursiveTileIterator& rhs) const;

            /// <summary>
            /// Test for inequality.
            /// </summary>
            inline bool operator !=(const RecursiveTileIterator& rhs) const {
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

            typedef MachineCollectionType::const_iterator MachineIterator;
            typedef Machine::TileCollectionType::const_iterator TileIterator;

            RecursiveTileIterator(const MachineCollectionType& machines,
                const bool isBegin);

            const MachineCollectionType& machines;
#pragma warning(push)
#pragma warning(disable: 4251)
            MachineIterator mit;
            TileIterator tit;
#pragma warning(pop)

            friend class DisplayConfiguration;
        };
#endif 

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
        iterator_type begin(void) const {
            return this->_machines.begin();
        }

        /// <summary>
        /// Gets an iterator for the end of the machine list.
        /// </summary>
        iterator_type end(void) const {
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
        const string_type& name(void) const {
            return this->_name;
        }

        /// <summary>
        /// Gets the bounding box of all tiles of the tiled display.
        /// </summary>
        bool range(offset& outBegin, offset& outEnd) const;

        /// <summary>
        /// Gets the configured overall size of the tiled display.
        /// </summary>
        const visus::vvand_config::size& size(void) const {
            return this->_size;
        }

#if 0
        /// <summary>
        /// Gets an iterator that enumerates all tiles on all machines.
        /// </summary>
        RecursiveTileIterator GetTilesBegin(void) const {
            return RecursiveTileIterator(this->machines, true);
        }

        /// <summary>
        /// Gets the end of the all-tile enumeration.
        /// </summary>
        RecursiveTileIterator GetTilesEnd(void) const {
            return RecursiveTileIterator(this->machines, false);
        }
#endif

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
        friend std::basic_ostream<T>& operator <<(std::basic_ostream<T>& lhs,
                const display_configuration<T>& rhs) {
            // Cf. http://www.parashift.com/c++-faq-lite/templates.html%23faq-35.16
            lhs << DPYCNF_TPL_LITERAL(T, "<?xml version=\"1.0\" encoding=\"utf-8\"?>");
            lhs << DPYCNF_TPL_LITERAL(T, "<TiledDisplay ");
            lhs << DPYCNF_TPL_LITERAL(T, "xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\" ");
            lhs << DPYCNF_TPL_LITERAL(T, "xmlns=\"http://www.visus.uni-stuttgart.de/vvand/2012/description\">");

            lhs << DPYCNF_TPL_LITERAL(T, "<Machines>");
            for (auto& m : rhs._machines) {
                lhs << DPYCNF_TPL_LITERAL(T, "<Machine>");

                lhs << DPYCNF_TPL_LITERAL(T, "<Identity>");
                lhs << m.identity();
                lhs << DPYCNF_TPL_LITERAL(T, "</Identity>");

                lhs << DPYCNF_TPL_LITERAL(T, "<Tiles>");
                for (auto t = m.begin(), end = m.end(); t != end; ++t) {
                    lhs << DPYCNF_TPL_LITERAL(T, "<LeftOffset>");
                    lhs << t->offset().left;
                    lhs << DPYCNF_TPL_LITERAL(T, "</LeftOffset>");

                    lhs << DPYCNF_TPL_LITERAL(T, "<Name>");
                    lhs << t->name();
                    lhs << DPYCNF_TPL_LITERAL(T, "</Name>");

                    lhs << DPYCNF_TPL_LITERAL(T, "<StereoChannel>");
                    switch (t->channel()) {
                        case stereo_channel::right:
                            lhs << DPYCNF_TPL_LITERAL(T, "Right");
                            break;

                        default:
                            lhs << DPYCNF_TPL_LITERAL(T, "Left");
                            break;
                    }
                    lhs << DPYCNF_TPL_LITERAL(T, "</StereoChannel>");

                    lhs << DPYCNF_TPL_LITERAL(T, "<TopOffset>");
                    lhs << t->offset().top;
                    lhs << DPYCNF_TPL_LITERAL(T, "</TopOffset>");

                    lhs << DPYCNF_TPL_LITERAL(T, "<WindowHeight>");
                    lhs << t->size().height;
                    lhs << DPYCNF_TPL_LITERAL(T, "</WindowHeight>");

                    lhs << DPYCNF_TPL_LITERAL(T, "<WindowWidth>");
                    lhs << t->size().width;
                    lhs << DPYCNF_TPL_LITERAL(T, "</WindowWidth>");
                }
                lhs << DPYCNF_TPL_LITERAL(T, "</Tiles>");

                lhs << DPYCNF_TPL_LITERAL(T, "</Machine>");
            }
            lhs << DPYCNF_TPL_LITERAL(T, "</Machines>");

            lhs << DPYCNF_TPL_LITERAL(T, "<Name>");
            lhs << rhs._name;
            lhs << DPYCNF_TPL_LITERAL(T, "</Name>");

            lhs << DPYCNF_TPL_LITERAL(T, "<Width>");
            lhs << rhs._size.width;
            lhs << DPYCNF_TPL_LITERAL(T, "</Width>");

            lhs << DPYCNF_TPL_LITERAL(T, "<Height>");
            lhs << rhs._size.height;
            lhs << DPYCNF_TPL_LITERAL(T, "</Height>");

            lhs << DPYCNF_TPL_LITERAL(T, "</TiledDisplay>");

            return lhs;
        }

    private:

        std::vector<machine_type> _machines;
        string_type _name;
        visus::vvand_config::size _size;

        friend class detail::vvand_config_parser<T>;
    };

} /* end namespace vvand_config */
} /* end namespace visus */

#include "visus/vvand_config/vvand_config_parser.h"
#include "visus/vvand_config/display_configuration.inl"
