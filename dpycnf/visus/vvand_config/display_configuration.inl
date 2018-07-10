/// <copyright file="display_configuration.inl" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 - 2018 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>


/*
 * ...recursive_tile_iterator::operator ++
 */
template<class T>
typename visus::vvand_config::display_configuration<T>::recursive_tile_iterator&
visus::vvand_config::display_configuration<T>::recursive_tile_iterator::operator ++(
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
template<class T>
bool visus::vvand_config::display_configuration<T>::recursive_tile_iterator::operator ==(
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
template<class T>
visus::vvand_config::display_configuration<T>::recursive_tile_iterator::recursive_tile_iterator(
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
 * visus::vvand_config::display_configuration<T>::load
 */
template<class T>
visus::vvand_config::display_configuration<T>
visus::vvand_config::display_configuration<T>::load(const string_type& path) {
    detail::vvand_config_parser<T> parser;
    return parser.parse_file(path);
}


/*
 * visus::vvand_config::display_configuration<T>::Parse
 */
template<class T>
visus::vvand_config::display_configuration<T>
visus::vvand_config::display_configuration<T>::parse(const string_type& text) {
    detail::vvand_config_parser<T> parser;
    return parser.parse_text(text);
}



/*
 * visus::vvand_config::display_configuration<T>::find_machine
 */
template<class T>
typename visus::vvand_config::display_configuration<T>::iterator_type
visus::vvand_config::display_configuration<T>::find_machine(
        const string_type& identity, const bool caseSensitive) const {
    string_type l;
    if (caseSensitive) {
        l = identity;
    } else {
        std::transform(identity.begin(), identity.end(),
            std::back_inserter(l), ::tolower);
    }

    return std::find_if(this->_machines.cbegin(), this->_machines.cend(),
            [&](const machine_type& m) -> bool {
        string_type r = m.identity();
        if (!caseSensitive) {
            std::transform(r.begin(), r.end(),
                std::back_inserter(r), ::tolower);
        }
        return (l == r);
    });
}


#if 0
/*
 * visus::vvand_config::display_configuration<T>::FindMachine
 */
template<class T>
visus::vvand_config::display_configuration<T>::MachineCollectionType::const_iterator
visus::vvand_config::display_configuration<T>::FindMachine(void) const {
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
 * visus::vvand_config::display_configuration<T>::range
 */
template<class T>
bool visus::vvand_config::display_configuration<T>::range(
        offset& outBegin, offset& outEnd) const {
    typedef std::numeric_limits<offset::value_type> offset_limits;
    auto minX = (offset_limits::max)();
    auto minY = (offset_limits::max)();
    auto maxX = (offset_limits::lowest)();
    auto maxY = (offset_limits::lowest)();
    auto retval = !this->_machines.empty();

    for (auto it = this->begin(), end = this->end(); it != end; ++it) {
        auto o = it->offset();
        auto s = it->size();
        if (o.left < minX) {
            minX = o.Left;
        }
        if (o.top < minY) {
            minY = o.Top;
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

/*
<TiledDisplay xmlns:i="http://www.w3.org/2001/XMLSchema-instance" xmlns="http://www.visus.uni-stuttgart.de/vvand/2012/description">
  <Machines>
    <Machine>
      <Identity>keshiki01</Identity>
      <Tiles>
        <Tile>

        </Tile>
      </Tiles>
    </Machine>
*/