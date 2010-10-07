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
List Task::populateReturnFields()
{
    return List("id")
           .append("project")
           .append("created_at")
           .append("updated_at")
           .append("content")
           .append("task_assignees")
           .append("color")
           .append("due_date")
           .append("duration")
           .append("entity")
           .append("milestone")
           .append("start_date")
           .append("sg_status_list")
           //.append("sg_system_task_type") // Seems no longer exist
           .append("sg_view_order");
}

// *****************************************************************************
const EntityPtrs Task::sgAssignees() const
{
    // Assignees is a mixed list of HumanUsers & Groups
    return Entity::getAttrValueAsMultiEntityPtr("task_assignees");
}

// *****************************************************************************
void Task::sgStatus(const std::string &val)
{
    setAttrValue(Fields("sg_status_list", val));
}

// *****************************************************************************
void Task::sgAssignees(const Strings &val)
{
    List assigneeLinkArray;

    for (size_t i = 0; i < val.size(); i++)
    {
        try
        {
            HumanUser *user = m_sg->findEntity<HumanUser>(FilterBy("login", "is", val[i]));
            assigneeLinkArray.append(user->asLink());
   
            delete user;
        }
        catch (SgEntityNotFoundError)
        {
            try
            {
                Group *group = m_sg->findEntity<Group>(FilterBy("code", "is", val[i]));
                assigneeLinkArray.append(group->asLink());

                delete group;
            }
            catch (SgEntityNotFoundError)
            {
                throw SgAttrSetValueError("task_assignees",
                                          "\"" + val[i] + "\" is not a valid User or Group");
            }
        }
    }

    setAttrValue(Fields("task_assignees", assigneeLinkArray));
}

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::Task &task)
{
    return toStdString(task.attrs());
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Task &task)
{
    output << toStdString(task);
    return output;
}
