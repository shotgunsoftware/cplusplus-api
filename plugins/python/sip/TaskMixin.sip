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

namespace Shotgun {

// *****************************************************************************
class TaskMixin
{
%TypeHeaderCode
    #include <Shotgun/TaskMixin.h>
%End

protected:
    TaskMixin();

public:
    virtual ~TaskMixin();

    Shotgun::Tasks getTasks(const int limit = 0) throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    Shotgun::Task getTaskByName(const std::string &taskName) throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    Shotgun::Tasks getMilestoneTasks(const int limit = 0) throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    Shotgun::Task getNextIncompleteMilestoneTask() throw(Shotgun::SgAttrError, Shotgun::SgEntityError);

    Shotgun::Task addTask(const std::string &taskName,
                             const std::string &taskType,
                             const int taskViewOrder = TIPSHOTGUN_INVALID_ORDER_NUM,
                             const std::string &taskAssignee = "",
                             const std::string &taskStartDate = "",
                             const std::string &taskDueDate = "",
                             const std::string &taskStatus = "",
                             const std::string &taskColor = "",
                             const bool taskMilestone = false) throw(Shotgun::SgAttrError, Shotgun::SgEntityError);

    Shotgun::Task updateTask(const std::string &taskName,
                                const int taskViewOrder = TIPSHOTGUN_INVALID_ORDER_NUM,
                                const std::string &taskAssignee = "",
                                const std::string &taskStartDate = "",
                                const std::string &taskEndDate = "",
                                const std::string &taskStatus = "",
                                const std::string &taskColor = "",
                                const bool taskMilestone = false) throw(Shotgun::SgAttrError, Shotgun::SgEntityError);

    bool removeTask(const std::string &taskName) throw(Shotgun::SgEntityError);
};

}; // End namespace Shotgun - must have a semi-colon

