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
class Review : Shotgun::Entity
{
%TypeHeaderCode
    #include <Shotgun/Review.h>
%End

protected:
    Review(Shotgun::Shotgun *sg, const xmlrpc_c::value &attrs);

public:
    Review();
    Review(const Shotgun::Review &ref);
    virtual ~Review();

    // Get an attribute's value
    const std::string sgName() const throw(Shotgun::SgAttrError);
    const std::string sgType() const throw(Shotgun::SgAttrError);
    const std::string sgMedia() const throw(Shotgun::SgAttrError);
    const std::string sgDateSent() const throw(Shotgun::SgAttrError);
    const std::string sgSentTo() const throw(Shotgun::SgAttrError);
    const std::string sgDateReviewed() const throw(Shotgun::SgAttrError);
    const std::string sgReviewedBy() const throw(Shotgun::SgAttrError);
    const std::string sgDisclaimers() const throw(Shotgun::SgAttrError);
    const std::string sgTipSupeNotes() const throw(Shotgun::SgAttrError);
    const std::string sgClientNotes() const throw(Shotgun::SgAttrError);

    // Set an attribute's value
    void sgMedia(const std::string &val) throw(Shotgun::SgAttrError);
    void sgDateSent(const std::string &val) throw(Shotgun::SgAttrError);
    void sgSentTo(const std::string &val) throw(Shotgun::SgAttrError);
    void sgDateReviewed(const std::string &val) throw(Shotgun::SgAttrError);
    void sgReviewedBy(const std::string &val) throw(Shotgun::SgAttrError);
    void sgDisclaimers(const std::string &val) throw(Shotgun::SgAttrError);
    void sgTipSupeNotes(const std::string &val) throw(Shotgun::SgAttrError);
    void sgClientNotes(const std::string &val) throw(Shotgun::SgAttrError);
};

}; // End namespace Shotgun - IMPORTANT: must have the semi-colon
