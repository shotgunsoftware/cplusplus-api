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

#ifndef __PUBLISH_EVENT_H__
#define __PUBLISH_EVENT_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class PublishEvent : public Entity
{
    friend class Shotgun;
    friend class Entity;
 
protected:
    PublishEvent(Shotgun *sg, const xmlrpc_c::value &attrs);

    static PublishEvent create(Shotgun *sg, 
                               const std::string &showCode,
                               const std::string &publishEventName,
                               const std::string &publishEventSource,
                               const std::string &publishEventType = "",
                               const int publishEventVersion = TIPSHOTGUN_INVALID_VERSION_NUM,
                               const std::string &publishEventResolution = "");
    static PublishEvents find(Shotgun *sg, SgMap &findMap);
    
public:
    PublishEvent();
    PublishEvent(const PublishEvent &ref);
    virtual ~PublishEvent();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); }
    const std::string sgFile() const { return getAttrValueAsString("sg_file"); } 
    //const std::string sgFormat() const { return getAttrValueAsString("sg_format"); } 
    const std::string sgPreviewHDQT() const { return getAttrValueAsQtPath("sg_preview_hd_qt"); } 
    const std::string sgPreviewQT() const { return getAttrValueAsQtPath("sg_preview_qt"); } 
    const int sgRev() const { return getAttrValueAsInt("sg_rev"); } 
    const std::string sgResolution() const { return getAttrValueAsString("sg_resolution"); } 
    const std::string sgType() const { return getAttrValueAsString("sg_type"); } 

    // Set an attribute's value
    void sgFile(const std::string &val) { setAttrValue("sg_file", toXmlrpcValue(val)); }
    //void sgFormat(const std::string &val) { setAttrValue("sg_format", toXmlrpcValue(val)); }
    void sgPreviewHDQT(const std::string &val);
    void sgPreviewQT(const std::string &val);
    void sgRev(const int val) { setAttrValue("sg_rev", toXmlrpcValue(val)); }
    void sgResolution(const std::string &val) { setAttrValue("sg_resolution", toXmlrpcValue(val)); }
    void sgType(const std::string &val) { setAttrValue("sg_type", toXmlrpcValue(val)); }

    PublishEvent &operator=(const PublishEvent &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __PUBLISH_EVENT_H__
