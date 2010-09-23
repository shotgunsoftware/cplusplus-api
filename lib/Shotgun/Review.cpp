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

#include <iostream>

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Review.h>
#include <Shotgun/Project.h>

namespace Shotgun {

// *****************************************************************************
Review::Review(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Review";
    m_attrs = new xmlrpc_c::value(attrs);
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
Review *Review::create(Shotgun *sg, 
                       const std::string &projectCode,
                       const std::string &reviewName)
{
    // Check if the review already exists
    try
    {
        Review *review = sg->findReviewByName(projectCode, reviewName);
        delete review;

        std::string err = "Review \"" + reviewName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(sg->getProjectLink(projectCode));
        attrsMap["code"] = toXmlrpcValue(reviewName);

        return sg->createEntity<Review>(Dict(attrsMap));
    }
}

// *****************************************************************************
SgArray Review::populateReturnFields(const SgArray &extraReturnFields)
{
    SgArray returnFields = extraReturnFields;

    returnFields.push_back(toXmlrpcValue("id"));
    returnFields.push_back(toXmlrpcValue("project"));
    returnFields.push_back(toXmlrpcValue("created_at"));
    returnFields.push_back(toXmlrpcValue("updated_at"));

    returnFields.push_back(toXmlrpcValue("code"));
    returnFields.push_back(toXmlrpcValue("sg_review_type"));
    returnFields.push_back(toXmlrpcValue("sg_review_media"));
    returnFields.push_back(toXmlrpcValue("sg_review_date_sent"));
    returnFields.push_back(toXmlrpcValue("sg_review_sent_to"));
    returnFields.push_back(toXmlrpcValue("sg_review_date_reviewed"));
    returnFields.push_back(toXmlrpcValue("sg_review_reviewed_by"));
    returnFields.push_back(toXmlrpcValue("sg_review_disclaimers"));
    returnFields.push_back(toXmlrpcValue("sg_review_tipsupe_notes"));
    returnFields.push_back(toXmlrpcValue("sg_review_client_notes"));

    return returnFields;
}

} // End namespace Shotgun

// *****************************************************************************
std::string toStdString(const Shotgun::Review &review)
{
    return toStdString(review.attrs());
}

// *****************************************************************************
std::string toStdString(const Shotgun::Reviews &reviews)
{
    Shotgun::SgArray array;
    for (size_t i = 0; i < reviews.size(); i++)
    {
        array.push_back(reviews[i].attrs());
    }
    
    return toStdString(Shotgun::toXmlrpcValue(array));
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Review &review)
{
    output << toStdString(review);
    return output;
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Reviews &reviews)
{
    output << toStdString(reviews);
    return output;
}
