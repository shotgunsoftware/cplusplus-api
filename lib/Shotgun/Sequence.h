//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Sequence : public Entity
{
    friend class Shotgun;
    friend class Shot;
    friend class DeliveryItem;
    friend class Reference;
    friend class Entity;
 
protected:
    Sequence(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Sequence create(Shotgun *sg, 
                           const std::string &showCode,
                           const std::string &sequenceName);
    static Sequences find(Shotgun *sg, SgMap &findMap);
    
public:
    Sequence();
    Sequence(const Sequence &ref);
    virtual ~Sequence();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); } 

    // Set an attribute's value
    void sgName(const std::string &name) { setAttrValue("code", toXmlrpcValue(name)); }

    Sequence &operator=(const Sequence &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __SEQUENCE_H__
