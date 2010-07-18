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

// #include <TipUtil/text.h>
// #include <TipUtil/DailyName.h>

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Daily.h>
#include <Shotgun/Shot.h>
#include <Shotgun/Sequence.h>
#include <Shotgun/Project.h>

namespace Shotgun {

// *****************************************************************************
Daily::Daily(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg), NoteMixin()
{
    m_type = "Version";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Daily::Daily()
    : Entity(NULL)
{
    m_type = "Version";
    m_attrs = NULL;
}

// *****************************************************************************
Daily::Daily(const Daily &ref)
    : Entity(ref.m_sg)
{
    m_type = "Version";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Daily::~Daily()
{
    // Nothing
}

// *****************************************************************************
Daily Daily::create(Shotgun *sg, const std::string &dailyName)
{
    // Check if the daily already exists
    try
    {
        Daily daily = sg->findDailyByName(dailyName);

        std::string err = "Daily \"" + dailyName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
#warning Implement in non-Tippett way
//         TipUtil::DailyName dn = TipUtil::DailyName(dailyName);
//         Show show = sg->findShowByCode(dn.show());
// 
//         // Create a very basic Daily entity with most of its attributes 
//         // be filled later from the Python side.
//         SgMap attrsMap;
//         attrsMap["project"] = toXmlrpcValue(show.asLink());
//         attrsMap["code"] = toXmlrpcValue(dailyName);
//         attrsMap["sg_sequence"] = toXmlrpcValue(dn.sequence());
//         attrsMap["sg_rev"] = toXmlrpcValue(dn.versionStr());
// 
//         // Call the base class function to create an entity
//         return Daily(sg, createEntity(sg, "Version", attrsMap));
    }
}

// *****************************************************************************
Dailies Daily::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create an Daily for each of them
    Dailies dailies;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            dailies.push_back(Daily(sg, result[i]));
        }
    }

    return dailies;
}

// *****************************************************************************
const Shot Daily::sgShot() const
{
#warning Implement in non-Tippett way
//     std::string theShotName = TipUtil::ShotName(sgProjectCode(), sgShotName()).shot(true, true);
// 
//     return m_sg->findShotByName(theShotName);
}

// *****************************************************************************
const Sequence Daily::sgSequence() const
{
    return m_sg->findSequenceByName(sgProjectCode(), sgSequenceName());
}

} // End namespace Shotgun
