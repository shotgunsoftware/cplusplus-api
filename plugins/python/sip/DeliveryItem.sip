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
class DeliveryItem : Shotgun::Entity
{
%TypeHeaderCode
    #include <Shotgun/DeliveryItem.h>
%End

protected:
    DeliveryItem(Shotgun::Shotgun *sg, const xmlrpc_c::value &attrs);

public:
    DeliveryItem();
    DeliveryItem(const Shotgun::DeliveryItem &ref);
    virtual ~DeliveryItem();

    // Get an attribute's value
    const std::string sgName() const throw(Shotgun::SgAttrError);
    const Shotgun::Asset sgAsset() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    const Shotgun::Delivery sgDelivery() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    const std::string sgStagingStatus() const throw(Shotgun::SgAttrError);
    const std::string sgStagingQt() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    const std::string sgProcessingStatus() const throw(Shotgun::SgAttrError);
    const std::string sgQualityControlStatus() const throw(Shotgun::SgAttrError);
    const std::string sgDataSize() const throw(Shotgun::SgAttrError);
    const std::string sgFiles() const throw(Shotgun::SgAttrError);
    const std::string sgNotes() const throw(Shotgun::SgAttrError);
    const int sgPriority() const throw(Shotgun::SgAttrError);
    const std::string sgProcessingType() const throw(Shotgun::SgAttrError);
    const std::string sgPublishType() const throw(Shotgun::SgAttrError);
    const Shotgun::Sequence sgSequence() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    const Shotgun::Shot sgShot() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    const std::string sgTippettName() const throw(Shotgun::SgAttrError);
    const std::string sgTippettPath() const throw(Shotgun::SgAttrError);
    const int sgTippettStartFrame() const throw(Shotgun::SgAttrError);
    const std::string sgWranglerNotes() const throw(Shotgun::SgAttrError);
    const std::string sgPath() const throw(Shotgun::SgAttrError);

    // Set an attribute's value
    void sgName(const std::string &val) throw(Shotgun::SgAttrError);
    void sgAsset(const Shotgun::Asset &val) throw(Shotgun::SgAttrError);
    void sgAsset(const Shotgun::SgMap &val) throw(Shotgun::SgAttrError);
    void sgDelivery(const Shotgun::Delivery &val) throw(Shotgun::SgAttrError);
    void sgDelivery(const Shotgun::SgMap &val) throw(Shotgun::SgAttrError);
    void sgStagingStatus(const std::string &val) throw(Shotgun::SgAttrError);
    void sgStagingQt(const std::string &val) throw(Shotgun::SgAttrError);
    void sgProcessingStatus(const std::string &val) throw(Shotgun::SgAttrError);
    void sgQualityControlStatus(const std::string &val) throw(Shotgun::SgAttrError);
    void sgDataSize(const std::string &val) throw(Shotgun::SgAttrError);
    void sgFiles(const std::string &val) throw(Shotgun::SgAttrError);
    void sgNotes(const std::string &val) throw(Shotgun::SgAttrError);
    void sgPriority(const int val) throw(Shotgun::SgAttrError);
    void sgProcessingType(const std::string &val) throw(Shotgun::SgAttrError);
    void sgPublishType(const std::string &val) throw(Shotgun::SgAttrError);
    void sgSequence(const Shotgun::Sequence &val) throw(Shotgun::SgAttrError);
    void sgSequence(const Shotgun::SgMap &val) throw(Shotgun::SgAttrError);
    void sgShot(const Shotgun::Shot &val) throw(Shotgun::SgAttrError);
    void sgShot(const Shotgun::SgMap &val) throw(Shotgun::SgAttrError);
    void sgTippettName(const std::string &val) throw(Shotgun::SgAttrError);
    void sgTippettPath(const std::string &val) throw(Shotgun::SgAttrError);
    void sgTippettStartFrame(const int val) throw(Shotgun::SgAttrError);
    void sgWranglerNotes(const std::string &val) throw(Shotgun::SgAttrError);
};

}; // End namespace Shotgun - must have the semi-colon
