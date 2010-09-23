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
    m_type = "HumanUser";
    m_attrs = new xmlrpc_c::value(attrs);
}


// *****************************************************************************
HumanUser::HumanUser(const HumanUser &ref)
    : Entity(ref.m_sg)
{
    m_type = "HumanUser";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
HumanUser::~HumanUser()
{
    // Nothing
}

// *****************************************************************************
HumanUser *HumanUser::create(Shotgun *sg, 
                             const std::string &userName,
                             const std::string &userLogin,
                             const std::string &userEmail)
{
    // Check if the user already exists
    try
    {
        HumanUser *user = sg->findHumanUserByLogin(userLogin);
        delete user;

        std::string err = "HumanUser \"" + userLogin + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        // Check if there is a retired user with the same name
        try
        {
            HumanUser *retiredHumanUser = sg->findRetiredHumanUser(userLogin);
            delete retiredHumanUser;
            
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

            return sg->createEntity<HumanUser>(Dict(attrsMap));
        }
    }
}

// *****************************************************************************
SgArray HumanUser::populateReturnFields(const SgArray &extraReturnFields)
{
    SgArray returnFields = extraReturnFields;

    returnFields.push_back(toXmlrpcValue("id"));
    returnFields.push_back(toXmlrpcValue("project"));
    returnFields.push_back(toXmlrpcValue("created_at"));
    returnFields.push_back(toXmlrpcValue("updated_at"));

    returnFields.push_back(toXmlrpcValue("name"));
    returnFields.push_back(toXmlrpcValue("admin"));
    returnFields.push_back(toXmlrpcValue("sg_department"));
    returnFields.push_back(toXmlrpcValue("email"));
    returnFields.push_back(toXmlrpcValue("login"));
    returnFields.push_back(toXmlrpcValue("sg_role"));
    returnFields.push_back(toXmlrpcValue("permission_rule_set"));

    return returnFields;
}

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::HumanUser &user)
{
    return toStdString(user.attrs());
}

// *****************************************************************************
std::string toStdString(const Shotgun::HumanUsers &users)
{
    Shotgun::SgArray array;
    for (size_t i = 0; i < users.size(); i++)
    {
        array.push_back(users[i].attrs());
    }
    
    return toStdString(Shotgun::toXmlrpcValue(array));
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::HumanUser &user)
{
    output << toStdString(user);
    return output;
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::HumanUsers &users)
{
    output << toStdString(users);
    return output;
}
