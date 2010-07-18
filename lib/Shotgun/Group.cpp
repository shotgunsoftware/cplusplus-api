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
#include <Shotgun/Group.h>

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
