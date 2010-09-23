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

namespace Shotgun {

// *****************************************************************************
TaskPtrs TaskMixin::getTasks(const int limit)
{
    // Dynamic_cast can cast it to the other base class of this class' 
    // derived class.
    if (Entity *entity = dynamic_cast<Entity *>(this))
    {
        return entity->sg()->findTasksByLinkEntity(entity->sgProjectCode(), 
                                                   entity->asLink(),
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
        return entity->sg()->findEntity<Task>(FilterBy("content", "is", taskName)
                                                  .And("entity", "is", entity->asLink())
                                                  .And("project", "is", entity->sg()->getProjectLink(entity->sgProjectCode())));
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
        return entity->sg()->findEntities<Task>(FilterBy("entity", "is", entity->asLink())
                                                    .And("milestone", "is", true)
                                                    .And("project", "is", entity->sg()->getProjectLink(entity->sgProjectCode())),
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
        if (milestones[i]->sgStatus() != "cmpt")
        {
            // Yes, consider it
            if (next < 0 or 
                milestones[next]->sgEndDate() > milestones[i]->sgEndDate())
            {
                next = i;
            }
        }    
    }

    if (next > 0)
    {
        // Return the last one found that has the ealiest endDate
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
        // TODO: check "task_mixin.py"
        return getTaskByName(taskName);
    }
    catch (SgEntityNotFoundError)
    {
        if (Entity *entity = dynamic_cast<Entity *>(this))
        {
            return entity->sg()->createTask(entity->sgProjectCode(),
                                            taskName,
                                            taskType,
                                            taskAssignee,
                                            taskStartDate,
                                            taskEndDate,
                                            taskStatus,
                                            taskColor,
                                            taskMilestone,
                                            entity->asLink());
        }
        else
        {
            throw SgEntityDynamicCastError("Entity");
        }
    }
}

// *****************************************************************************
Task TaskMixin::updateTask(const std::string &taskName,
                           const std::string &taskAssignee,
                           const std::string &taskStartDate,
                           const std::string &taskEndDate,
                           const std::string &taskStatus,
                           const std::string &taskColor,
                           const bool taskMilestone)
{
    Task *task = getTaskByName(taskName);

    SgMap updateMap;

    // taskAssignee
    if (taskAssignee != "")
    {
        try
        {
            HumanUser *user = task->sg()->findHumanUserByLogin(taskAssignee);

            SgArray assignees;
            assignees.push_back(toXmlrpcValue(user->asLink()));
            updateMap["task_assignees"] = toXmlrpcValue(assignees);

            delete user;
        }
        catch (SgEntityNotFoundError)
        {
            try
            {
                Group *group = task->sg()->findGroupByName(taskAssignee);

                SgArray assignees;
                assignees.push_back(toXmlrpcValue(group->asLink()));
                updateMap["task_assignees"] = toXmlrpcValue(assignees);

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
            updateMap["start_date"] = toXmlrpcValue(currDateStr());
        }
        else
        {
            updateMap["start_date"] = toXmlrpcValue(taskStartDate);
        }
    }

    // taskEndDate
    if (taskEndDate != "")
    {
        if (taskEndDate == "now")
        {
            updateMap["due_date"] = toXmlrpcValue(currDateStr());
        }
        else
        {
            updateMap["due_date"] = toXmlrpcValue(taskEndDate);
        }
    }

    // taskStatus
    if (taskStatus != "")
    {
        updateMap["sg_status_list"] = toXmlrpcValue(taskStatus);
    }

    // taskColor
    if (taskColor != "")
    {
        updateMap["color"] = toXmlrpcValue(taskColor);
    }

    // taskMilestone
    updateMap["milestone"] = toXmlrpcValue(taskMilestone);

    // update the task's attributes
    task->setAttrValue(updateMap);

#warning This needs to be fixed as soon as the return type is changed to pointer
#if 0
    return task;
#else
    Task out = *task;
    delete task;
    return out;
#endif
}

// *****************************************************************************
bool TaskMixin::removeTask(const std::string &taskName)
{
    try
    {
        Task *task = getTaskByName(taskName);

        task->sg()->deleteTaskById(task->sgId());

        delete task;
        return true;
    }
    catch (SgEntityNotFoundError)
    {
        return false;
    }
}

} // End namespace Shotgun
