/*
-----------------------------------------------------------------------------
Copyright (c) 2010 Tippett Studio
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
-----------------------------------------------------------------------------
*/

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Playlist.h>
#include <Shotgun/Note.h>
#include <Shotgun/Daily.h>

namespace Shotgun {

// *****************************************************************************
Playlist::Playlist(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Playlist";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Playlist::Playlist()
    : Entity(NULL)
{
    m_type = "Playlist";
    m_attrs = NULL;
}

// *****************************************************************************
Playlist::Playlist(const Playlist &ref)
    : Entity(ref.m_sg)
{
    m_type = "Playlist";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Playlist::~Playlist()
{
    // Nothing
}

// *****************************************************************************
Playlist Playlist::create(Shotgun *sg, 
                          const std::string &showCode,
                          const std::string &playlistName)
{
    // Check if the playlist already exists
    try
    {
        Playlist playlist = sg->findPlaylistByName(showCode, playlistName);

        std::string err = "Playlist \"" + playlistName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        Show show = sg->findShowByCode(showCode);

        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(show.asLink());
        attrsMap["code"] = toXmlrpcValue(playlistName);

        // Call the base class function to create an entity
        return Playlist(sg, createEntity(sg, "Playlist", attrsMap));
    }
}

// *****************************************************************************
Playlists Playlist::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create an Playlist for each of them
    Playlists playlists;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            playlists.push_back(Playlist(sg, result[i]));
        }
    }

    return playlists;
}

// *****************************************************************************
const Notes Playlist::sgNotes() const
{
    Notes notes;

    SgArray entities = getAttrValueAsMultiEntityAttrMap("notes");
    for (size_t i = 0; i < entities.size(); i++)
    {
        notes.push_back(Note(m_sg, entities[i]));
    }

    return notes;
}

// *****************************************************************************
const Dailies Playlist::sgDailies() const
{
    Dailies dailies;

    SgArray entities = getAttrValueAsMultiEntityAttrMap("versions");
    for (size_t i = 0; i < entities.size(); i++)
    {
        dailies.push_back(Daily(m_sg, entities[i]));
    }

    return dailies;
}

// *****************************************************************************
void Playlist::sgNotes(const Notes &val)
{
    SgArray noteLinkArray;

    for (size_t i = 0; i < val.size(); i++)
    {
        noteLinkArray.push_back(toXmlrpcValue(val[i].asLink()));
    }

    setAttrValue("notes", toXmlrpcValue(noteLinkArray));
}

// *****************************************************************************
void Playlist::sgNotes(const SgArray &val)
{
    for (size_t i = 0; i < val.size(); i++)
    {
        try
        {
            Entity::validateLink(val[i]);
        }
        catch (SgAttrLinkError &error)
        {
            throw SgAttrSetValueError("notes", error.what());
        }
    }

    setAttrValue("notes", toXmlrpcValue(val));
}

// *****************************************************************************
void Playlist::sgDailies(const Dailies &val)
{
    SgArray dailyLinkArray;

    for (size_t i = 0; i < val.size(); i++)
    {
        dailyLinkArray.push_back(toXmlrpcValue(val[i].asLink()));
    }

    setAttrValue("versions", toXmlrpcValue(dailyLinkArray));
}

// *****************************************************************************
void Playlist::sgDailies(const SgArray &val)
{
    for (size_t i = 0; i < val.size(); i++)
    {
        try
        {
            Entity::validateLink(val[i]);
        }
        catch (SgAttrLinkError &error)
        {
            throw SgAttrSetValueError("versions", error.what());
        }
    }

    setAttrValue("versions", toXmlrpcValue(val));
}

} // End namespace Shotgun
