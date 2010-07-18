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
class Reference : Shotgun::Entity
{
%TypeHeaderCode
    #include <Shotgun/Reference.h>
%End
 
protected:
    Reference(Shotgun::Shotgun *sg, const xmlrpc_c::value &attrs);

public:
    Reference();
    Reference(const Shotgun::Reference &ref);
    virtual ~Reference();

    // Get an attribute's value
    const std::string sgName() const throw(Shotgun::SgAttrError);
    const std::string sgChecksum() const throw(Shotgun::SgAttrError);
    const bool sgHero() const throw(Shotgun::SgAttrError);
    const bool sgRemove() const throw(Shotgun::SgAttrError);
    const Shotgun::Asset sgAsset() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    const Shotgun::Sequence sgSequence() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    const Shotgun::Shot sgShot() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    const std::string sgPurpose() const throw(Shotgun::SgAttrError);
    const Shotgun::Strings sgTags() const throw(Shotgun::SgAttrError);

    // Set an attribute's value
    void sgChecksum(const std::string &val) throw(Shotgun::SgAttrError);
    void sgHero(const bool val) throw(Shotgun::SgAttrError);
    void sgRemove(const bool val) throw(Shotgun::SgAttrError);
    void sgAsset(const Shotgun::Asset &val) throw(Shotgun::SgAttrError);
    void sgAsset(const Shotgun::SgMap &val) throw(Shotgun::SgAttrError);
    void sgSequence(const Shotgun::Sequence &val) throw(Shotgun::SgAttrError);
    void sgSequence(const Shotgun::SgMap &val) throw(Shotgun::SgAttrError);
    void sgShot(const Shotgun::Shot &val) throw(Shotgun::SgAttrError);
    void sgShot(const Shotgun::SgMap &val) throw(Shotgun::SgAttrError);
    void sgPurpose(const std::string &val) throw(Shotgun::SgAttrError);
    void sgTags(const Shotgun::Strings &val) throw(Shotgun::SgAttrError);
};

}; // End namespace Shotgun - must have the semi-colon
