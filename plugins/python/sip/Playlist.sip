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

namespace Shotgun {

// *****************************************************************************
class Playlist : Shotgun::Entity
{
%TypeHeaderCode
    #include <Shotgun/Playlist.h>
%End

public:
    Playlist(const Shotgun::Playlist &ref);
    virtual ~Playlist();

    // Get an attribute's value
    const std::string sgName() const throw(Shotgun::SgAttrError);
    const std::string sgDescription() const throw(Shotgun::SgAttrError);
    const std::string sgThumbnail() const throw(Shotgun::SgAttrError);
    const Shotgun::Strings sgTags() const throw(Shotgun::SgAttrError);
    const Shotgun::Notes sgNotes() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    const Shotgun::Versions sgVersions() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError);

    // Set an attribute's value
    void sgName(const std::string &val) throw(Shotgun::SgAttrError);
    void sgDescription(const std::string &val) throw(Shotgun::SgAttrError);
    void sgTags(const Shotgun::Strings &val) throw(Shotgun::SgAttrError);
    void sgNotes(const Shotgun::Notes &val) throw(Shotgun::SgAttrError); 
    void sgNotes(const Shotgun::SgArray &val) throw(Shotgun::SgAttrError);
    void sgVersions(const Shotgun::Versions &val) throw(Shotgun::SgAttrError);
    void sgVersions(const Shotgun::SgArray &val) throw(Shotgun::SgAttrError);

protected:
    Playlist(Shotgun::Shotgun *sg, const xmlrpc_c::value &attrs);
};

}; // End namespace Shotgun - must have the semi-colon
