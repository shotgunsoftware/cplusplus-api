//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#ifndef __GROUP_H__
#define __GROUP_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Group : public Entity
{
    friend class Shotgun;
    friend class Entity;
    friend class Task;
 
protected:
    Group(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Group create(Shotgun *sg, const std::string &groupName);
    static Groups find(Shotgun *sg, SgMap &findMap);
    
public:
    Group();
    Group(const Group &ref);
    virtual ~Group();

    const std::string sgName() const { return getAttrValueAsString("code"); } 
    const std::string sgLogin() const { return getAttrValueAsString("code"); } 

    Group &operator=(const Group &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __GROUP_H__
