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

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/ReviewItem.h>
#include <Shotgun/Project.h>

namespace Shotgun {

// *****************************************************************************
ReviewItem::ReviewItem(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "ReviewItem";
    m_attrs = new xmlrpc_c::value(attrs);
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
ReviewItem *ReviewItem::create(Shotgun *sg, 
                               const std::string &projectCode,
                               const std::string &reviewItemName)
{
    // Check if the reviewItem already exists
    try
    {
        ReviewItem *reviewItem = sg->findReviewItemByName(projectCode, reviewItemName);
        delete reviewItem;

        std::string err = "ReviewItem \"" + reviewItemName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(sg->getProjectLink(projectCode));
        attrsMap["code"] = toXmlrpcValue(reviewItemName); 

        return sg->createEntity<ReviewItem>(Dict(attrsMap));
    }
}

// *****************************************************************************
SgArray ReviewItem::populateReturnFields(const SgArray &extraReturnFields)
{
    SgArray returnFields = extraReturnFields;

    returnFields.push_back(toXmlrpcValue("id"));
    returnFields.push_back(toXmlrpcValue("project"));
    returnFields.push_back(toXmlrpcValue("created_at"));
    returnFields.push_back(toXmlrpcValue("updated_at"));

    returnFields.push_back(toXmlrpcValue("code"));
    returnFields.push_back(toXmlrpcValue("sg_version"));
    returnFields.push_back(toXmlrpcValue("sg_link"));
    returnFields.push_back(toXmlrpcValue("sg_review"));
    returnFields.push_back(toXmlrpcValue("sg_purpose"));
    returnFields.push_back(toXmlrpcValue("sg_order"));
    returnFields.push_back(toXmlrpcValue("sg_reviewed_by"));
    returnFields.push_back(toXmlrpcValue("sg_date_reviewed"));
    returnFields.push_back(toXmlrpcValue("sg_approved_"));

    return returnFields;
}

} // End namespace Shotgun
