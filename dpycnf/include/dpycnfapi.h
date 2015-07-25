/// <copyright file="dpycnfapi.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#ifndef DPYCNF_STATIC

#ifdef DPYCNF_EXPORTS
#define DPYCNF_API __declspec(dllexport)
#else /* DPYCNF_EXPORTS */
#define DPYCNF_API __declspec(dllimport)
#endif /* DPYCNF_EXPORTS */

#else /* DPYCNF_STATIC */

#define DPYCNF_API

#endif /* DPYCNF_STATIC */
