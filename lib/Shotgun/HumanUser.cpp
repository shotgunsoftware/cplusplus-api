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
#include <Shotgun/HumanUser.h>

namespace Shotgun {

// *****************************************************************************
HumanUser::HumanUser(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "HumanHumanUser";
    m_attrs = new xmlrpc_c::value(attrs);
}


// *****************************************************************************
HumanUser::HumanUser(const HumanUser &ref)
    : Entity(ref.m_sg)
{
    m_type = "HumanHumanUser";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
HumanUser::~HumanUser()
{
    // Nothing
}

// *****************************************************************************
HumanUser HumanUser::create(Shotgun *sg, 
                  const std::string &userName,
                  const std::string &userLogin,
                  const std::string &userEmail)
{
    // Check if the user already exists
    try
    {
        HumanUser user = sg->findHumanUserByLogin(userLogin);

        std::string err = "HumanUser \"" + userLogin + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        // Check if there is a retired user with the same name
        try
        {
            HumanUser retiredHumanUser = sg->findRetiredHumanUser(userLogin);
            
            // TODO: need to reset the retired user's login
           
            std::string err = "Retired user \"" + userLogin + "\" already exists.";
            throw SgEntityCreateError(err);
        }
        catch (SgEntityNotFoundError)
        {
            SgMap attrsMap;

            attrsMap["name"] = toXmlrpcValue(userName);
            attrsMap["login"] = toXmlrpcValue(userLogin);
            attrsMap["email"] = toXmlrpcValue(userEmail);

            // Call the base class function to create an entity
            return HumanUser(sg, createEntity(sg, "HumanHumanUser", attrsMap));
        }
    }
}

// *****************************************************************************
HumanUsers HumanUser::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create an HumanUser for each of them
    HumanUsers users;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            users.push_back(HumanUser(sg, result[i]));
        }
    }

    return users;
}

} // End namespace Shotgun
