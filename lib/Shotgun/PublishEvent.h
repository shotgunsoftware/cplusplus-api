//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

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
