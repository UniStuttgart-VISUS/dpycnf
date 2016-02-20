/// <copyright file="DisplayConfiguration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#include "stdafx.h"
#include "Visus/VvandConfig/DisplayConfiguration.h"

#include "../../VvandConfigParser.h"


/*
 * ...RecursiveTileIterator::operator +
 */
Visus::VvandConfig::DisplayConfiguration::RecursiveTileIterator&
Visus::VvandConfig::DisplayConfiguration::RecursiveTileIterator::operator ++(void) {
    if (this->mit != this->machines.cend()) {
        if (++this->tit == this->mit->GetTilesEnd()) {
            if (++this->mit != this->machines.cend()) {
                this->tit = this->mit->GetTilesBegin();
            }
        }
    }
    return *this;
}


/*
 * Visus::VvandConfig::DisplayConfiguration::RecursiveTileIterator::operator ==
 */
bool Visus::VvandConfig::DisplayConfiguration::RecursiveTileIterator::operator ==(
        const RecursiveTileIterator& rhs) const {
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
 * ...::RecursiveTileIterator::RecursiveTileIterator
 */
Visus::VvandConfig::DisplayConfiguration::RecursiveTileIterator::RecursiveTileIterator(
        const MachineCollectionType& machines, const bool isBegin) 
        : machines(machines) {
    this->mit = isBegin ? machines.cbegin() : machines.cend();
    if (this->mit != machines.cend()) {
        this->tit = isBegin
            ? machines.front().GetTilesBegin()
            : machines.back().GetTilesEnd();
    }
}


/*
 * Visus::VvandConfig::DisplayConfiguration::Load
 */
Visus::VvandConfig::DisplayConfiguration
Visus::VvandConfig::DisplayConfiguration::Load(const StringType& path) {
    VvandConfigParser parser;
    return parser.ParseFile(path);
}


/*
 * Visus::VvandConfig::DisplayConfiguration::Parse
 */
Visus::VvandConfig::DisplayConfiguration
Visus::VvandConfig::DisplayConfiguration::Parse(const StringType& text) {
    VvandConfigParser parser;
    return parser.ParseText(text);
}



/*
 * Visus::VvandConfig::DisplayConfiguration::FindMachine
 */
Visus::VvandConfig::DisplayConfiguration::MachineCollectionType::const_iterator
Visus::VvandConfig::DisplayConfiguration::FindMachine(
        const StringType& identity, const bool caseSensitive) {
    StringType l;
    if (caseSensitive) {
        l = identity;
    } else {
        std::transform(identity.begin(), identity.end(), l.begin(), ::tolower);
    }

    return std::find_if(this->machines.cbegin(), this->machines.cend(),
            [&](const Machine& m) -> bool {
        StringType r = m.GetIdentity();
        if (!caseSensitive) {
            std::transform(r.begin(), r.end(), r.begin(), ::tolower);
        }
        return (l == r);
    });
}


/*
 * Visus::VvandConfig::DisplayConfiguration::ToString
 */
Visus::VvandConfig::DisplayConfiguration::StringType
Visus::VvandConfig::DisplayConfiguration::ToString(void) const {
    std::basic_ostringstream<TCHAR> retval;
    retval << _T("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
    retval << _T("<TiledDisplay ")
        _T("xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\" ")
        _T("xmlns=\"http://www.visus.uni-stuttgart.de/vvand/2012/description\">");

    retval << _T("<Machines>");
    for (auto& m : this->machines) {
        retval << _T("<Machine>");

        retval << _T("<Identity>");
        retval << m.GetIdentity();
        retval << _T("</Identity>");

        retval << _T("<Tiles>");
        for (auto t = m.GetTilesBegin(); t != m.GetTilesEnd(); ++t) {
            retval << _T("<LeftOffset>");
            retval << t->GetOffset().Left;
            retval << _T("</LeftOffset>");

            retval << _T("<Name>");
            retval << t->GetName();
            retval << _T("</Name>");

            retval << _T("<StereoChannel>");
            switch (t->GetStereoChannel()) {
                case StereoChannel::RIGHT:
                    retval << _T("Right");
                    break;

                default:
                    retval << _T("Left");
                    break;
            }
             retval << _T("</StereoChannel>");

            retval << _T("<TopOffset>");
            retval << t->GetOffset().Top;
            retval << _T("</TopOffset>");

            retval << _T("<WindowHeight>");
            retval << t->GetSize().Height;
            retval << _T("</WindowHeight>");

            retval << _T("<WindowWidth>");
            retval << t->GetSize().Width;
            retval << _T("</WindowWidth>");
        }
        retval << _T("</Tiles>");

        retval << _T("</Machine>");
    }
    retval << _T("</Machines>");

    retval << _T("<Name>");
    retval << this->name;
    retval << _T("</Name>");

    retval << _T("<Width>");
    retval << this->size.Width;
    retval << _T("</Width>");

    retval << _T("<Height>");
    retval << this->size.Height;
    retval << _T("</Height>");

    retval << _T("</TiledDisplay>");

    return retval.str();
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