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

#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Element : public Entity
{
    friend class Shotgun;
    friend class Shot;
    friend class Asset;
    friend class Entity;
 
public:
    Element(const Element &ref);
    virtual ~Element();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); } 
    const Assets sgAssets() const;
    const Shots sgShots() const;
    const Strings sgTags() const { return getAttrValueAsTags("tag_list"); } 
    const std::string sgType() const { return getAttrValueAsString("sg_element_type"); }

    // Set an attribute's value
    void sgAssets(const Assets &val);
    void sgAssets(const SgArray &val);
    void sgShots(const Shots &val);
    void sgShots(const SgArray &val); // An array of entity links
    void sgTags(const Strings &val) { setAttrValue("tag_list", toXmlrpcValue(val)); }
    void sgType(const std::string &val) { setAttrValue("sg_element_type", toXmlrpcValue(val)); }

    Element &operator=(const Element &that)
    {
        Entity::operator=(that);
        return *this;
    }

protected:
    Element(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Element create(Shotgun *sg, 
                          const std::string &projectCode,
                          const std::string &elementName,
                          const std::string &elementType);
    static Elements find(Shotgun *sg, SgMap &findMap);

};

} // End namespace Shotgun

#endif    // End #ifdef __ELEMENT_H__
