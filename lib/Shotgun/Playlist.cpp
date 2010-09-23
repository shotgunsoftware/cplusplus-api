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

namespace Shotgun {

// *****************************************************************************
Playlist::Playlist(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Playlist";
    m_attrs = new xmlrpc_c::value(attrs);
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
Playlist *Playlist::create(Shotgun *sg, 
                           const std::string &projectCode,
                           const std::string &playlistName)
{
    // Check if the playlist already exists
    try
    {
        Playlist *playlist = sg->findPlaylistByName(projectCode, playlistName);
        delete playlist;

        std::string err = "Playlist \"" + playlistName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(sg->getProjectLink(projectCode));
        attrsMap["code"] = toXmlrpcValue(playlistName);

        return sg->createEntity<Playlist>(Dict(attrsMap));
    }
}

// *****************************************************************************
SgArray Playlist::populateReturnFields(const SgArray &extraReturnFields)
{
    SgArray returnFields = extraReturnFields;

    returnFields.push_back(toXmlrpcValue("id"));
    returnFields.push_back(toXmlrpcValue("project"));
    returnFields.push_back(toXmlrpcValue("created_at"));
    returnFields.push_back(toXmlrpcValue("updated_at"));

    returnFields.push_back(toXmlrpcValue("code"));
    returnFields.push_back(toXmlrpcValue("sg_date_and_time"));
    returnFields.push_back(toXmlrpcValue("description"));
    returnFields.push_back(toXmlrpcValue("notes"));
    returnFields.push_back(toXmlrpcValue("tag_list"));
    returnFields.push_back(toXmlrpcValue("image"));
    returnFields.push_back(toXmlrpcValue("versions"));

    return returnFields;
}

// *****************************************************************************
const NotePtrs Playlist::sgNotes() const
{
    NotePtrs notes;

    EntityPtrs entities = getAttrValueAsMultiEntityPtr("notes");
    for (size_t i = 0; i < entities.size(); i++)
    {
        if (Note *note = dynamic_cast<Note *>(entities[i]))
        {
            notes.push_back(note);
        }
    }

    return notes;
}

// *****************************************************************************
const VersionPtrs Playlist::sgVersions() const
{
    VersionPtrs versions;

    EntityPtrs entities = getAttrValueAsMultiEntityPtr("versions");
    for (size_t i = 0; i < entities.size(); i++)
    {
        if (Version *version = dynamic_cast<Version *>(entities[i]))
        {
            versions.push_back(version);
        }
    }

    return versions;
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
void Playlist::sgVersions(const Versions &val)
{
    SgArray versionLinkArray;

    for (size_t i = 0; i < val.size(); i++)
    {
        versionLinkArray.push_back(toXmlrpcValue(val[i].asLink()));
    }

    setAttrValue("versions", toXmlrpcValue(versionLinkArray));
}

// *****************************************************************************
void Playlist::sgVersions(const SgArray &val)
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

// *****************************************************************************
std::string toStdString(const Shotgun::Playlist &playlist)
{
    return toStdString(playlist.attrs());
}

// *****************************************************************************
std::string toStdString(const Shotgun::Playlists &playlists)
{
    Shotgun::SgArray array;
    for (size_t i = 0; i < playlists.size(); i++)
    {
        array.push_back(playlists[i].attrs());
    }
    
    return toStdString(Shotgun::toXmlrpcValue(array));
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Playlist &playlist)
{
    output << toStdString(playlist);
    return output;
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Playlists &playlists)
{
    output << toStdString(playlists);
    return output;
}
