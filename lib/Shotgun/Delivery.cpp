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
#include <Shotgun/Delivery.h>
#include <Shotgun/Project.h>

namespace Shotgun {

// *****************************************************************************
Delivery::Delivery(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Delivery";
    m_attrs = new xmlrpc_c::value(attrs);
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
Delivery *Delivery::create(Shotgun *sg, 
                           const std::string &projectCode,
                           const std::string &deliveryName)
{
    // Check if the delivery already exists
    try
    {
        Delivery *delivery = sg->findDeliveryByName(projectCode, deliveryName);
        delete delivery;

        std::string err = "Delivery \"" + deliveryName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(sg->getProjectLink(projectCode));
        attrsMap["title"] = toXmlrpcValue(deliveryName);

        return sg->createEntity<Delivery>(Dict(attrsMap));
    }
}

// *****************************************************************************
SgArray Delivery::populateReturnFields()
{
    SgArray returnFields;

    returnFields.push_back(toXmlrpcValue("id"));
    returnFields.push_back(toXmlrpcValue("project"));
    returnFields.push_back(toXmlrpcValue("created_at"));
    returnFields.push_back(toXmlrpcValue("updated_at"));

    returnFields.push_back(toXmlrpcValue("title"));
    returnFields.push_back(toXmlrpcValue("sg_delivery_data_size"));
    returnFields.push_back(toXmlrpcValue("sg_delivery_notes"));
    returnFields.push_back(toXmlrpcValue("sg_delivery_path"));
    returnFields.push_back(toXmlrpcValue("sg_delivery_staged_path"));
    returnFields.push_back(toXmlrpcValue("sg_delivery_status"));
    returnFields.push_back(toXmlrpcValue("sg_delivery_type"));
    returnFields.push_back(toXmlrpcValue("sg_wrangler"));
    returnFields.push_back(toXmlrpcValue("sg_wrangler_notes"));
 
    return returnFields;
}

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::Delivery &delivery)
{
    return toStdString(delivery.attrs());
}

// *****************************************************************************
std::string toStdString(const Shotgun::Deliveries &deliveries)
{
    Shotgun::SgArray array;
    for (size_t i = 0; i < deliveries.size(); i++)
    {
        array.push_back(deliveries[i].attrs());
    }
    
    return toStdString(Shotgun::toXmlrpcValue(array));
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Delivery &delivery)
{
    output << toStdString(delivery);
    return output;
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Deliveries &deliveries)
{
    output << toStdString(deliveries);
    return output;
}
