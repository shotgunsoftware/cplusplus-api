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

#ifndef __TASK_MIXIN_H__
#define __TASK_MIXIN_H__

#include <string>

#include <Shotgun/Task.h>

namespace Shotgun {

// *****************************************************************************
/// \class TaskMixin
/// A TaskMixin class is used as "add-on"s to any entity class that shares a
/// common set of Task-related functions. The entity class needs to derive
/// from the TaskMixin class.
class TaskMixin
{
public:
    /// A destructor that does nothing.
    virtual ~TaskMixin() {};

    /// Returns an array of Task entities which link to the current entity.
    TaskPtrs getTasks(const int limit = 0);

    /// Returns a Task entity by its name which links to the current entity.
    Task *getTaskByName(const std::string &taskName);

    /// Returns milestone Task entities which link to the current entity.
    TaskPtrs getMilestoneTasks(const int limit = 0);

    /// Returns an incomplete milestone Task entity that has the earliest due date.
    Task *getNextIncompleteMilestoneTask();

    /// Creates a new Task entity with data from the current entity.
    Task *addTask(const std::string &taskName,
                  const std::string &taskType,
                  const std::string &taskAssignee = "",
                  const std::string &taskStartDate = "",
                  const std::string &taskEndDate = "",
                  const std::string &taskStatus = "",
                  const std::string &taskColor = "",
                  const bool taskMilestone = false);

    /// Finds an existing Task entity by its name and updates its data with
    /// the passed arguments.
    Task *updateTask(const std::string &taskName,
                     const std::string &taskAssignee = "",
                     const std::string &taskStartDate = "",
                     const std::string &taskEndDate = "",
                     const std::string &taskStatus = "",
                     const std::string &taskColor = "",
                     const bool taskMilestone = false);

    /// Removes a Task entity by its name.
    bool removeTask(const std::string &taskName);

protected:
    /// A constructor that does nothing.
    TaskMixin() {}
};

} // End namespace Shotgun

#endif    // End #ifdef __TASK_MIXIN_H__
