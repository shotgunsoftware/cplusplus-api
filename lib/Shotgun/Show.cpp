//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#include <iostream>
#include <vector>

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Show.h>

namespace Shotgun {

// *****************************************************************************
Show::Show(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Project";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Show::Show()
    : Entity(NULL)
{
    m_type = "Project";
    m_attrs = NULL;
}

// *****************************************************************************
Show::Show(const Show &ref)
    : Entity(ref.m_sg)
{
    m_type = "Show";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Show::~Show()
{
    // Nothing
}

// *****************************************************************************
Show Show::create(Shotgun *sg, 
                  const std::string &showName,
                  const std::string &showCode)
{
    // Check if the show already exists
    try
    {
        Show show = sg->findShowByCode(showCode);

        std::string err = "Show \"" + showCode + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        SgMap attrsMap;

        attrsMap["code"] = toXmlrpcValue(showCode);
        attrsMap["name"] = toXmlrpcValue(showName);
        attrsMap["sg_status"] = toXmlrpcValue("Active");
        attrsMap["sg_handle_duration"] = toXmlrpcValue(TIPSHOTGUN_SHOW_DEFAULT_HANDLE_DURATION);
        attrsMap["sg_default_start_frame"] = toXmlrpcValue(TIPSHOTGUN_SHOW_DEFAULT_START_FRAME);

        // Call the base class function to create an entity
        return Show(sg, createEntity(sg, "Project", attrsMap));
    }
}

// *****************************************************************************
Shows Show::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create an Show for each of them
    Shows shows;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            shows.push_back(Show(sg, result[i]));
        }
    }

    return shows;
}

} // End namespace Shotgun
