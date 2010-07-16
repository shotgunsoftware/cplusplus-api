//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Delivery.h>
#include <Shotgun/Show.h>

namespace Shotgun {

// *****************************************************************************
Delivery::Delivery(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Delivery";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Delivery::Delivery()
    : Entity(NULL)
{
    m_type = "Delivery";
    m_attrs = NULL;
}

// *****************************************************************************
Delivery::Delivery(const Delivery &ref)
    : Entity(ref.m_sg)
{
    m_type = "Delivery";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Delivery::~Delivery()
{
    // Nothing
}

// *****************************************************************************
Delivery Delivery::create(Shotgun *sg, 
                          const std::string &showCode,
                          const std::string &deliveryName)
{
    // Check if the delivery already exists
    try
    {
        Delivery delivery = sg->findDeliveryByName(showCode, deliveryName);

        std::string err = "Delivery \"" + deliveryName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        Show show = sg->findShowByCode(showCode);
        User user = sg->findUserByLogin(std::string(getenv("USER")));

        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(show.asLink());
        attrsMap["title"] = toXmlrpcValue(deliveryName);
        attrsMap["sg_wrangler"] = toXmlrpcValue(user.asLink());

        // Call the base class function to create an entity
        Delivery delivery = Delivery(sg, createEntity(sg, "Delivery", attrsMap));

        // Update "title" and attach sgId() to it. See addDelivery() in delivery.py.
        char titleStr[32];
        sprintf(titleStr, "%s [%d]", delivery.sgName().c_str(), delivery.sgId());
        delivery.sgName(std::string(titleStr));

        return delivery;
    }
}

// *****************************************************************************
Deliveries Delivery::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create a Delivery for each of them
    Deliveries deliveries;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            deliveries.push_back(Delivery(sg, result[i]));
        }
    }

    return deliveries;
}

} // End namespace Shotgun
