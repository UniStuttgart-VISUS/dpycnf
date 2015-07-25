/// <copyright file="DisplayConfiguration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#include "stdafx.h"
#include "Visus/VvandConfig/DisplayConfiguration.h"

#include "../../VvandConfigParser.h"


/*
 * Visus::VvandConfig::DisplayConfiguration::Parse
 */
Visus::VvandConfig::DisplayConfiguration
Visus::VvandConfig::DisplayConfiguration::Parse(const StringType& path) {
    VvandConfigParser parser;
    return parser.Parse(path);
}
