/// <copyright file="tile.inl" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 - 2020 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>


/*
 * visus::vvand_config::tile<T>::~tile
 */
template<class T>
visus::vvand_config::tile<T>::~tile(void) {
    delete this->_position;
}


/*
 * visus::vvand_config::tile<T>::operator =
 */
template<class T>
visus::vvand_config::tile<T>& visus::vvand_config::tile<T>::operator =(
        const tile& rhs) {
    if (this != std::addressof(rhs)) {
        this->_channel = rhs._channel;
        this->_name = rhs._name;
        this->_offset = rhs._offset;

        delete this->_position;
        if (rhs._position != nullptr) {
            this->_position = new offset_type(*rhs._position);
        }

        this->_size = rhs._size;
    }

    return *this;
}

/*
 * visus::vvand_config::tile<T>::operator =
 */
template<class T>
visus::vvand_config::tile<T>& visus::vvand_config::tile<T>::operator =(
        tile&& rhs) {
    if (this != std::addressof(rhs)) {
        this->_channel = std::move(rhs._channel);
        rhs._channel = stereo_channel_type::mono;
        this->_name = std::move(rhs._name);
        this->_offset = std::move(rhs._offset);
        this->_position = std::move(rhs._position);
        rhs._position = nullptr;
        this->_size = std::move(rhs._size);
    }

    return *this;
}
