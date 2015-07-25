/// <copyright file="DisplayConfiguration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#include "stdafx.h"
#include "Visus/VvandConfig/DisplayConfiguration.h"

#include "../../VvandConfigParser.h"


/*
 * ...RecursiveTileIterator::operator +
 */
Visus::VvandConfig::DisplayConfiguration::RecursiveTileIterator&
Visus::VvandConfig::DisplayConfiguration::RecursiveTileIterator::operator ++(void) {
    if (this->mit != this->machines.end()) {
        if (++this->tit == this->mit->GetTilesEnd()) {
            if (++this->mit != this->machines.end()) {
                this->tit = this->mit->GetTilesBegin();
            }
        }
    }
    return *this;
}


/*
 * ...::RecursiveTileIterator::RecursiveTileIterator
 */
Visus::VvandConfig::DisplayConfiguration::RecursiveTileIterator::RecursiveTileIterator(
        const MachineCollectionType& machines, const bool isBegin) 
        : machines(machines) {
    this->mit = isBegin ? machines.cbegin() : machines.cend();
    this->tit = isBegin
        ? machines.front().GetTilesBegin()
        : machines.back().GetTilesEnd();
}




/*
 * Visus::VvandConfig::DisplayConfiguration::Parse
 */
Visus::VvandConfig::DisplayConfiguration
Visus::VvandConfig::DisplayConfiguration::Parse(const StringType& path) {
    VvandConfigParser parser;
    return parser.Parse(path);
}
