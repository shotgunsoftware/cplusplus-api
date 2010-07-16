//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#ifndef __REFERENCE_H__
#define __REFERENCE_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Asset.h>
#include <Shotgun/Sequence.h>
#include <Shotgun/Shot.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Reference : public Entity
{
    friend class Shotgun;
    friend class Entity;
 
protected:
    Reference(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Reference create(Shotgun *sg, 
                            const std::string &showCode,
                            const std::string &referencePath,
                            const std::string &referencePurpose = "",
                            const Strings &linkAssets = Strings(),
                            const Strings &linkSequences = Strings(),
                            const Strings &linkShots = Strings(),
                            const Strings &tags = Strings());
    static References find(Shotgun *sg, SgMap &findMap);
    
public:
    Reference();
    Reference(const Reference &ref);
    virtual ~Reference();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); } 
    const std::string sgChecksum() const { return getAttrValueAsString("sg_checksum"); } 
    const bool sgHero() const { return getAttrValueAsBool("sg_hero"); } 
    const bool sgRemove() const { return getAttrValueAsBool("sg_remove"); } 
    const Asset sgAsset() const { return Asset(m_sg, getAttrValueAsEntityAttrMap("sg_asset")); } 
    const Sequence sgSequence() const { return Sequence(m_sg, getAttrValueAsEntityAttrMap("sg_sequence")); } 
    const Shot sgShot() const { return Shot(m_sg, getAttrValueAsEntityAttrMap("sg_shot")); } 
    const std::string sgPurpose() const { return getAttrValueAsString("sg_purpose"); } 
    const Strings sgTags() const { return getAttrValueAsTags("tag_list"); } 

    // Set an attribute's value
    void sgChecksum(const std::string &val) { setAttrValue("sg_checksum", toXmlrpcValue(val)); }
    void sgHero(const bool val) { setAttrValue("sg_hero", toXmlrpcValue(val)); }
    void sgRemove(const bool val) { setAttrValue("sg_remove", toXmlrpcValue(val)); }
    void sgAsset(const Asset &val) { setAttrValue("sg_asset", toXmlrpcValue(val.asLink())); }
    void sgAsset(const SgMap &val);
    void sgSequence(const Sequence &val) { setAttrValue("sg_sequence", toXmlrpcValue(val.asLink())); }
    void sgSequence(const SgMap &val);
    void sgShot(const Shot &val) { setAttrValue("sg_shot", toXmlrpcValue(val.asLink())); }
    void sgShot(const SgMap &val);
    void sgPurpose(const std::string &val) { setAttrValue("sg_purpose", toXmlrpcValue(val)); }
    void sgTags(const Strings &val) { setAttrValue("tag_list", toXmlrpcValue(val)); }

    Reference &operator=(const Reference &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __REFERENCE_H__
