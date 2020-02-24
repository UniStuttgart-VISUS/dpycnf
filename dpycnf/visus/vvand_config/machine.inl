/// <copyright file="machine.inl" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2020 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>


/*
 * visus::vvand_config::machine<T>::find_tile
 */
template<class T>
typename visus::vvand_config::machine<T>::iterator_type
visus::vvand_config::machine<T>::find_tile(const string_type& name,
        const bool caseSensitive) const {
    return std::find_if(this->_tiles.cbegin(), this->_tiles.cend(),
        [&](const tile_type& m) -> bool {
            return detail::equals(name, m.name(), caseSensitive);
        });
}


/*
 * visus::vvand_config::machine<T>::find_tile
 */
template<class T>
typename visus::vvand_config::machine<T>::iterator_type
visus::vvand_config::machine<T>::find_tile(const offset_type& offset,
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
