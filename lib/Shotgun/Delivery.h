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

#ifndef __DELIVERY_H__
#define __DELIVERY_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Delivery : public Entity
{
    friend class Shotgun;
    friend class DeliveryItem;
    friend class Entity;
 
protected:
    Delivery(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Delivery create(Shotgun *sg, 
                           const std::string &showCode,
                           const std::string &deliveryName);
    static Deliveries find(Shotgun *sg, SgMap &findMap);
    
public:
    Delivery();
    Delivery(const Delivery &ref);
    virtual ~Delivery();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("title"); } 
    const std::string sgDataSize() const { return getAttrValueAsString("sg_delivery_data_size"); } 
    const std::string sgNotes() const { return getAttrValueAsString("sg_delivery_notes"); } 
    const std::string sgPath() const { return getAttrValueAsString("sg_delivery_path"); } 
    const std::string sgOriginalPath() const { return getAttrValueAsString("sg_delivery_staged_path"); } 
    const std::string sgStagedPath() const { return sgOriginalPath(); }
    const std::string sgStatus() const { return getAttrValueAsString("sg_delivery_status"); } 
    const std::string sgType() const { return getAttrValueAsString("sg_delivery_type"); } 
    const std::string sgWrangler() const { return getAttrValueAsUserLogin("sg_wrangler"); } 
    const std::string sgWranglerNotes() const { return getAttrValueAsString("sg_wrangler_notes"); } 

    // Set an attribute's value
    void sgName(const std::string &val) { setAttrValue("title", toXmlrpcValue(val)); }
    void sgDataSize(const std::string &val) { setAttrValue("sg_delivery_data_size", toXmlrpcValue(val)); }
    void sgNotes(const std::string &val) { setAttrValue("sg_delivery_notes", toXmlrpcValue(val)); }
    void sgPath(const std::string &val) { setAttrValue("sg_delivery_path", toXmlrpcValue(val)); }
    void sgOriginalPath(const std::string &val) { setAttrValue("sg_delivery_staged_path", toXmlrpcValue(val)); }
    void sgStagedPath(const std::string &val) { sgOriginalPath(val); }
    void sgStatus(const std::string &val) { setAttrValue("sg_delivery_status", toXmlrpcValue(val)); }
    void sgType(const std::string &val) { setAttrValue("sg_delivery_type", toXmlrpcValue(val)); }
    void sgWrangler(const std::string &val) { setAttrValue("sg_wrangler", toXmlrpcValue(val)); }
    void sgWranglerNotes(const std::string &val) { setAttrValue("sg_wrangler_notes", toXmlrpcValue(val)); }

    Delivery &operator=(const Delivery &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __DELIVERY_H__
