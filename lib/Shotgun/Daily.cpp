//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

// #include <TipUtil/text.h>
// #include <TipUtil/DailyName.h>

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Daily.h>
#include <Shotgun/Shot.h>
#include <Shotgun/Sequence.h>
#include <Shotgun/Show.h>

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
//     std::string theShotName = TipUtil::ShotName(sgShowCode(), sgShotName()).shot(true, true);
// 
//     return m_sg->findShotByName(theShotName);
}

// *****************************************************************************
const Sequence Daily::sgSequence() const
{
    return m_sg->findSequenceByName(sgShowCode(), sgSequenceName());
}

} // End namespace Shotgun
