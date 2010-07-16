//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#ifndef __TASK_H__
#define __TASK_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Task : public Entity
{
    friend class Shotgun;
    friend class Entity;
 
protected:
    Task(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Task create(Shotgun *sg, 
                       const std::string &showCode,
                       const std::string &taskName,
                       const std::string &taskType,
                       const int taskViewOrder = TIPSHOTGUN_INVALID_ORDER_NUM,
                       const std::string &taskAssignee = "",
                       const std::string &taskStartDate = "",
                       const std::string &taskEndDate = "",
                       const std::string &taskStatus = "",
                       const std::string &taskColor = "",
                       const bool taskMilestone = false,
                       const SgMap &taskEntityLink = SgMap());
    static Tasks find(Shotgun *sg, SgMap &findMap);
    
public:
    Task();
    Task(const Task &ref);
    virtual ~Task();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("content"); } 
    const std::string sgColor() const { return getAttrValueAsString("color"); } 
    const std::string sgEndDate() const { return getAttrValueAsString("due_date"); } 
    const int sgDuration() const { return getAttrValueAsInt("duration"); } 
    const bool sgMilestone() const { return getAttrValueAsBool("milestone"); } 
    const std::string sgStartDate() const { return getAttrValueAsString("start_date"); } 
    const std::string sgStatus() const { return getAttrValueAsString("sg_status_list"); } 
    const std::string sgType() const { return getAttrValueAsString("sg_system_task_type"); } 
    const int sgViewOrder() const { return getAttrValueAsInt("sg_view_order"); } 
    const std::string sgDueDate() const { return sgEndDate(); } 
    
    // ------------------------------------------------------------------------
    // IMPORTANT: 
    // (1) C++ - user must be responsible for deleting the pointers in C++ app.
    // (2) Python - the ownership has been transferred to Python by using the 
    //     /Factory/ annotation.
    // ------------------------------------------------------------------------
    Entity *sgLink() { return getAttrValueAsEntityPtr("entity"); }
    // The return value is a mixed list of Users & Groups
    const EntityPtrs sgAssignees() const; 
    const std::string sgLinkEntityType() const { return linkEntityType("entity"); }

    // Set an attribute's value
    void sgStatus(const std::string &val) { setAttrValue("sg_status_list", toXmlrpcValue(val)); }
    void sgViewOrder(const int val) { setAttrValue("sg_view_order", toXmlrpcValue(val)); }
    void sgAssignees(const Strings &val);

    Task &operator=(const Task &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __TASK_H__
