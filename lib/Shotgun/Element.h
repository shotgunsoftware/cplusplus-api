//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

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
 
protected:
    Element(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Element create(Shotgun *sg, 
                          const std::string &showCode,
                          const std::string &elementName,
                          const std::string &elementType);
    static Elements find(Shotgun *sg, SgMap &findMap);
    
public:
    Element();
    Element(const Element &ref);
    virtual ~Element();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); } 
    const Assets sgAssets() const; // NOTE: put the implementation in *.cpp 
    const Shots sgShots() const; // NOTE: put the implementation in *.cpp 
    const Strings sgTags() const { return getAttrValueAsTags("tag_list"); } 
    const std::string sgType() const { return getAttrValueAsString("sg_element_type"); }

    // Set an attribute's value
    void sgAssets(const Assets &val); // An array of Asset entities
    void sgAssets(const SgArray &val); // An array of entity links
    void sgShots(const Shots &val); // An array of Shot entities
    void sgShots(const SgArray &val); // An array of entity links
    void sgTags(const Strings &val) { setAttrValue("tag_list", toXmlrpcValue(val)); }
    void sgType(const std::string &val) { setAttrValue("sg_element_type", toXmlrpcValue(val)); }

    Element &operator=(const Element &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __ELEMENT_H__
