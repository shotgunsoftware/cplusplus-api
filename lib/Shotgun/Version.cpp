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
#include <Shotgun/Version.h>
#include <Shotgun/Shot.h>
#include <Shotgun/Sequence.h>
#include <Shotgun/Project.h>

namespace Shotgun {

// *****************************************************************************
Version::Version(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg), NoteMixin()
{
    m_type = "Version";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Version::Version(const Version &ref)
    : Entity(ref.m_sg)
{
    m_type = "Version";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Version::~Version()
{
    // Nothing
}

// *****************************************************************************
Version *Version::create(Shotgun *sg, const std::string &versionName)
{
    // Check if the version already exists
    try
    {
        Version *version = sg->findVersionByName(versionName);
        delete version;

        std::string err = "Version \"" + versionName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        throw SgEntityCreateError("[Not implemented yet] Version::create(..)");
#warning Implement in non-Tippett way
//         TipUtil::VersionName dn = TipUtil::VersionName(versionName);
// 
//         // Create a very basic Version entity with most of its attributes 
//         // be filled later from the Python side.
//         SgMap attrsMap;
//         attrsMap["project"] = toXmlrpcValue(sg->getProjectLink(projectCode));
//         attrsMap["code"] = toXmlrpcValue(versionName);
//         attrsMap["sg_sequence"] = toXmlrpcValue(dn.sequence());
//         attrsMap["sg_rev"] = toXmlrpcValue(dn.versionStr());
// 
//         return sg->createEntity<Version>(Dict(attrsMap));
    }
}

// *****************************************************************************
SgArray Version::populateReturnFields(const SgArray &extraReturnFields)
{
    SgArray returnFields = extraReturnFields;

    returnFields.push_back(toXmlrpcValue("id"));
    returnFields.push_back(toXmlrpcValue("project"));
    returnFields.push_back(toXmlrpcValue("created_at"));
    returnFields.push_back(toXmlrpcValue("updated_at"));

    returnFields.push_back(toXmlrpcValue("code"));
    returnFields.push_back(toXmlrpcValue("sg_department"));
    returnFields.push_back(toXmlrpcValue("description"));
    returnFields.push_back(toXmlrpcValue("sg_sequence"));
    returnFields.push_back(toXmlrpcValue("entity"));
    returnFields.push_back(toXmlrpcValue("sg_rev"));
    returnFields.push_back(toXmlrpcValue("frame_count"));
    returnFields.push_back(toXmlrpcValue("frame_range"));
    returnFields.push_back(toXmlrpcValue("sg_source"));
    returnFields.push_back(toXmlrpcValue("sg_source_2k"));
    returnFields.push_back(toXmlrpcValue("sg_daily_hd"));
    returnFields.push_back(toXmlrpcValue("image"));
    returnFields.push_back(toXmlrpcValue("sg_status"));
    returnFields.push_back(toXmlrpcValue("sg_status_list"));
    returnFields.push_back(toXmlrpcValue("sg_epk_"));
    returnFields.push_back(toXmlrpcValue("sg_dailies_date"));
    returnFields.push_back(toXmlrpcValue("sg_view_order"));
    returnFields.push_back(toXmlrpcValue("sg_preview_qt"));
    returnFields.push_back(toXmlrpcValue("sg_preview_hd_qt"));
    returnFields.push_back(toXmlrpcValue("user"));

    return returnFields;
}

// *****************************************************************************
const Shot *Version::sgShot() const
{
#warning Implement in non-Tippett way
//     std::string theShotName = TipUtil::ShotName(sgProjectCode(), sgShotName()).shot(true, true);
// 
//     return m_sg->findShotByName(theShotName);
}

} // End namespace Shotgun
