//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#ifndef __REVIEW_ITEM_H__
#define __REVIEW_ITEM_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Daily.h>
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
                             const std::string &showCode,
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
    const Daily sgDaily() const { return Daily(m_sg, getAttrValueAsEntityAttrMap("sg_version")); }
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
