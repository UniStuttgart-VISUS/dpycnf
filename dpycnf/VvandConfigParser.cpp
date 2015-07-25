/// <copyright file="VvandConfigParser.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2015 Christoph Müller. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#include "stdafx.h"
#include "VvandConfigParser.h"

#include "XmlException.h"

#ifdef XML_UNICODE
#define _X(s) L#s
#else /* XML_UNICODE */
#define _X(s) s
#endif /* XML_UNICODE */

#define TAG_TILEDDISPLAY _X("TiledDisplay")
#define TAG_MACHINES _X("Machines")
#define TAG_MACHINE _X("Machine")
#define TAG_IDENTITY _X("Identity")
#define TAG_TILES _X("Tiles")
#define TAG_TILE _X("Tile")
#define TAG_LEFTOFFSET _X("LeftOffset")
#define TAG_TOPOFFSET _X("TopOffset")
#define TAG_WINDOWWIDTH _X("WindowWidth")
#define TAG_WINDOWHEIGHT _X("WindowHeight")
#define TAG_STEREOCHANNEL _X("StereoChannel")
#define TAG_WIDTH _X("Width")
#define TAG_HEIGHT _X("Height")
#define TAG_NAME _X("Name")


/*
 * Visus::VvandConfig::VvandConfigParser::VvandConfigParser
 */
Visus::VvandConfig::VvandConfigParser::VvandConfigParser(void) { }


/*
 * Visus::VvandConfig::VvandConfigParser::~VvandConfigParser
 */
Visus::VvandConfig::VvandConfigParser::~VvandConfigParser(void) { }


/*
 * Visus::VvandConfig::VvandConfigParser::Parse
 */
Visus::VvandConfig::DisplayConfiguration
Visus::VvandConfig::VvandConfigParser::Parse(const StringType& path) {
    Visus::VvandConfig::DisplayConfiguration retval;
    Base::Parse(path);
    return retval;
}


/*
 * Visus::VvandConfig::VvandConfigParser::OnCharacters
 */
void Visus::VvandConfig::VvandConfigParser::OnCharacters(
        const XML_Char *s, const int len) {
    this->cdata.append(s, len);
}


/*
 * Visus::VvandConfig::VvandConfigParser::OnEndElement
 */
void Visus::VvandConfig::VvandConfigParser::OnEndElement(
        const XML_Char *name) {
#define THROW_UNEXPECTED_TAG(tag)                                              \
    throw XmlException(_X("Closing tag \"") tag _X("\" is unexpected here."),  \
        this->GetCurrentLineNumber(), this->GetCurrentColumnNumber(),          \
        __FILE__, __LINE__)


    if (SaxParser::AreStringsEqual(name, TAG_TILEDDISPLAY, false)) {
        if (this->currentScope == Scope::TILED_DISPLAY) {
            this->currentScope = Scope::UNKNOWN;
        } else {
            THROW_UNEXPECTED_TAG(TAG_TILEDDISPLAY);
        }

    } else if (SaxParser::AreStringsEqual(name, TAG_MACHINES, false)) {
        if (this->currentScope == Scope::MACHINES) {
            this->currentScope = Scope::TILED_DISPLAY;
        } else {
            THROW_UNEXPECTED_TAG(TAG_MACHINES);
        }

    } else if (SaxParser::AreStringsEqual(name, TAG_MACHINE, false)) {
        if (this->currentScope == Scope::MACHINE) {
            this->currentScope = Scope::MACHINES;
            this->currentConfig.machines.push_back(this->currentMachine);
        } else {
            THROW_UNEXPECTED_TAG(TAG_MACHINE);
        }

    } else if (SaxParser::AreStringsEqual(name, TAG_IDENTITY, false)) {
        if (this->currentScope == Scope::MACHINE) {
            this->currentMachine.identity = this->cdata;
        } else {
            THROW_UNEXPECTED_TAG(TAG_IDENTITY);
        }

    } else if (SaxParser::AreStringsEqual(name, TAG_TILES, false)) {
        if (this->currentScope == Scope::TILES) {
            this->currentScope = Scope::MACHINE;
        } else {
            THROW_UNEXPECTED_TAG(TAG_TILES);
        }

    } else if (SaxParser::AreStringsEqual(name, TAG_TILE, false)) {
        if (this->currentScope == Scope::TILE) {
            this->currentScope = Scope::TILES;
            this->currentMachine.tiles.push_back(this->currentTile);
        } else {
            THROW_UNEXPECTED_TAG(TAG_TILE);
        }

    } else if (SaxParser::AreStringsEqual(name, TAG_LEFTOFFSET, false)) {
        if (this->currentScope == Scope::TILE) {
            int tmp = std::stoi(this->cdata);
            this->currentTile.offset.Left = std::min<int>(tmp,
                this->currentTile.offset.Left);
        }

    } else if (SaxParser::AreStringsEqual(name, TAG_TOPOFFSET, false)) {
        if (this->currentScope == Scope::TILE) {
            int tmp = std::stoi(this->cdata);
            this->currentTile.offset.Top = std::min<int>(tmp, 
                this->currentTile.offset.Top);
        }

    } else if (SaxParser::AreStringsEqual(name, TAG_WINDOWWIDTH, false)) {
        if (this->currentScope == Scope::TILE) {
            int tmp = std::stoi(this->cdata);
            this->currentTile.size.Width = std::max<int>(tmp, 0);
        }

    } else if (SaxParser::AreStringsEqual(name, TAG_WINDOWHEIGHT, false)) {
        if (this->currentScope == Scope::TILE) {
            int tmp = std::stoi(this->cdata);
            this->currentTile.size.Height = std::max<int>(tmp, 0);
        }


    } else if (SaxParser::AreStringsEqual(name, TAG_STEREOCHANNEL, false)) {
        if (SaxParser::AreStringsEqual(this->cdata.c_str(), _X("right"), false)) {
            this->currentTile.stereoChannel = StereoChannel::RIGHT;

        } else if (SaxParser::AreStringsEqual(this->cdata.c_str(), _X("left"), false)) {
            this->currentTile.stereoChannel = StereoChannel::LEFT;

        } else {
            this->currentTile.stereoChannel = StereoChannel::MONO;
        }

    } else if (SaxParser::AreStringsEqual(name, TAG_WIDTH, false)) {
        if (this->currentScope == Scope::TILED_DISPLAY) {
            int tmp = std::stoi(this->cdata);
            this->currentConfig.size.Width = std::max<int>(tmp, 0);
        }

    } else if (SaxParser::AreStringsEqual(name, TAG_HEIGHT, false)) {
        if (this->currentScope == Scope::TILED_DISPLAY) {
            int tmp = std::stoi(this->cdata);
            this->currentConfig.size.Height = std::max<int>(tmp, 0);
        }

    } else if (SaxParser::AreStringsEqual(name, TAG_NAME, false)) {
        if (this->currentScope == Scope::TILE) {
            this->currentTile.name = this->cdata;
        } else if (this->currentScope == Scope::TILED_DISPLAY) {
            this->currentConfig.name = this->cdata;
        }

    }

#undef THROW_UNEXPECTED_TAG
}


/*
 * Visus::VvandConfig::VvandConfigParser::OnStartElement
 */
void Visus::VvandConfig::VvandConfigParser::OnStartElement(
        const XML_Char *name, const XML_Char **atts) {
    // Clear old CDATA
    this->cdata.clear();

    if (SaxParser::AreStringsEqual(name, TAG_TILEDDISPLAY, false)) {
        this->currentScope = Scope::TILED_DISPLAY;
        this->currentConfig = Visus::VvandConfig::DisplayConfiguration();

    } else if (SaxParser::AreStringsEqual(name, TAG_MACHINES, false)) {
        this->currentScope = Scope::MACHINES;

    } else if (SaxParser::AreStringsEqual(name, TAG_MACHINE, false)) {
        this->currentScope = Scope::MACHINE;
        this->currentMachine = Visus::VvandConfig::Machine();

    } else if (SaxParser::AreStringsEqual(name, TAG_IDENTITY, false)) {
        // Nothing to do

    } else if (SaxParser::AreStringsEqual(name, TAG_TILES, false)) {
        this->currentScope = Scope::TILES;

    } else if (SaxParser::AreStringsEqual(name, TAG_TILE, false)) {
        this->currentScope = Scope::TILE;
        this->currentTile = Visus::VvandConfig::Tile();

    } else if (SaxParser::AreStringsEqual(name, TAG_LEFTOFFSET, false)) {
        // Nothing to do.

    } else if (SaxParser::AreStringsEqual(name, TAG_TOPOFFSET, false)) {
        // Nothing to do.

    } else if (SaxParser::AreStringsEqual(name, TAG_WINDOWWIDTH, false)) {
        // Nothing to do.

    } else if (SaxParser::AreStringsEqual(name, TAG_WINDOWHEIGHT, false)) {
        // Nothing to do.

    } else if (SaxParser::AreStringsEqual(name, TAG_STEREOCHANNEL, false)) {
        // Nothing to do.

    } else if (SaxParser::AreStringsEqual(name, TAG_WIDTH, false)) {
        // Nothing to do.

    } else if (SaxParser::AreStringsEqual(name, TAG_HEIGHT, false)) {
        // Nothing to do.

    } else if (SaxParser::AreStringsEqual(name, TAG_NAME, false)) {
        // Nothing to do.

    }
}
