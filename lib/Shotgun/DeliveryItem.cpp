//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/DeliveryItem.h>
#include <Shotgun/Show.h>

namespace Shotgun {

// *****************************************************************************
DeliveryItem::DeliveryItem(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "CustomEntity01";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
DeliveryItem::DeliveryItem()
    : Entity(NULL)
{
    m_type = "CustomEntity01";
    m_attrs = NULL;
}

// *****************************************************************************
DeliveryItem::DeliveryItem(const DeliveryItem &ref)
    : Entity(ref.m_sg)
{
    m_type = "CustomEntity01";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
DeliveryItem::~DeliveryItem()
{
    // Nothing
}

// *****************************************************************************
DeliveryItem DeliveryItem::create(Shotgun *sg, 
                                  const std::string &showCode,
                                  const std::string &deliveryItemName,
                                  const SgMap &deliveryLink)
{
    // Check if the deliveryItem already exists
    try
    {
        DeliveryItem deliveryItem = sg->findDeliveryItemByName(showCode, deliveryItemName);

        std::string err = "DeliveryItem \"" + deliveryItemName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        Show show = sg->findShowByCode(showCode);

        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(show.asLink());
        attrsMap["code"] = toXmlrpcValue(deliveryItemName);

        if (!deliveryLink.empty())
        {
            attrsMap["sg_delivery"] = toXmlrpcValue(deliveryLink);
        }

        // Call the base class function to create an entity
        return DeliveryItem(sg, createEntity(sg, "CustomEntity01", attrsMap));
    }
}

// *****************************************************************************
DeliveryItems DeliveryItem::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create a DeliveryItem 
    // (i.e. CustomEntity01) for each of them
    DeliveryItems deliveryItems;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            deliveryItems.push_back(DeliveryItem(sg, result[i]));
        }
    }

    return deliveryItems;
}

// *****************************************************************************
void DeliveryItem::sgAsset(const SgMap &val)
{
    try
    {
        Entity::validateLink(val);
    }
    catch (SgAttrLinkError &error)
    {
        throw SgAttrSetValueError("sg_asset", error.what());
    }

    setAttrValue("sg_asset", toXmlrpcValue(val));
}

// *****************************************************************************
void DeliveryItem::sgDelivery(const SgMap &val)
{
    try
    {
        Entity::validateLink(val);
    }
    catch (SgAttrLinkError &error)
    {
        throw SgAttrSetValueError("sg_delivery", error.what());
    }

    setAttrValue("sg_delivery", toXmlrpcValue(val));
}

// *****************************************************************************
void DeliveryItem::sgSequence(const SgMap &val)
{
    try
    {
        Entity::validateLink(val);
    }
    catch (SgAttrLinkError &error)
    {
        throw SgAttrSetValueError("sg_sequence", error.what());
    }

    setAttrValue("sg_sequence", toXmlrpcValue(val));
}

// *****************************************************************************
void DeliveryItem::sgShot(const SgMap &val)
{
    try
    {
        Entity::validateLink(val);
    }
    catch (SgAttrLinkError &error)
    {
        throw SgAttrSetValueError("sg_shot", error.what());
    }

    setAttrValue("sg_shot", toXmlrpcValue(val));
}

} // End namespace Shotgun
