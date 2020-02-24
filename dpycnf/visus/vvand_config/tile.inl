/// <copyright file="tile.inl" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 - 2020 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>


/*
 * visus::vvand_config::tile<T>::~tile
 */
template<class T>
visus::vvand_config::tile<T>::~tile(void) {
    if (this->_position != nullptr) {
        delete this->_position;
    }
}
