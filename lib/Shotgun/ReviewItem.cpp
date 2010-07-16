//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/ReviewItem.h>
#include <Shotgun/Show.h>

namespace Shotgun {

// *****************************************************************************
ReviewItem::ReviewItem(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "ReviewItem";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
ReviewItem::ReviewItem()
    : Entity(NULL)
{
    m_type = "ReviewItem";
    m_attrs = NULL;
}

// *****************************************************************************
ReviewItem::ReviewItem(const ReviewItem &ref)
    : Entity(ref.m_sg)
{
    m_type = "ReviewItem";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
ReviewItem::~ReviewItem()
{
    // Nothing
}

// *****************************************************************************
ReviewItem ReviewItem::create(Shotgun *sg, 
                              const std::string &showCode,
                              //const std::string &reviewItemName, // read-only
                              const SgMap &reviewItemShotLink,
                              const SgMap &reviewItemDailyLink,
                              const SgMap &reviewItemReviewLink,
                              const std::string &reviewItemPurpose,
                              const int reviewItemOrder)
{
    // Check if the reviewItem already exists
    try
    {
        std::string reviewItemName = getAttrValueAsString("name", reviewItemDailyLink);
        ReviewItem reviewItem = sg->findReviewItemByName(showCode, reviewItemName);

        std::string err = "ReviewItem \"" + reviewItemName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        Show show = sg->findShowByCode(showCode);

        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(show.asLink());
        // Attribute "code" is read-only, I think it's filled in automatically 
        // based on the "sg_version" link.
        //attrsMap["code"] = toXmlrpcValue(reviewItemName); 
        attrsMap["sg_link"] = toXmlrpcValue(reviewItemShotLink);
        attrsMap["sg_version"] = toXmlrpcValue(reviewItemDailyLink);
        attrsMap["sg_review"] = toXmlrpcValue(reviewItemReviewLink);
        attrsMap["sg_purpose"] = toXmlrpcValue(reviewItemPurpose);

        if (reviewItemOrder != TIPSHOTGUN_INVALID_ORDER_NUM)
        {
            attrsMap["sg_order"] = toXmlrpcValue(reviewItemOrder);
        }

        // Call the base class function to create an entity
        return ReviewItem(sg, createEntity(sg, "ReviewItem", attrsMap));
    }
}

// *****************************************************************************
ReviewItems ReviewItem::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create a ReviewItem for each of them
    ReviewItems reviewItems;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            reviewItems.push_back(ReviewItem(sg, result[i]));
        }
    }

    return reviewItems;
}

} // End namespace Shotgun
