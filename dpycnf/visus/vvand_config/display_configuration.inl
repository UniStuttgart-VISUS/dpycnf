// <copyright file="display_configuration.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2015 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * ...recursive_tile_iterator::operator ++
 */
template<class TChar>
typename DPYCNF_NAMESPACE::display_configuration<TChar>::recursive_tile_iterator&
DPYCNF_NAMESPACE::display_configuration<TChar>::recursive_tile_iterator::operator ++(
        void) {
    if (this->mit != this->machines.cend()) {
        if (++this->tit == this->mit->end()) {
            if (++this->mit != this->machines.cend()) {
                this->tit = this->mit->begin();
            }
        }
    }
    return *this;
}


/*
 * ...::recursive_tile_iterator::operator ==
 */
template<class TChar>
bool DPYCNF_NAMESPACE::display_configuration<TChar>::recursive_tile_iterator::operator ==(
        const recursive_tile_iterator& rhs) const {
    if (this->mit == rhs.mit) {
        if (this->mit != this->machines.cend()) {
            return (this->tit == rhs.tit);
        } else {
            return true;
        }

    } else {
        return false;
    }
}


/*
 * ...::recursive_tile_iterator::recursive_tile_iterator
 */
template<class TChar>
DPYCNF_NAMESPACE::display_configuration<TChar>::recursive_tile_iterator::recursive_tile_iterator(
        const collection_type& machines, const bool isBegin)
        : machines(machines) {
    this->mit = isBegin ? machines.cbegin() : machines.cend();
    if (this->mit != machines.cend()) {
        this->tit = isBegin
            ? machines.front().begin()
            : machines.back().end();
    }
}


/*
 * DPYCNF_NAMESPACE::display_configuration<T>::load
 */
template<class TChar>
DPYCNF_NAMESPACE::display_configuration<TChar>
DPYCNF_NAMESPACE::display_configuration<TChar>::load(const string_type& path) {
    detail::vvand_config_parser<TChar> parser;
    return parser.parse_file(path);
}


/*
 * DPYCNF_NAMESPACE::display_configuration<T>::Parse
 */
template<class TChar>
DPYCNF_NAMESPACE::display_configuration<TChar>
DPYCNF_NAMESPACE::display_configuration<TChar>::parse(const string_type& text) {
    detail::vvand_config_parser<TChar> parser;
    return parser.parse_text(text);
}



/*
 * DPYCNF_NAMESPACE::display_configuration<T>::find_machine
 */
template<class TChar>
typename DPYCNF_NAMESPACE::display_configuration<TChar>::iterator_type
DPYCNF_NAMESPACE::display_configuration<TChar>::find_machine(
        const string_type& identity, const bool caseSensitive) const {
    return std::find_if(this->_machines.cbegin(), this->_machines.cend(),
            [&](const machine_type& m) -> bool {
        return detail::equals(identity, m.identity(), caseSensitive);
    });
}


#if 0
/*
 * DPYCNF_NAMESPACE::display_configuration<T>::FindMachine
 */
template<class TChar>
DPYCNF_NAMESPACE::display_configuration<TChar>::MachineCollectionType::const_iterator
DPYCNF_NAMESPACE::display_configuration<TChar>::FindMachine(void) const {
    string_type::value_type name[MAX_COMPUTERNAME_LENGTH + 1];
    auto size = static_cast<DWORD>(std::size(name));

    ::ZeroMemory(name, sizeof(name));
    if (::GetComputerNameW(name, &size)) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    return this->FindMachine(name, false);
}
#endif


/*
 * DPYCNF_NAMESPACE::display_configuration<T>::range
 */
template<class TChar>
bool DPYCNF_NAMESPACE::display_configuration<TChar>::range(
        offset& outBegin, offset& outEnd) const {
    typedef std::numeric_limits<offset::value_type> offset_limits;
    auto minX = (offset_limits::max)();
    auto minY = (offset_limits::max)();
    auto maxX = (offset_limits::lowest)();
    auto maxY = (offset_limits::lowest)();
    auto retval = !this->_machines.empty();

    for (auto it = this->tiles_begin(), end = this->tiles_end(); it != end;
            ++it) {
        auto o = it->offset();
        auto s = it->size();
        if (o.left < minX) {
            minX = o.left;
        }
        if (o.top < minY) {
            minY = o.top;
        }
        if (o.left + s.width > maxX) {
            maxX = o.left + s.width;
        }
        if (o.top + s.height > maxY) {
            maxY = o.top + s.height;
        }
    }

    if (retval) {
        outBegin.left = minX;
        outBegin.top = minY;
        outEnd.left = maxX;
        outEnd.top = maxY;
    }

    return retval;
}
