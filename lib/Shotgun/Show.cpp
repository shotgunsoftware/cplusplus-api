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
