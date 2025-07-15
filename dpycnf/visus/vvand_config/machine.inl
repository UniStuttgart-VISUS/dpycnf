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
