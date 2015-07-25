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

    private:

        MachineCollectionType machines;
        StringType name;
        Size size;

        friend class VvandConfigParser;
    };
}
}
