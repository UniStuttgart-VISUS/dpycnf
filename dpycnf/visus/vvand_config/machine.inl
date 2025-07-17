// <copyright file="machine.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2015 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * DPYCNF_NAMESPACE::machine<TChar>::find_tile
 */
template<class TChar>
typename DPYCNF_NAMESPACE::machine<TChar>::iterator_type
DPYCNF_NAMESPACE::machine<TChar>::find_tile(const string_type& name,
        const bool caseSensitive) const {
    return std::find_if(this->_tiles.cbegin(), this->_tiles.cend(),
        [&](const tile_type& m) -> bool {
            return detail::equals(name, m.name(), caseSensitive);
        });
}


/*
 * DPYCNF_NAMESPACE::machine<TChar>::find_tile
 */
template<class TChar>
typename DPYCNF_NAMESPACE::machine<TChar>::iterator_type
DPYCNF_NAMESPACE::machine<TChar>::find_tile(const offset_type& offset,
        const bool windowOffset) const {
    return std::find_if(this->_tiles.cbegin(), this->_tiles.cend(),
        [&](const tile_type& m) -> bool {
            if (windowOffset) {
                return ((m.position() != nullptr)
                    && (m.position()->left == offset.left)
                    && (m.position()->top == offset.top));

            } else {
                return ((m.offset().left == offset.left)
                    && (m.offset().top == offset.top));
            }
        });
}


#if defined(NLOHMANN_JSON_VERSION_MAJOR)
/*
 * DPYCNF_NAMESPACE::to_json<TChar>
 */
template<class TChar>
void DPYCNF_NAMESPACE::to_json<TChar>(nlohmann::json& json,
        const machine<TChar>& value) {
    json["Identity"] = value.identity();

    auto& tiles = json["Tiles"] = nlohmann::json::array();
    std::copy(value._tiles.begin(),
        value._tiles.end(),
        std::back_inserter(tiles));
}


/*
 * DPYCNF_NAMESPACE::from_json<TChar>
 */
template<class TChar>
void DPYCNF_NAMESPACE::from_json<TChar>(const nlohmann::json& json,
        machine<TChar>& value) {
    {
        auto it = json.find("Identity");
        if (it != json.end()) {
            value._identity = it->template get<decltype(value._identity)>();
        } else {
            value._identity.clear();
        }
    }

    {
        typedef machine<TChar>::tile_type tile_type;
        value._tiles.clear();

        auto it = json.find("Tiles");
        if (it != json.end()) {
            value._tiles.reserve(it->size());
            std::transform(it->begin(),
                it->end(),
                std::back_inserter(value._tiles),
                [](const nlohmann::json& t) {
                    return t.template get<tile_type>();
                });
        } /* if (it != json.end()) */
    }
}
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */
