// <copyright file="tile.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2015 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * DPYCNF_NAMESPACE::tile<T>::~tile
 */
template<class TChar>
DPYCNF_NAMESPACE::tile<TChar>::~tile(void) noexcept {
    delete this->_position;
}
