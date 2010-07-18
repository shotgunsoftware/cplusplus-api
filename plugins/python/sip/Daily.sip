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
class Daily : Shotgun::Entity, Shotgun::NoteMixin
{
%TypeHeaderCode
    #include <Shotgun/Daily.h>
%End

protected:
    Daily(Shotgun::Shotgun *sg, const xmlrpc_c::value &attrs);

public:
    Daily();
    Daily(const Shotgun::Daily &ref);
    virtual ~Daily();

    // Get an attribute's value
    const std::string sgName() const throw(Shotgun::SgAttrError);
    const std::string sgCode() const throw(Shotgun::SgAttrError);
    const std::string sgAuthor() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
// TODO: Implement in non-Tippett way
//    const std::string sgShotName() const throw(Shotgun::SgAttrError);
    const Shotgun::Shot sgShot() const throw(Shotgun::SgAttrError);
    const std::string sgDepartment() const throw(Shotgun::SgAttrError);
    const std::string sgDescription() const throw(Shotgun::SgAttrError);
    const std::string sgSequenceName() const throw(Shotgun::SgAttrError);
    const Shotgun::Sequence sgSequence() const throw(Shotgun::SgAttrError);
    const std::string sgVersion() const throw(Shotgun::SgAttrError);
    const size_t sgFrameCount() const throw(Shotgun::SgAttrError);
    const std::string sgFrameRange() const throw(Shotgun::SgAttrError);
    const std::string sgSource() const throw(Shotgun::SgAttrError);
    const std::string sgSource2k() const throw(Shotgun::SgAttrError);
    const bool sgIsHD() const throw(Shotgun::SgAttrError);
    const std::string sgQuicktimePath() const throw(Shotgun::SgAttrError);
    const std::string sgQuicktimeURL() const throw(Shotgun::SgAttrError);
    const std::string sgHDQuicktimePath() const throw(Shotgun::SgAttrError);
    const std::string sgHDQuicktimeURL() const throw(Shotgun::SgAttrError);
    const std::string sgThumbnailPath() const throw(Shotgun::SgAttrError);
    const std::string sgReviewStatus() const throw(Shotgun::SgAttrError);
    //TODO: void sgReviewStatus(const std::string &status) throw(Shotgun::SgAttrError);
    const std::string sgStatus() const throw(Shotgun::SgAttrError);
    const bool sgIsEPK() const throw(Shotgun::SgAttrError);
    const int sgViewOrder() const throw(Shotgun::SgAttrError);
    const std::string sgDateReviewed() const throw(Shotgun::SgAttrError);

    // ------------------------------------------------------------------------
    // Add a /Factory/ annotation which specifies that the value returned by
    // the function (which should be a wrapped C structure or C++ class instance)
    // is a newly created instance and is owned by Python.
    // ------------------------------------------------------------------------
    Shotgun::Entity *sgLink() throw(Shotgun::SgAttrError, Shotgun::SgEntityError) /Factory/;
    const std::string sgLinkEntityType() const throw(Shotgun::SgAttrError);

    // Set an attribute's value
    void sgReviewStatus(const std::string &val) throw(Shotgun::SgAttrError);
};

}; // End namespace Shotgun - IMPORTANT: has to have the semi-colon
