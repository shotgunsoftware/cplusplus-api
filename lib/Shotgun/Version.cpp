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
// Version::Version()
//     : Entity(NULL)
// {
//     m_type = "Version";
//     m_attrs = NULL;
// }

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
Version Version::create(Shotgun *sg, const std::string &versionName)
{
    // Check if the version already exists
    try
    {
        Version version = sg->findVersionByName(versionName);

        std::string err = "Version \"" + versionName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
#warning Implement in non-Tippett way
//         TipUtil::VersionName dn = TipUtil::VersionName(versionName);
//         Show show = sg->findShowByCode(dn.show());
// 
//         // Create a very basic Version entity with most of its attributes 
//         // be filled later from the Python side.
//         SgMap attrsMap;
//         attrsMap["project"] = toXmlrpcValue(show.asLink());
//         attrsMap["code"] = toXmlrpcValue(versionName);
//         attrsMap["sg_sequence"] = toXmlrpcValue(dn.sequence());
//         attrsMap["sg_rev"] = toXmlrpcValue(dn.versionStr());
// 
//         // Call the base class function to create an entity
//         return Version(sg, createEntity(sg, "Version", attrsMap));
    }
}

// *****************************************************************************
Versions Version::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create an Version for each of them
    Versions versions;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            versions.push_back(Version(sg, result[i]));
        }
    }

    return versions;
}

// *****************************************************************************
const Shot Version::sgShot() const
{
#warning Implement in non-Tippett way
//     std::string theShotName = TipUtil::ShotName(sgProjectCode(), sgShotName()).shot(true, true);
// 
//     return m_sg->findShotByName(theShotName);
}

} // End namespace Shotgun
