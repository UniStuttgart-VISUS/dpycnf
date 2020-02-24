/// <copyright file="tile.inl" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2015 - 2020 Christoph M�ller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>


/*
 * visus::vvand_config::tile<T>::~tile
 */
template<class T>
visus::vvand_config::tile<T>::~tile(void) {
    if (this->_position != nullptr) {
        delete this->_position;
    }
}
