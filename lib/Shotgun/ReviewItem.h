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

#ifndef __REVIEW_ITEM_H__
#define __REVIEW_ITEM_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Version.h>
#include <Shotgun/Shot.h>
#include <Shotgun/Review.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class ReviewItem : public Entity
{
    friend class Shotgun;
    friend class Entity;
 
protected:
    ReviewItem(Shotgun *sg, const xmlrpc_c::value &attrs);

    static ReviewItem create(Shotgun *sg, 
                             const std::string &projectCode,
                             //const std::string &reviewItemName, // read-only 
                             const SgMap &reviewItemShotLink,
                             const SgMap &reviewItemDailyLink,
                             const SgMap &reviewItemReviewLink,
                             const std::string &reviewItemPurpose = "",
                             const int reviewItemOrder = TIPSHOTGUN_INVALID_ORDER_NUM);
    static ReviewItems find(Shotgun *sg, SgMap &findMap);
    
public:
    ReviewItem();
    ReviewItem(const ReviewItem &ref);
    virtual ~ReviewItem();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); } 
    const Review sgReview() const { return Review(m_sg, getAttrValueAsEntityAttrMap("sg_review")); }
    const std::string sgPurpose() const { return getAttrValueAsString("sg_purpose"); }
    const int sgOrder() const { return getAttrValueAsInt("sg_order"); }
    const std::string sgReviewedBy() const { return getAttrValueAsString("sg_reviewed_by"); } 
    const std::string sgDateReviewed() const { return getAttrValueAsString("sg_date_reviewed"); }
    const bool sgApproved() const { return getAttrValueAsBool("sg_approved_"); } 
   
    // ------------------------------------------------------------------------
    // IMPORTANT:
    // (1) C++ - user must be responsible for deleting the pointers in C++ app.
    // (2) Python - the ownership has been transferred to Python by using the
    //     /Factory/ annotation.
    // ------------------------------------------------------------------------
    Entity *sgLink() { return getAttrValueAsEntityPtr("sg_link"); }
    const std::string sgLinkEntityType() const { return linkEntityType("sg_link"); }

    // Set an attribute's value
    void sgDateReviewed(const std::string &val) { setAttrValue("sg_date_reviewed", toXmlrpcValue(val)); }

    ReviewItem &operator=(const ReviewItem &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __REVIEW_ITEM_H__
