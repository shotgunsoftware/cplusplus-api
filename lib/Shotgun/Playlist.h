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

#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

#include <Shotgun/Entity.h>
#include <Shotgun/Version.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Playlist : public Entity
{
    friend class Shotgun;
 
public:
    Playlist(const Playlist &ref);
    virtual ~Playlist();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); }
    const std::string sgDescription() const { return getAttrValueAsString("description"); }
    const std::string sgThumbnail() const { return getAttrValueAsString("image"); }
    const Strings sgTags() const { return getAttrValueAsTags("tag_list"); }
    const NotePtrs sgNotes() const;
    const VersionPtrs sgVersions() const;

    // Set an attribute's value
    void sgName(const std::string &val) { setAttrValue("code", toXmlrpcValue(val)); }
    void sgDescription(const std::string &val) { setAttrValue("description", toXmlrpcValue(val)); }
    void sgTags(const Strings &val) { setAttrValue("tag_list", toXmlrpcValue(val)); }
    void sgNotes(const Notes &val);  // An array of Note entities
    void sgNotes(const SgArray &val);  // An array of entity links
    void sgVersions(const Versions &val);  // An array of Version entities
    void sgVersions(const SgArray &val);  // An array of entity links

    static std::string type() { return std::string("Playlist"); }

    Playlist &operator=(const Playlist &that)
    {
        Entity::operator=(that);
        return *this;
    }

protected:
    Playlist(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Entity *factory(Shotgun *sg, const xmlrpc_c::value &attrs) { return new Playlist(sg, attrs); }
    static Playlist create(Shotgun *sg,
                           const std::string &projectCode,
                           const std::string &playlistName);

    static SgArray populateReturnFields(const SgArray &extraReturnFields = SgArray());
};

} // End namespace Shotgun

#endif    // End #ifdef __PLAYLIST_H__
