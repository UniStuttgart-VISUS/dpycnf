// <copyright file="size.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


#if defined(NLOHMANN_JSON_VERSION_MAJOR)
/*
 * DPYCNF_NAMESPACE::to_json
 */
template<class TValue>
void DPYCNF_NAMESPACE::to_json(nlohmann::json& json,
        const basic_size<TValue>& value) {
    json["Width"] = value.width;
    json["Height"] = value.height;
}


/*
 * DPYCNF_NAMESPACE::from_json
 */
template<class TValue>
void DPYCNF_NAMESPACE::from_json(const nlohmann::json& json,
        basic_size<TValue>& value) {
    {
        auto it = json.find("Width");
        if (it != json.end()) {
            value.width = it->template get<decltype(value.width)>();
        }
    }

    {
        auto it = json.find("Height");
        if (it != json.end()) {
            value.height = it->template get<decltype(value.height)>();
        }
    }
}
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */
