//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#include <iostream>

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Review.h>
#include <Shotgun/Show.h>

namespace Shotgun {

// *****************************************************************************
Review::Review(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Review";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Review::Review()
    : Entity(NULL)
{
    m_type = "Review";
    m_attrs = NULL;
}

// *****************************************************************************
Review::Review(const Review &ref)
    : Entity(ref.m_sg)
{
    m_type = "Review";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Review::~Review()
{
    // Nothing
}

// *****************************************************************************
Review Review::create(Shotgun *sg, 
                      const std::string &showCode,
                      const std::string &reviewName,
                      const std::string &reviewType)
{
    // Check if the review already exists
    try
    {
        Review review = sg->findReviewByName(showCode, reviewName);

        std::string err = "Review \"" + reviewName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        Show show = sg->findShowByCode(showCode);

        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(show.asLink());
        attrsMap["code"] = toXmlrpcValue(reviewName);
        attrsMap["sg_review_type"] = toXmlrpcValue(reviewType);

        // Call the base class function to create an entity
        return Review(sg, createEntity(sg, "Review", attrsMap));
    }
}

// *****************************************************************************
Reviews Review::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create a Review for each of them
    Reviews reviews;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            reviews.push_back(Review(sg, result[i]));
        }
    }

    return reviews;
}

} // End namespace Shotgun
