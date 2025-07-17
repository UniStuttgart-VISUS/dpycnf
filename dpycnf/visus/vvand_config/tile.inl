// <copyright file="tile.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2015 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * DPYCNF_NAMESPACE::tile<T>::~tile
 */
template<class T>
DPYCNF_NAMESPACE::tile<T>::~tile(void) noexcept {
    delete this->_position;
}


/*
 * DPYCNF_NAMESPACE::tile<T>::operator =
 */
template<class T>
DPYCNF_NAMESPACE::tile<T>& DPYCNF_NAMESPACE::tile<T>::operator =(
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
 * DPYCNF_NAMESPACE::tile<T>::operator =
 */
template<class T>
DPYCNF_NAMESPACE::tile<T>& DPYCNF_NAMESPACE::tile<T>::operator =(
        tile&& rhs) noexcept {
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


#if defined(NLOHMANN_JSON_VERSION_MAJOR)
/*
 * DPYCNF_NAMESPACE::to_json<TChar>
 */
template<class TChar>
void DPYCNF_NAMESPACE::to_json<TChar>(nlohmann::json& json,
        const tile<TChar>& value) {
    json["Channel"] = value._channel;
    json["Name"] = value._name;
    json["Offset"] = value._offset;

    if (value._position != nullptr) {
        json["Position"] = *value._position;
    }

    json["Size"] = value._size;
}


/*
 * DPYCNF_NAMESPACE::from_json<TChar>
 */
template<class TChar>
void DPYCNF_NAMESPACE::from_json<TChar>(const nlohmann::json& json,
        tile<TChar>& value) {
    {
        value._channel = stereo_channel::mono;

        auto it = json.find("Channel");
        if (it != json.end()) {
            value._channel = it->template get<decltype(value._channel)>();
        } /* if (it != json.end()) */
    }

    {
        auto it = json.find("Name");
        if (it != json.end()) {
            value._name = it->template get<decltype(value._name)>();
        } else {
            value._name.clear();
        }
    }

    {
        value._offset.left = 0;
        value._offset.top = 0;

        auto it = json.find("Offset");
        if (it != json.end()) {
            value._offset = it->template get<decltype(value._offset)>();
        }
    }

    {
        auto it = json.find("Position");
        if (it != json.end()) {
            auto position = it->template get<offset>();

            if (value._position == nullptr) {
                value._position = new offset(position);
            } else {
                *value._position = position;
            }
        } else {
            delete value._position;
            value._position = nullptr;
        }
    }

    {
        value._size.width = value._size.height = 0;

        auto it = json.find("Size");
        if (it != json.end()) {
            value._size = it->template get<decltype(value._size)>();
        }
    }
}
#endif /* defined(NLOHMANN_JSON_VERSION_MAJOR) */
