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
    
public:
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
    // The "sg_system_task_type" field seems no longer exist
    //const std::string sgType() const { return getAttrValueAsString("sg_system_task_type"); } 
    
    // ------------------------------------------------------------------------
    // IMPORTANT: 
    // (1) C++ - user must be responsible for deleting the pointers in C++ app.
    // (2) Python - the ownership has been transferred to Python by using the 
    //     /Factory/ annotation.
    // ------------------------------------------------------------------------
    const Entity *sgLink() const { return getAttrValueAsEntityPtr("entity"); }
    // The return value is a mixed list of HumanUsers & Groups
    const EntityPtrs sgAssignees() const; 
    const std::string sgLinkEntityType() const { return linkEntityType("entity"); }

    // Set an attribute's value
    void sgStatus(const std::string &val) { setAttrValue("sg_status_list", toXmlrpcValue(val)); }
    void sgAssignees(const Strings &val);

    static std::string type() { return std::string("Task"); }

    Task &operator=(const Task &that)
    {
        Entity::operator=(that);
        return *this;
    }

protected:
    Task(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Entity *factory(Shotgun *sg, const xmlrpc_c::value &attrs) { return new Task(sg, attrs); }
    static Task create(Shotgun *sg, 
                       const std::string &projectCode,
                       const std::string &taskName,
                       const std::string &taskType,
                       const std::string &taskAssignee = "",
                       const std::string &taskStartDate = "",
                       const std::string &taskEndDate = "",
                       const std::string &taskStatus = "",
                       const std::string &taskColor = "",
                       const bool taskMilestone = false,
                       const SgMap &taskEntityLink = SgMap());

    static SgArray populateReturnFields(const SgArray &extraReturnFields = SgArray());
};

} // End namespace Shotgun

#endif    // End #ifdef __TASK_H__
