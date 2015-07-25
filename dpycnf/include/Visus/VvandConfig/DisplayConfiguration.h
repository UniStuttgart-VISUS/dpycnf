/// <copyright file="DisplayConfiguration.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once


#include "Visus/VvandConfig/Machine.h"

#ifndef DPYCNF_STATIC
// Make instantiation available in DLL interface.
template class DPYCNF_API std::vector<Visus::VvandConfig::Machine>;
#endif /* !DPYCNF_STATIC */


namespace Visus {
namespace VvandConfig {

    /// <summary>
    /// Represents the whole configuration of a tiled display.
    /// </summary>
    class DPYCNF_API DisplayConfiguration {

    public:

        typedef std::basic_string<wchar_t> StringType;
        typedef std::vector<Machine> MachineCollectionType;

        /// <summary>
        /// An iterator which enables iterating all tiles of the tiled display
        /// regardless of the machine that is driving it.
        /// </summary>
        class DPYCNF_API RecursiveTileIterator : public std::iterator<
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
            inline bool operator ==(const RecursiveTileIterator& rhs) const {
                return ((this->mit == rhs.mit) && (this->tit == rhs.tit));
            }

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

        /// <summary>
        /// Parses the display configuration from the given file.
        /// </summary>
        /// <param name="path">The path to an XML file.</param>
        /// <exception cref="std::system_error">If an I/O error occurred while
        /// reading the input file.</exception>
        /// <exception cref="XmlException">If an XML syntax error was found in
        /// the file.</exception>
        static DisplayConfiguration Parse(const StringType& path);

        /// <summary>
        /// Gets an iterator for the begin of the machine list.
        /// </summary>
        MachineCollectionType::const_iterator GetMachinesBegin(void) const {
            return this->machines.begin();
        }

        /// <summary>
        /// Gets an iterator for the end of the machine list.
        /// </summary>
        MachineCollectionType::const_iterator GetMachinesEnd(void) const {
            return this->machines.end();
        }

        /// <summary>
        /// Gets the user-defined name of the tiled display.
        /// </summary>
        const StringType& GetName(void) const {
            return this->name;
        }

        /// <summary>
        /// Gets the overall size of the tiled display.
        /// </summary>
        const Size& GetSize(void) const {
            return this->size;
        }

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

    private:

        MachineCollectionType machines;
#pragma warning(push)
#pragma warning(disable: 4251)
        StringType name;
#pragma warning(pop)
        Size size;

        friend class VvandConfigParser;
    };
}
}
