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
class Note : Shotgun::Entity
{
%TypeHeaderCode
    #include <Shotgun/Note.h>
%End

protected:
    Note(Shotgun::Shotgun *sg, const xmlrpc_c::value &attrs);

public:
    Note();
    Note(const Shotgun::Note &ref);
    virtual ~Note();

    const std::string sgAuthor() const throw(Shotgun::SgAttrError);
    const std::string sgBody() const throw(Shotgun::SgAttrError);
    const Shotgun::SgArray sgCc() const throw(Shotgun::SgAttrError);
    const Shotgun::SgArray sgTo() const throw(Shotgun::SgAttrError);
    const std::string sgStatus() const throw(Shotgun::SgAttrError);
    const std::string sgSubject() const throw(Shotgun::SgAttrError);
    const std::string sgName() const throw(Shotgun::SgAttrError);
    const std::string sgType() const throw(Shotgun::SgAttrError);
    const Shotgun::SgArray sgLinks() const throw(Shotgun::SgAttrError);

    const Shotgun::Review getLinkedReview() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    const Shotgun::Shot getLinkedShot() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    const Shotgun::Daily getLinkedDaily() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
};

}; // End namespace Shotgun - IMPORTANT: has to have the semi-colon
