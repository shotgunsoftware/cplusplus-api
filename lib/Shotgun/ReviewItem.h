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
 
public:
    ReviewItem(const ReviewItem &ref);
    virtual ~ReviewItem();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); } 
   
    // ------------------------------------------------------------------------
    // IMPORTANT:
    // (1) C++ - user must be responsible for deleting the pointers in C++ app.
    // (2) Python - the ownership has been transferred to Python by using the
    //     /Factory/ annotation.
    // ------------------------------------------------------------------------
    const Entity *sgLink() const { return getAttrValueAsEntityPtr("sg_link"); }
    const std::string sgLinkEntityType() const { return linkEntityType("sg_link"); }

    static std::string type() { return std::string("ReviewItem"); }

    ReviewItem &operator=(const ReviewItem &that)
    {
        Entity::operator=(that);
        return *this;
    }

protected:
    ReviewItem(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Entity *factory(Shotgun *sg, const xmlrpc_c::value &attrs) { return new ReviewItem(sg, attrs); }
    static List populateReturnFields();
};

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::ReviewItem &reviewItem);
std::ostream& operator<<(std::ostream &output, const Shotgun::ReviewItem &reviewItem);

#endif    // End #ifdef __REVIEW_ITEM_H__
