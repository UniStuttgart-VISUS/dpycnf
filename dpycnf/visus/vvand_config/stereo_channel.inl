// <copyright file="stereo_channel.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


#if defined(NLOHMANN_JSON_VERSION_MAJOR)
/*
 * DPYCNF_NAMESPACE::to_json
 */
void DPYCNF_NAMESPACE::to_json(nlohmann::json& json,
        const stereo_channel value) {
    switch (value) {
        case stereo_channel::left:
            json = "left";
            break;

        case stereo_channel::right:
            json = "right";
            break;

        case stereo_channel::mono:
        default:
            json = "mono";
            break;
    }
}


/*
 * DPYCNF_NAMESPACE::from_json
 */
void DPYCNF_NAMESPACE::from_json(const nlohmann::json& json,
        stereo_channel& value) {
    value = stereo_channel::mono;

    if (json.is_string()) {
        auto channel = json.get<std::string>();
        std::transform(channel.begin(), channel.end(), channel.begin(),
            [](unsigned char c) { return std::tolower(c); });

        if (channel == "left") {
            value = stereo_channel::left;

        } else if (channel == "right") {
            value = stereo_channel::right;
        }
    }
}
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */
