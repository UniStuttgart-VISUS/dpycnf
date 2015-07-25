/// <copyright file="dpycnfapi.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2015 Christoph M�ller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>

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
