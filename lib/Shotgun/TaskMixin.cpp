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

#include <iostream>

#include <Shotgun/TaskMixin.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Entity.h>
#include <Shotgun/HumanUser.h>
#include <Shotgun/Group.h>

namespace SG {

// *****************************************************************************
TaskPtrs TaskMixin::getTasks(const int limit)
{
    // Dynamic_cast can cast it to the other base class of this class' 
    // derived class.
    if (Entity *entity = dynamic_cast<Entity *>(this))
    {
        Dict projectAsLink = entity->sg()->findEntityAsLink<Project>(FilterBy("code", "is", entity->sgProjectCode()));

        return entity->sg()->findEntities<Task>(FilterBy("entity", "is", entity->asLink())
                                                    .And("project", "is", projectAsLink),
                                                limit);
    }
    else
    {
        throw SgEntityDynamicCastError("Entity");
    }
}

// *****************************************************************************
Task *TaskMixin::getTaskByName(const std::string &taskName)
{
    if (Entity *entity = dynamic_cast<Entity *>(this))
    {
        Dict projectAsLink = entity->sg()->findEntityAsLink<Project>(FilterBy("code", "is", entity->sgProjectCode()));

        return entity->sg()->findEntity<Task>(FilterBy("content", "is", taskName)
                                                  .And("entity", "is", entity->asLink())
                                                  .And("project", "is", projectAsLink));
    }
    else
    {
        throw SgEntityDynamicCastError("Entity");
    }
}

// *****************************************************************************
TaskPtrs TaskMixin::getMilestoneTasks(const int limit)
{
    if (Entity *entity = dynamic_cast<Entity *>(this))
    {
        Dict projectAsLink = entity->sg()->findEntityAsLink<Project>(FilterBy("code", "is", entity->sgProjectCode()));

        return entity->sg()->findEntities<Task>(FilterBy("entity", "is", entity->asLink())
                                                    .And("milestone", "is", true)
                                                    .And("project", "is", projectAsLink),
                                                limit);

    }
    else
    {
        throw SgEntityDynamicCastError("Entity");
    }
}

// *****************************************************************************
Task *TaskMixin::getNextIncompleteMilestoneTask()
{
    TaskPtrs milestones = getMilestoneTasks();

    int next = -1; 
    for (size_t i = 0; i < milestones.size(); i++)
    {
        // Is this milestone incomplete?
        if (milestones[i]->getAttrValueAsString("sg_status_list") != "cmpt")
        {
            // Yes, consider it
            if (next < 0 || milestones[next]->getAttrValueAsString("due_date") > milestones[i]->getAttrValueAsString("due_date"))
            {
                next = i;
            }
        }    
    }

    if (next > 0)
    {
        // Return the last one found that has the earliest endDate
        return milestones[next];
    }
    else
    {
        throw SgEntityNotFoundError("Task");
    }
}

// *****************************************************************************
Task *TaskMixin::addTask(const std::string &taskName,
                         const std::string &taskType,
                         const std::string &taskAssignee,
                         const std::string &taskStartDate,
                         const std::string &taskEndDate,
                         const std::string &taskStatus,
                         const std::string &taskColor,
                         const bool taskMilestone)
{
    // Check if the task already exists
    try
    {
        return getTaskByName(taskName);
    }
    catch (SgEntityNotFoundError)
    {
        if (Entity *entity = dynamic_cast<Entity *>(this))
        {
            // Prepare data for creating a Task entity
            Dict projectAsLink = entity->sg()->findEntityAsLink<Project>(FilterBy("code", "is", entity->sgProjectCode()));

            Dict attrsMap = Dict("project", projectAsLink)
                            .add("content", taskName)
                            //.add("sg_system_task_type", taskType) // This field seems no longer exist
                            .add("milestone", taskMilestone)
                            .add("entity", entity->asLink());

            // taskAssignee - could be a HumanUser or a Group
            if (taskAssignee != "")
            {
                try
                {
                    Dict userAsLink = entity->sg()->findEntityAsLink<HumanUser>(FilterBy("login", "is", taskAssignee));

                    attrsMap.add("task_assignees", List(userAsLink));
                }
                catch (SgEntityNotFoundError)
                {
                    try
                    {
                        Dict groupAsLink = entity->sg()->findEntityAsLink<Group>(FilterBy("code", "is", taskAssignee));

                        attrsMap.add("task_assignees", List(groupAsLink));
                    }
                    catch (SgEntityNotFoundError)
                    {
                    }
                }
            }

            // taskStartDate
            if (taskStartDate != "")
            {
                if (taskStartDate == "now")
                {
                    attrsMap.add("start_date", currDateStr());
                }
                else
                {
                    attrsMap.add("start_date", taskStartDate);
                }
            }

            // taskEndDate
            if (taskEndDate != "")
            {
                if (taskEndDate == "now")
                {
                    attrsMap.add("due_date", currDateStr());
                }
                else
                {
                    attrsMap.add("due_date", taskEndDate);
                }
            }

            // taskStatus
            if (taskStatus != "")
            {
                attrsMap.add("sg_status_list", taskStatus);
            }

            // taskColor
            if (taskColor != "")
            {
                attrsMap.add("color", taskColor);
            }

            return entity->sg()->createEntity<Task>(attrsMap);
        }
        else
        {
            throw SgEntityDynamicCastError("Entity");
        }
    }
}

// *****************************************************************************
Task *TaskMixin::updateTask(const std::string &taskName,
                            const std::string &taskAssignee,
                            const std::string &taskStartDate,
                            const std::string &taskEndDate,
                            const std::string &taskStatus,
                            const std::string &taskColor,
                            const bool taskMilestone)
{
    Task *task = getTaskByName(taskName);

    Fields fieldData;

    // taskAssignee
    if (taskAssignee != "")
    {
        try
        {
            Dict userAsLink = task->sg()->findEntityAsLink<HumanUser>(FilterBy("login", "is", taskAssignee));

            fieldData.append("task_assignees", List(userAsLink));
        }
        catch (SgEntityNotFoundError)
        {
            try
            {
                Dict groupAsLink = task->sg()->findEntityAsLink<Group>(FilterBy("code", "is", taskAssignee));
                fieldData.append("task_assignees", List(groupAsLink));
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
            fieldData.append("start_date", currDateStr());
        }
        else
        {
            fieldData.append("start_date", taskStartDate);
        }
    }

    // taskEndDate
    if (taskEndDate != "")
    {
        if (taskEndDate == "now")
        {
            fieldData.append("due_date", currDateStr());
        }
        else
        {
            fieldData.append("due_date", taskEndDate);
        }
    }

    // taskStatus
    if (taskStatus != "")
    {
        fieldData.append("sg_status_list", taskStatus);
    }

    // taskColor
    if (taskColor != "")
    {
        fieldData.append("color", taskColor);
    }

    // taskMilestone
    fieldData.append("milestone", taskMilestone);

    // update the task's attributes
    task->setAttrValue(fieldData);

    return task;
}

// *****************************************************************************
bool TaskMixin::removeTask(const std::string &taskName)
{
    try
    {
        Task *task = getTaskByName(taskName);

        task->sg()->deleteEntity<Task>(task->sgId());

        delete task;
        return true;
    }
    catch (SgEntityNotFoundError)
    {
        return false;
    }
}

} // End namespace SG
