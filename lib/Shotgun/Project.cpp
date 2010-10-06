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
#include <vector>

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Project.h>

namespace Shotgun {

// *****************************************************************************
Project::Project(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Project";

    if (attrs.type() != xmlrpc_c::value::TYPE_NIL)
    {
        m_attrs = new xmlrpc_c::value(attrs);
    }
}

// *****************************************************************************
Project::Project(const Project &ref)
    : Entity(ref.m_sg)
{
    m_type = "Project";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Project::~Project()
{
    // Nothing
}

// *****************************************************************************
List Project::populateReturnFields()
{
    return List("id")
           .append("project")
           .append("created_at")
           .append("updated_at")
           .append("name")
           .append("code")
           .append("sg_status")
           .append("sg_archive_watcher")
           .append("sg_pub_stills_watcher")
           .append("sg_generate_shot_aliases")
           .append("sg_send_dailies_notices")
           .append("sg_polish_shot_notifications")
           .append("sg_report_storage_information")
           .append("sg_default_start_frame")
           .append("sg_ms_project_schedule");
}

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::Project &project)
{
    return toStdString(project.attrs());
}

// *****************************************************************************
std::string toStdString(const Shotgun::Projects &projects)
{
    // The std::string of xmlrpc_c::value type has been formatted very well.
    // So convert it to xmlrpc_c::value first.
    Shotgun::List list;
    for (size_t i = 0; i < projects.size(); i++)
    {
        list.append(projects[i].attrs());
    }
    
    return toStdString(list);
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Project &project)
{
    output << toStdString(project);
    return output;
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Projects &projects)
{
    output << toStdString(projects);
    return output;
}
