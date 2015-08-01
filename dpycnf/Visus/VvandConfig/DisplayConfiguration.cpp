/// <copyright file="DisplayConfiguration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#include "stdafx.h"
#include "Visus/VvandConfig/DisplayConfiguration.h"

#include <algorithm>

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


/*
 * Visus::VvandConfig::DisplayConfiguration::FindMachine
 */
Visus::VvandConfig::DisplayConfiguration::MachineCollectionType::const_iterator
Visus::VvandConfig::DisplayConfiguration::FindMachine(
        const StringType& identity, const bool caseSensitive) {
    StringType l;
    if (caseSensitive) {
        l = identity;
    } else {
        std::transform(identity.begin(), identity.end(), l.begin(), ::tolower);
    }

    return std::find_if(this->machines.cbegin(), this->machines.cend(),
            [&](const Machine& m) -> bool {
        StringType r = m.GetIdentity();
        if (!caseSensitive) {
            std::transform(r.begin(), r.end(), r.begin(), ::tolower);
        }
        return (l == r);
    });
}
