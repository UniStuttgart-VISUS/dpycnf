// <copyright file="ndisplay_builder.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_DPYCNF_VISUS_VVAND_CONFIG_NDISPLAY_BUILDER_H)
#define _DPYCNF_VISUS_VVAND_CONFIG_NDISPLAY_BUILDER_H
#pragma once

#include <codecvt>
#include <string>
#include <unordered_map>

#include "visus/vvand_config/display_configuration.h"


DPYCNF_NAMESPACE_BEGIN

/// <summary>
/// A utility class to build an nDisplay configuration from a
/// <see cref="display_configuration{TChar}" /> object.
/// </summary>
/// <typeparam name="TChar">The character type used in the builder.
/// </typeparam>
template<class TChar> class ndisplay_builder final {

public:

    /// <summary>
    /// The character type used in the builder.
    /// </summary>
    typedef TChar char_type;

    /// <summary>
    /// The type of the display configuration to be converted.
    /// </summary>
    typedef display_configuration<TChar> config_type;

    /// <summary>
    /// The string type used in the builder.
    /// </summary>
    typedef std::basic_string<TChar> string_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline ndisplay_builder(void)
        : _camera_distance(200.0f),
        _height(0.0f),
        _ipd(6.4f),
        _preview(1920),
        _width(0.0f) { }

    /// <summary>
    /// Adds an IP address for a host name.
    /// </summary>
    /// <param name="identity">The identity of the node in the
    /// <see cref="display_configuration{TChar}" />, which is typically a host
    /// name.</param>
    /// <param name="address">The IP address of the node.</param>
    /// <returns>*<see langword="this" />.</returns>
    inline ndisplay_builder& add_ip_address(const string_type& identity,
            const string_type & address) {
        this->_addresses[this->to_utf8(identity)] = this->to_utf8(address);
        return *this;
    }

#if defined(NLOHMANN_JSON_VERSION_MAJOR)
    /// <summary>
    /// Adds the IP addresses from a JSON object.
    /// </summary>
    /// <param name="addresses">A JSON object with the node identities as keys
    /// and the respective IP addresses as values.</param>
    /// <returns>*<see langword="this" />.</returns>
    inline ndisplay_builder& add_ip_addresses(const nlohmann::json& addresses) {
        for (auto it = addresses.begin(); it != addresses.end(); ++it) {
            this->_addresses[it.key()] = it.value();
        }
        return *this;
    }
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */

#if defined(NLOHMANN_JSON_VERSION_MAJOR)
    /// <summary>
    /// Builds the nDisplay configuration from the specified display
    /// configuration.
    /// </summary>
    /// <param name="config">The display configuration to build from.</param>
    /// <returns>The nDisplay configuration as JSON object.</returns>
    nlohmann::json build(const config_type& config) const;
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */

    /// <summary>
    /// Adds a head node controlling the cluster.
    /// </summary>
    /// <param name="head_node">The name of the head node.</param>
    /// <param name="address">The IP address of the node.</param>
    /// <returns>*<see langword="this" />.</returns>
    inline ndisplay_builder& controlled_by(const string_type& head_node,
            const string_type& address) {
        this->controlled_by(head_node);
        return this->add_ip_address(this->_head_node, address);
    }

    /// <summary>
    /// Adds a head node controlling the cluster.
    /// </summary>
    /// <param name="head_node">The name of the head node.</param>
    /// <returns>*<see langword="this" />.</returns>
    inline ndisplay_builder& controlled_by(const string_type& head_node) {
        this->_head_node = this->to_utf8(head_node);
        return *this;
    }

    /// <summary>
    /// Sets the distance of the camera from the display wall in centimetres.
    /// </summary>
    /// <param name="distance">The distance of the camera from the
    /// screen.</param>
    /// <returns>*<see langword="this" />.</returns>
    inline ndisplay_builder& with_camera_distance(
            const float distance) noexcept {
        this->_camera_distance = std::abs(distance);
        return *this;
    }

    /// <summary>
    /// Sets a description to be added to the configuration.
    /// </summary>
    /// <param name="description">The description text.</param>
    /// <returns>*<see langword="this" />.</returns>
    inline ndisplay_builder& with_description(const string_type& description) {
        this->_description = this->to_utf8(description);
        return *this;
    }

    /// <summary>
    /// Sets the interpupillary distance (IPD) in centimetres.
    /// </summary>
    /// <param name="ipd">The IPD in centimetres.</param>
    /// <returns>*<see langword="this" />.</returns>
    inline ndisplay_builder& with_interpupillary_distance(
            const float ipd) noexcept {
        this->_ipd = ipd;
        return *this;
    }

    /// <summary>
    /// Sets the interpupillary distance (IPD) in centimetres.
    /// </summary>
    /// <param name="ipd">The IPD in centimetres.</param>
    /// <returns>*<see langword="this" />.</returns>
    inline ndisplay_builder& with_ipd(const float ipd) noexcept {
        this->_ipd = ipd;
        return *this;
    }

    /// <summary>
    /// Sets the physical height of the display wall.
    /// </summary>
    /// <param name="height">The physical height of the display wall.</param>
    /// <returns>*<see langword="this" />.</returns>
    inline ndisplay_builder& with_physical_height(const float height) noexcept {
        this->_height = height;
        return *this;
    }

    /// <summary>
    /// Sets the physical size of the display wall.
    /// </summary>
    /// <param name="width">The physical width of the display wall.</param>
    /// <param name="height">The physical height of the display wall.</param>
    /// <returns>*<see langword="this" />.</returns>
    inline ndisplay_builder& with_physical_size(const float width,
            const float height) noexcept {
        this->_height = height;
        this->_width = width;
        return *this;
    }

    /// <summary>
    /// Sets the physical width of the display wall.
    /// </summary>
    /// <param name="width">The physical width of the display wall.</param>
    /// <returns>*<see langword="this" />.</returns>
    inline ndisplay_builder& with_physical_width(const float width) noexcept {
        this->_width = width;
        return *this;
    }

    /// <summary>
    /// Sets the width of the preview window in pixels.
    /// </summary>
    /// <param name="preview">The width of the preview window on the head
    /// node.</param>
    /// <returns>*<see langword="this" />.</returns>
    inline ndisplay_builder& with_preview_width(
            const std::uint32_t preview) noexcept {
        this->_preview = preview;
        return *this;
    }

private:

    typedef std::codecvt_utf8<wchar_t> converter_type;

#if defined(NLOHMANN_JSON_VERSION_MAJOR)
    static nlohmann::json make_xform(const float x = 0.0f, const float y = 0.0f,
        const float z = 0.0f, const float pitch = 0.0f, const float yaw = 0.0f,
        const float roll = 0.0f);
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */

#if defined(NLOHMANN_JSON_VERSION_MAJOR)
    static nlohmann::json make_viewport(const offset& position,
        const size& size,
        const std::string& screen,
        const stereo_channel channel);
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */

    const std::string& address(const std::string& host) const;

    inline const std::string& to_utf8(const std::string& str) const noexcept {
        return str;
    }

    inline const std::string to_utf8(const std::wstring& str) const {
        return this->_converter.to_bytes(str);
    }

    std::unordered_map<std::string, std::string> _addresses;
    float _camera_distance;
    std::wstring_convert<converter_type, wchar_t> _converter;
    std::string _description;
    std::string _head_node;
    float _height;
    float _ipd;
    std::uint32_t _preview;
    float _width;
};

DPYCNF_NAMESPACE_END

#include "visus/vvand_config/ndisplay_builder.inl"

#endif /* !defined(_DPYCNF_VISUS_VVAND_CONFIG_NDISPLAY_BUILDER_H) */
