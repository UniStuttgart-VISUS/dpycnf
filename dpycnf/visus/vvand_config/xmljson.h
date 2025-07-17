// <copyright file="xmljson.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_DPYCNF_VISUS_VVAND_CONFIG_XMLJSON_H)
#define _DPYCNF_VISUS_VVAND_CONFIG_XMLJSON_H
#pragma once

#include <codecvt>
#include <string>

#include "visus/vvand_config/api.h"


#if defined(NLOHMANN_JSON_VERSION_MAJOR)
namespace std {
    // Cf. https://json.nlohmann.me/features/arbitrary_types/

    /// <summary>
    /// Convert a wide string to JSON.
    /// </summary>
    /// <param name="json"></param>
    /// <param name="value"></param>
    inline void to_json(nlohmann::json& json, const std::wstring& value) {
        typedef std::codecvt_utf8<wchar_t> converter_type;
        static std::wstring_convert<converter_type, wchar_t> converter;
        json = converter.to_bytes(value);
    }


    /// <summary>
    /// Convert JSON into a wide string.
    /// </summary>
    /// <param name="json"></param>
    /// <returns></returns>
    inline void from_json(const nlohmann::json& json, std::wstring& value) {
        typedef std::codecvt_utf8<wchar_t> converter_type;
        static std::wstring_convert<converter_type, wchar_t> converter;
        value = json.is_string()
            ? converter.from_bytes(json.get<std::string>())
            : std::wstring();
    }

} /* namespace std */
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */

#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_XMLJSON_H) */
