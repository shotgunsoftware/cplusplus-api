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

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Task.h>
#include <Shotgun/Project.h>

namespace Shotgun {

// *****************************************************************************
Task::Task(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Task";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Task::Task(const Task &ref)
    : Entity(ref.m_sg)
{
    m_type = "Task";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Task::~Task()
{
    // Nothing
}

// *****************************************************************************
Task *Task::create(Shotgun *sg, 
                   const std::string &projectCode,
                   const std::string &taskName,
                   const std::string &taskType,
                   const std::string &taskAssignee,
                   const std::string &taskStartDate,
                   const std::string &taskEndDate,
                   const std::string &taskStatus,
                   const std::string &taskColor,
                   const bool taskMilestone,
                   const SgMap &taskEntityLink)
{
    SgMap attrsMap;
    attrsMap["project"] = toXmlrpcValue(sg->getProjectLink(projectCode));
    attrsMap["content"] = toXmlrpcValue(taskName);
    attrsMap["sg_system_task_type"] = toXmlrpcValue(taskType); // This field seems no longer exist
    attrsMap["milestone"] = toXmlrpcValue(taskMilestone);

    // taskEntityLink
    if (taskEntityLink.size() > 0)
    {
        attrsMap["entity"] = toXmlrpcValue(taskEntityLink);
    }

    // taskAssignee - could be a HumanUser or a Group
    if (taskAssignee != "")
    {
        try
        {
            HumanUser *user = sg->findHumanUserByLogin(taskAssignee);

            SgArray assignees;
            assignees.push_back(toXmlrpcValue(user->asLink()));
            attrsMap["task_assignees"] = toXmlrpcValue(assignees);

            delete user;
        }
        catch (SgEntityNotFoundError)
        {
            try
            {
                Group *group = sg->findGroupByName(taskAssignee);

                SgArray assignees;
                assignees.push_back(toXmlrpcValue(group->asLink()));
                attrsMap["task_assignees"] = toXmlrpcValue(assignees);

                delete group;
            }
            catch (SgEntityNotFoundError)
            {
                // Do nothing
            }
        }
    }

    // taskStartDate
    if (taskStartDate != "")
    {
        if (taskStartDate == "now")
        {
            attrsMap["start_date"] = toXmlrpcValue(currDateStr());
        }
        else
        {
            attrsMap["start_date"] = toXmlrpcValue(taskStartDate);
        }
    }

    // taskEndDate
    if (taskEndDate != "")
    {
        if (taskEndDate == "now")
        {
            attrsMap["due_date"] = toXmlrpcValue(currDateStr());
        }
        else
        {
            attrsMap["due_date"] = toXmlrpcValue(taskEndDate);
        }
    }

    // taskStatus
    if (taskStatus != "")
    {
        attrsMap["sg_status_list"] = toXmlrpcValue(taskStatus);
    }

    // taskColor
    if (taskColor != "")
    {
        attrsMap["color"] = toXmlrpcValue(taskColor);
    }

    return sg->createEntity<Task>(Dict(attrsMap));
}

// *****************************************************************************
SgArray Task::populateReturnFields(const SgArray &extraReturnFields)
{
    SgArray returnFields = extraReturnFields;

    returnFields.push_back(toXmlrpcValue("id"));
    returnFields.push_back(toXmlrpcValue("project"));
    returnFields.push_back(toXmlrpcValue("created_at"));
    returnFields.push_back(toXmlrpcValue("updated_at"));

    returnFields.push_back(toXmlrpcValue("content"));
    returnFields.push_back(toXmlrpcValue("task_assignees"));
    returnFields.push_back(toXmlrpcValue("color"));
    returnFields.push_back(toXmlrpcValue("due_date"));
    returnFields.push_back(toXmlrpcValue("duration"));
    returnFields.push_back(toXmlrpcValue("entity"));
    returnFields.push_back(toXmlrpcValue("milestone"));
    returnFields.push_back(toXmlrpcValue("start_date"));
    returnFields.push_back(toXmlrpcValue("sg_status_list"));
//    returnFields.push_back(toXmlrpcValue("sg_system_task_type")); // Seems no longer exist
    returnFields.push_back(toXmlrpcValue("sg_view_order"));

    return returnFields;
}

// *****************************************************************************
const EntityPtrs Task::sgAssignees() const
{
    // Assignees is a mixed list of HumanUsers & Groups
    return Entity::getAttrValueAsMultiEntityPtr("task_assignees");
}

// *****************************************************************************
void Task::sgAssignees(const Strings &val)
{
    SgArray assigneeLinkArray;

    for (size_t i = 0; i < val.size(); i++)
    {
        try
        {
            HumanUser *user = m_sg->findHumanUserByLogin(val[i]);
            assigneeLinkArray.push_back(toXmlrpcValue(user->asLink()));
   
            delete user;
        }
        catch (SgEntityNotFoundError)
        {
            try
            {
                Group *group = m_sg->findGroupByName(val[i]);
                assigneeLinkArray.push_back(toXmlrpcValue(group->asLink()));

                delete group;
            }
            catch (SgEntityNotFoundError)
            {
                throw SgAttrSetValueError("task_assignees",
                                          "\"" + val[i] + "\" is not a valid User or Group");
            }
        }
    }

    setAttrValue("task_assignees", toXmlrpcValue(assigneeLinkArray));
}

} // End namespace Shotgun
