/// <copyright file="dpycnfapi.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2015 Christoph M�ller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>

#pragma once

#ifdef DPYCNF_EXPORTS
#define DPYCNF_API __declspec(dllexport)
#else
#define DPYCNF_API __declspec(dllimport)
#endif
