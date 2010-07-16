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

#ifndef __DAILY_H__
#define __DAILY_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>
#include <Shotgun/NoteMixin.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Daily : public Entity, public NoteMixin
{
    friend class Shotgun;
    friend class Shot;
    friend class ReviewItem;
    friend class Note;
    friend class Playlist;
    friend class Entity;
 
protected:
    Daily(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Daily create(Shotgun *sg, const std::string &dailyName);
    static Dailies find(Shotgun *sg, SgMap &findMap);
    
public:
    Daily();
    Daily(const Daily &ref);
    virtual ~Daily();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); }
    const std::string sgCode() const { return sgName(); }
    const std::string sgAuthor() const { return getAttrValueAsUserLogin("user"); }
#warning TODO: Implement in non-Tippett way
//    const std::string sgShotName() const { return (TipUtil::DailyName(getAttrValueAsString("code"))).shot(); }
    const Shot sgShot() const; 
    const std::string sgDepartment() const { return getAttrValueAsString("sg_department"); }
    const std::string sgDescription() const { return getAttrValueAsString("description"); }
    const std::string sgSequenceName() const { return getAttrValueAsString("sg_sequence"); }
    const Sequence sgSequence() const;
    const std::string sgVersion() const { return getAttrValueAsString("sg_rev"); }
    const size_t sgFrameCount() const { return getAttrValueAsInt("frame_count"); }
    const std::string sgFrameRange() const { return getAttrValueAsString("frame_range"); }
    const std::string sgSource() const { return getAttrValueAsString("sg_source"); }
    const std::string sgSource2k() const { return getAttrValueAsString("sg_source_2k"); }
    const bool sgIsHD() const { return (getAttrValueAsString("sg_daily_hd") == "Yes") ? true : false; }
    const std::string sgQuicktimePath() const { return getAttrValueAsQtPath("sg_preview_qt"); }
    const std::string sgQuicktimeURL() const { return getAttrValueAsQtURL("sg_preview_qt"); }
    const std::string sgHDQuicktimePath() const { return getAttrValueAsQtPath("sg_preview_hd_qt"); }
    const std::string sgHDQuicktimeURL() const { return getAttrValueAsQtURL("sg_preview_hd_qt"); }
    const std::string sgThumbnailPath() const { return getAttrValueAsString("image"); /*TODO: This doesn't work yet.*/ }
    const std::string sgReviewStatus() const { return getAttrValueAsString("sg_status"); }
    const std::string sgStatus() const { return getAttrValueAsString("sg_status_list"); }
    const bool sgIsEPK() const { return (getAttrValueAsString("sg_epk_") == "Yes") ? true : false; }
    const int sgViewOrder() const { return getAttrValueAsInt("sg_view_order"); }
    const std::string sgDateReviewed() const { return getAttrValueAsString("sg_dailies_date"); }

    // ------------------------------------------------------------------------
    // IMPORTANT:
    // (1) C++ - user must be responsible for deleting the pointers in C++ app.
    // (2) Python - the ownership has been transferred to Python by using the
    //     /Factory/ annotation.
    // ------------------------------------------------------------------------
    Entity *sgLink() { return getAttrValueAsEntityPtr("entity"); } 
    const std::string sgLinkEntityType() const { return linkEntityType("entity"); }
    
    // Set an attribute's value
    void sgReviewStatus(const std::string &val) { setAttrValue("sg_status", toXmlrpcValue(val)); }

    Daily &operator=(const Daily &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __DAILY_H__
