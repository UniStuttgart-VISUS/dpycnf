// <copyright file="offset.inl" company="Visualisierungsinstitut der Universität Stuttgart">
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
        const basic_offset<TValue>& value) {
    json["Left"] = value.left;
    json["Top"] = value.top;
}


/*
 * DPYCNF_NAMESPACE::from_json
 */
template<class TValue>
void DPYCNF_NAMESPACE::from_json(const nlohmann::json& json,
        basic_offset<TValue>& value) {
    {
        auto it = json.find("Left");
        if (it != json.end()) {
            value.left = it->template get<decltype(value.left)>();
        }
    }

    {
        auto it = json.find("Top");
        if (it != json.end()) {
            value.top = it->template get<decltype(value.top)>();
        }
    }
}
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */
