/// <copyright file="dpycnfapi.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#ifdef DPYCNF_EXPORTS
#define DPYCNF_API __declspec(dllexport)
#else
#define DPYCNF_API __declspec(dllimport)
#endif
