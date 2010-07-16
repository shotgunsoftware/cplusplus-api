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
#include <Shotgun/Show.h>

namespace Shotgun {

// *****************************************************************************
Task::Task(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Task";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Task::Task()
    : Entity(NULL)
{
    m_type = "Task";
    m_attrs = NULL;
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
Task Task::create(Shotgun *sg, 
                  const std::string &showCode,
                  const std::string &taskName,
                  const std::string &taskType,
                  const int taskViewOrder,
                  const std::string &taskAssignee,
                  const std::string &taskStartDate,
                  const std::string &taskEndDate,
                  const std::string &taskStatus,
                  const std::string &taskColor,
                  const bool taskMilestone,
                  const SgMap &taskEntityLink)
{
    Show show = sg->findShowByCode(showCode);

    SgMap attrsMap;
    attrsMap["project"] = toXmlrpcValue(show.asLink());
    attrsMap["content"] = toXmlrpcValue(taskName);
    attrsMap["sg_system_task_type"] = toXmlrpcValue(taskType);
    attrsMap["milestone"] = toXmlrpcValue(taskMilestone);

    // taskEntityLink
    if (taskEntityLink.size() > 0)
    {
        attrsMap["entity"] = toXmlrpcValue(taskEntityLink);
    }

    // taskViewOrder
    if (taskViewOrder != TIPSHOTGUN_INVALID_ORDER_NUM)
    {
        attrsMap["sg_view_order"] = toXmlrpcValue(taskViewOrder);
    }

    // taskAssignee - could be a User or a Group
    if (taskAssignee != "")
    {
        try
        {
            User user = sg->findUserByLogin(taskAssignee);

            SgArray assignees;
            assignees.push_back(toXmlrpcValue(user.asLink()));
            attrsMap["task_assignees"] = toXmlrpcValue(assignees);
        }
        catch (SgEntityNotFoundError)
        {
            try
            {
                Group group = sg->findGroupByName(taskAssignee);

                SgArray assignees;
                assignees.push_back(toXmlrpcValue(group.asLink()));
                attrsMap["task_assignees"] = toXmlrpcValue(assignees);
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

    // Call the base class function to create an entity
    return Task(sg, createEntity(sg, "Task", attrsMap));
}

// *****************************************************************************
Tasks Task::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create a Task for each of them
    Tasks tasks;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            tasks.push_back(Task(sg, result[i]));
        }
    }

    return tasks;
}

// *****************************************************************************
const EntityPtrs Task::sgAssignees() const
{
    // Assignees is a mixed list of Users & Groups
    SgArray entities = Entity::getAttrValueAsMultiEntityAttrMap("task_assignees");
    EntityPtrs assignees;

    for (size_t i = 0; i < entities.size(); i++)
    {
        SgMap entityAsMap = SgMap(xmlrpc_c::value_struct(entities[i]));

        if (Entity::getAttrValueAsString("type", entityAsMap) == "HumanUser")
        {
            assignees.push_back(new User(m_sg, entities[i]));
        }
        else if (getAttrValueAsString("type", entityAsMap) == "Group")
        {
            assignees.push_back(new Group(m_sg, entities[i]));
        }
    }

    return assignees;
}

// *****************************************************************************
void Task::sgAssignees(const Strings &val)
{
    SgArray assigneeLinkArray;

    for (size_t i = 0; i < val.size(); i++)
    {
        try
        {
            User user = m_sg->findUserByLogin(val[i]);
            assigneeLinkArray.push_back(toXmlrpcValue(user.asLink()));
        }
        catch (SgEntityNotFoundError)
        {
            try
            {
                Group group = m_sg->findGroupByName(val[i]);
                assigneeLinkArray.push_back(toXmlrpcValue(group.asLink()));
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
