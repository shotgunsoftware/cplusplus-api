//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/User.h>

namespace Shotgun {

// *****************************************************************************
User::User(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "HumanUser";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
User::User()
    : Entity(NULL)
{
    m_type = "HumanUser";
    m_attrs = NULL;
}

// *****************************************************************************
User::User(const User &ref)
    : Entity(ref.m_sg)
{
    m_type = "HumanUser";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
User::~User()
{
    // Nothing
}

// *****************************************************************************
User User::create(Shotgun *sg, 
                  const std::string &userName,
                  const std::string &userLogin,
                  const std::string &userEmail,
                  const std::string &userDept)
{
    // Check if the user already exists
    try
    {
        User user = sg->findUserByLogin(userLogin);

        std::string err = "User \"" + userLogin + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        // Check if there is a retired user with the same name
        try
        {
            User retiredUser = sg->findRetiredUser(userLogin);
            
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
            attrsMap["sg_department"] = toXmlrpcValue(userDept);

            // Call the base class function to create an entity
            return User(sg, createEntity(sg, "HumanUser", attrsMap));
        }
    }
}

// *****************************************************************************
Users User::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create an User for each of them
    Users users;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            users.push_back(User(sg, result[i]));
        }
    }

    return users;
}

} // End namespace Shotgun
