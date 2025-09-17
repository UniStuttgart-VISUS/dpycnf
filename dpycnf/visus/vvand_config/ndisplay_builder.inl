// <copyright file="ndisplay_builder.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


#if defined(NLOHMANN_JSON_VERSION_MAJOR)
/*
 * DPYCNF_NAMESPACE::ndisplay_builder<TChar>::build
 */
template<class TChar>
nlohmann::json DPYCNF_NAMESPACE::ndisplay_builder<TChar>::build(
        const config_type& config) const {
    const auto total_virtual_size = config.size();

    auto cameras = nlohmann::json::object();
    auto nodes = nlohmann::json::object();
    auto screens = nlohmann::json::object();
    auto xforms = nlohmann::json::object();

    {
        auto& cam = cameras["centre_camera"] = make_xform(
            -this->_camera_distance);
        cam["parentId"] = "room_origin";
        cam["interpupillaryDistance"] = 0;
        cam["swapEyes"] = false;
        cam["stereoOffset"] = "none";
    }

    {
        auto& cam = cameras["left_camera"] = make_xform(
            -this->_camera_distance);
        cam["parentId"] = "room_origin";
        cam["interpupillaryDistance"] = this->_ipd;
        cam["swapEyes"] = false;
        cam["stereoOffset"] = "left";
    }

    {
        auto& cam = cameras["right_camera"] = make_xform(
            -this->_camera_distance);
        cam["parentId"] = "room_origin";
        cam["interpupillaryDistance"] = this->_ipd;
        cam["swapEyes"] = false;
        cam["stereoOffset"] = "right";
    }

    if (!this->_head_node.empty()) {
        const auto aspect = static_cast<float>(total_virtual_size.height)
            / static_cast<float>(total_virtual_size.width);
        const auto height = static_cast<std::uint32_t>(0.5f + aspect
            * static_cast<float>(this->_preview));

        auto& node = nodes[this->_head_node] = {
            { "host", this->address(this->_head_node) },
            { "sound", true },
            { "fullscreen", false }
        };

        auto& screen = screens["preview"] = make_xform();
        screen["parentId"] = "room_origin";
        screen["size"] = {
            { "width", this->_preview / 233.68f },
            { "height", height / 233.68f }
        };

        auto& vp = node["viewports"]["vp_preview"] = make_viewport(offset(),
            size(this->_preview, height), "preview", stereo_channel::mono);

        node["window"] = vp["region"];
    }

    xforms["room_origin"] = make_xform();
    // Make the Powerwall's origin the top-left corner. Note that the nDisplay
    // base coordinate is weird in that y is left and z is up.
    auto& pw_origin = xforms["powerwall_origin"] = make_xform(
        0.0f, -0.5f * this->_width, this->_height);
    pw_origin["parentId"] = "room_origin";

    for (auto& m : config) {
        const auto nid = this->to_utf8(m.identity());
        auto& node = nodes[nid] = nlohmann::json::object();
        node["sound"] = false;
        node["fullscreen"] = true;
        node["host"] = this->address(nid);

        for (auto& t : m) {
            const auto virtual_pos = t.offset();
            const auto physical_pos = basic_offset<float>(
                (this->_width * virtual_pos.left) / total_virtual_size.width,
                -(this->_height * virtual_pos.top) / total_virtual_size.height);
            const auto physical_size = basic_size<float>(
                (this->_width * t.size().width) / total_virtual_size.width,
                (this->_height * t.size().height) / total_virtual_size.height);
            const auto window_pos = (t.position() == nullptr)
                ? offset(0, 0) : *t.position();

            auto tid = this->to_utf8(m.identity());
            tid += "_";
            tid += std::to_string(virtual_pos.left);
            tid += "_";
            tid += std::to_string(virtual_pos.top);

            // World transform of the tile.
            const auto xid = "xform_" + tid;
            auto& xform = xforms[xid] = make_xform(
                0.0f, physical_pos.left, physical_pos.top);
            xform["parentId"] = "powerwall_origin";

            // Screen of the tile.
            const auto sid = "tile_" + tid;
            auto& screen = screens[sid] = make_xform();
            screen["parentId"] = xid;
            screen["size"] = {
                { "width",physical_size.width },
                { "height", physical_size.height }
            };

            // Viewport of the tile.
            const auto vid = "vp_" + tid;
            auto& vp = node["viewports"][vid] = make_viewport(window_pos,
                t.size(), sid, t.channel());
            node["window"] = vp["region"];
        } /* for (auto& t : m) */
    } /* for (auto& m : config) */

    auto retval = nlohmann::json::object();
    retval["version"] = "5.00";
    retval["cluster"]["nodes"] = nodes;

    if (!this->_head_node.empty()) {
        retval["cluster"]["primaryNode"] = {
            { "id", this->_head_node }
        };
    }

    if (!this->_description.empty()) {
        retval["description"] = this->_description;
    }

    retval["scene"]["cameras"] = cameras;
    retval["scene"]["screens"] = screens;
    retval["scene"]["xforms"] = xforms;

    return { { "nDisplay", retval } };
}
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */


#if defined(NLOHMANN_JSON_VERSION_MAJOR)
template<class TChar>
nlohmann::json DPYCNF_NAMESPACE::ndisplay_builder<TChar>::make_xform(
        const float x, const float y, const float z,
        const float pitch, const float yaw, const float roll) {
    nlohmann::json retval = {
        { "parentId", "" },
        {
            "location", {
                { "x", x },
                { "y", y },
                { "z", z }
            }
        },
        {
            "rotation", {
                { "pitch", pitch },
                { "yaw", yaw },
                { "roll", roll }
            }
        }
    };
    return retval;
}
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */

#if defined(NLOHMANN_JSON_VERSION_MAJOR)
/*
 * DPYCNF_NAMESPACE::ndisplay_builder<TChar>::make_viewport
 */
template<class TChar>
nlohmann::json DPYCNF_NAMESPACE::ndisplay_builder<TChar>::make_viewport(
        const offset& position,
        const size& size,
        const std::string& screen,
        const stereo_channel channel) {
    nlohmann::json retval {
        { "bufferRatio", 1 },
        { "gPUIndex", -1 },
        { "allowCrossGPUTransfer", false },
        { "isShared", false },
    };

    //retval["overscan"] = {
    //    { "bEnabled", false },
    //    { "left", 0 },
    //    { "right", 0 },
    //    { "top", 0 },
    //    { "bottom", 0 },
    //    { "oversize", true }
    //};

    retval["projectionPolicy"] = {
        { "type", "simple" },
        { "parameters", { { "screen", screen } } }
    };

    switch (channel) {
        case stereo_channel::left:
            retval["camera"] = "left_camera";
            break;

        case stereo_channel::right:
            retval["camera"] = "right_camera";
            break;

        case stereo_channel::mono:
        default:
            retval["camera"] = "centre_camera";
            break;
    }

    retval["region"] = {
        { "x", position.left },
        { "y", position.top },
        { "w", size.width },
        { "h", size.height }
    };

    return retval;
}
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */


/*
 * DPYCNF_NAMESPACE::ndisplay_builder<TChar>::address
 */
template<class TChar>
const std::string& DPYCNF_NAMESPACE::ndisplay_builder<TChar>::address(
        const std::string& host) const {
    static const std::string Localhost("127.0.0.1");
    auto it = this->_addresses.find(host);
    return (it == this->_addresses.end()) ? Localhost : it->second;
}
