/// <copyright file="DisplayConfiguration.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once


#include "Visus/VvandConfig/Machine.h"

// Make instantiation available in DLL interface.
template class DPYCNF_API std::vector<Visus::VvandConfig::Machine>;


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
