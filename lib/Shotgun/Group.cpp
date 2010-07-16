//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Group.h>
#include <Shotgun/Show.h>

namespace Shotgun {

// *****************************************************************************
Group::Group(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Group";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Group::Group()
    : Entity(NULL)
{
    m_type = "Group";
    m_attrs = NULL;
}

// *****************************************************************************
Group::Group(const Group &ref)
    : Entity(ref.m_sg)
{
    m_type = "Group";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Group::~Group()
{
    // Nothing
}

// *****************************************************************************
Group Group::create(Shotgun *sg, const std::string &groupName)
{
    // Check if the group already exists
    try
    {
        Group group = sg->findGroupByName(groupName);

        std::string err = "Group \"" + groupName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        SgMap attrsMap;
        attrsMap["code"] = toXmlrpcValue(groupName);

        // Call the base class function to create an entity
        return Group(sg, createEntity(sg, "Group", attrsMap));
    }
}

// *****************************************************************************
Groups Group::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create a Group for each of them
    Groups groups;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            groups.push_back(Group(sg, result[i]));
        }
    }

    return groups;
}

} // End namespace Shotgun
