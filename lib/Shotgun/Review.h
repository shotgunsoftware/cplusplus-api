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

#ifndef __REVIEW_H__
#define __REVIEW_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Review : public Entity
{
    friend class Shotgun;
    friend class ReviewItem;
    friend class Note;
    friend class Entity;
 
protected:
    Review(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Review create(Shotgun *sg, 
                         const std::string &showCode,
                         const std::string &reviewName,
                         const std::string &reviewType);
    static Reviews find(Shotgun *sg, SgMap &findMap);
    
public:
    Review();
    Review(const Review &ref);
    virtual ~Review();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); } 
    const std::string sgType() const { return getAttrValueAsString("sg_review_type"); }
    const std::string sgMedia() const { return getAttrValueAsString("sg_review_media"); } 
    const std::string sgDateSent() const { return getAttrValueAsString("sg_review_date_sent"); } 
    const std::string sgSentTo() const { return getAttrValueAsString("sg_review_sent_to"); } 
    const std::string sgDateReviewed() const { return getAttrValueAsString("sg_review_date_reviewed"); } 
    const std::string sgReviewedBy() const { return getAttrValueAsString("sg_review_reviewed_by"); } 
    const std::string sgDisclaimers() const { return getAttrValueAsString("sg_review_disclaimers"); } 
    const std::string sgTipSupeNotes() const { return getAttrValueAsString("sg_review_tipsupe_notes"); } 
    const std::string sgClientNotes() const { return getAttrValueAsString("sg_review_client_notes"); } 
   
    // Set an attribute's value
    void sgMedia(const std::string &val) { setAttrValue("sg_review_media", toXmlrpcValue(val)); }
    void sgDateSent(const std::string &val) { setAttrValue("sg_review_date_sent", toXmlrpcValue(val)); }
    void sgSentTo(const std::string &val) { setAttrValue("sg_review_sent_to", toXmlrpcValue(val)); }
    void sgDateReviewed(const std::string &val) { setAttrValue("sg_review_date_reviewed", toXmlrpcValue(val)); }
    void sgReviewedBy(const std::string &val) { setAttrValue("sg_review_reviewed_by", toXmlrpcValue(val)); }
    void sgDisclaimers(const std::string &val) { setAttrValue("sg_review_disclaimers", toXmlrpcValue(val)); }
    void sgTipSupeNotes(const std::string &val) { setAttrValue("sg_review_tipsupe_notes", toXmlrpcValue(val)); }
    void sgClientNotes(const std::string &val) { setAttrValue("sg_review_client_notes", toXmlrpcValue(val)); }

    Review &operator=(const Review &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __REVIEW_H__
