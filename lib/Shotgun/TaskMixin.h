//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#ifndef __TASK_MIXIN_H__
#define __TASK_MIXIN_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Task.h>

namespace Shotgun {

// *****************************************************************************
class TaskMixin
{
protected:
    TaskMixin() {}

public:
    virtual ~TaskMixin() {};

    Tasks getTasks(const int limit = 0);
    Task getTaskByName(const std::string &taskName);
    Tasks getMilestoneTasks(const int limit = 0);
    Task getNextIncompleteMilestoneTask();

    Task addTask(const std::string &taskName,
                 const std::string &taskType,
                 const int taskViewOrder = TIPSHOTGUN_INVALID_ORDER_NUM,
                 const std::string &taskAssignee = "",
                 const std::string &taskStartDate = "",
                 const std::string &taskEndDate = "",
                 const std::string &taskStatus = "",
                 const std::string &taskColor = "",
                 const bool taskMilestone = false);

    Task updateTask(const std::string &taskName,
                    const int taskViewOrder = TIPSHOTGUN_INVALID_ORDER_NUM,
                    const std::string &taskAssignee = "",
                    const std::string &taskStartDate = "",
                    const std::string &taskEndDate = "",
                    const std::string &taskStatus = "",
                    const std::string &taskColor = "",
                    const bool taskMilestone = false);

    bool removeTask(const std::string &taskName);
};

} // End namespace Shotgun

#endif    // End #ifdef __TASK_MIXIN_H__
