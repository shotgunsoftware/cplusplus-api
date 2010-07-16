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
