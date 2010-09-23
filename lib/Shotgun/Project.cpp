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
Project *Project::create(Shotgun *sg, 
                         const std::string &projectName,
                         const std::string &projectCode)
{
    // Check if the project already exists
    try
    {
        Project *project = sg->findProjectByCode(projectCode);
        delete project;

        std::string err = "Project \"" + projectCode + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        SgMap attrsMap;

        attrsMap["code"] = toXmlrpcValue(projectCode);
        attrsMap["name"] = toXmlrpcValue(projectName);

        return sg->createEntity<Project>(Dict(attrsMap));
    }
}

// *****************************************************************************
SgArray Project::populateReturnFields(const SgArray &extraReturnFields)
{
    SgArray returnFields = extraReturnFields;

    returnFields.push_back(toXmlrpcValue("id"));
    returnFields.push_back(toXmlrpcValue("project"));
    returnFields.push_back(toXmlrpcValue("created_at"));
    returnFields.push_back(toXmlrpcValue("updated_at"));

    returnFields.push_back(toXmlrpcValue("name"));
    returnFields.push_back(toXmlrpcValue("code"));
    returnFields.push_back(toXmlrpcValue("sg_status"));
    returnFields.push_back(toXmlrpcValue("sg_archive_watcher"));
    returnFields.push_back(toXmlrpcValue("sg_pub_stills_watcher"));
    returnFields.push_back(toXmlrpcValue("sg_generate_shot_aliases"));
    returnFields.push_back(toXmlrpcValue("sg_send_dailies_notices"));
    returnFields.push_back(toXmlrpcValue("sg_polish_shot_notifications"));
    returnFields.push_back(toXmlrpcValue("sg_report_storage_information"));
    returnFields.push_back(toXmlrpcValue("sg_default_start_frame"));
    returnFields.push_back(toXmlrpcValue("sg_ms_project_schedule"));

    return returnFields;
}

} // End namespace Shotgun
