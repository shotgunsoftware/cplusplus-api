//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#ifndef __USER_H__
#define __USER_H__

#include <Shotgun/Entity.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class User : public Entity
{
    friend class Shotgun;
    friend class Entity;
    friend class Task;
 
protected:
    User(Shotgun *sg, const xmlrpc_c::value &attrs);

    static User create(Shotgun *sg,
                       const std::string &userName,
                       const std::string &userLogin,
                       const std::string &userEmail,
                       const std::string &userDept);

    static Users find(Shotgun *sg, SgMap &findMap);
    
public:
    User();
    User(const User &ref);
    virtual ~User();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("name"); }
    const bool sgCode() const { return getAttrValueAsBool("admin"); }
    const std::string sgDepartment() const { return getAttrValueAsString("sg_department"); }
    const std::string sgEmail() const { return getAttrValueAsString("email"); }
    const std::string sgLogin() const { return getAttrValueAsString("login"); }
    const std::string sgRole() const { return getAttrValueAsString("sg_role"); }
    const SgMap sgPermissionGroup() const { return getAttrValueAsMap("permission_rule_set"); }

    // Set an attribute's value
    void sgName(const std::string &val) { setAttrValue("name", toXmlrpcValue(val)); }
    void sgDepartment(const std::string &val) { setAttrValue("sg_department", toXmlrpcValue(val)); }
    void sgEmail(const std::string &val) { setAttrValue("email", toXmlrpcValue(val)); }
    void sgLogin(const std::string &val) { setAttrValue("login", toXmlrpcValue(val)); }

    User &operator=(const User &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __USER_H__
