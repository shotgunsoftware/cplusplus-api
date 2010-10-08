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
List Delivery::defaultReturnFields()
{
    return List("id")
           .append("project")
           .append("created_at")
           .append("updated_at")
           .append("title")
           .append("sg_delivery_data_size")
           .append("sg_delivery_notes")
           .append("sg_delivery_path")
           .append("sg_delivery_staged_path")
           .append("sg_delivery_status")
           .append("sg_delivery_type")
           .append("sg_wrangler")
           .append("sg_wrangler_notes");
}

// *****************************************************************************
void Delivery::sgName(const std::string &val)
{
    setAttrValue(Fields("title", val));
}

// *****************************************************************************
void Delivery::sgStatus(const std::string &val)
{
    setAttrValue(Fields("sg_delivery_status", val));
}

// *****************************************************************************
void Delivery::sgType(const std::string &val)
{
    setAttrValue(Fields("sg_delivery_type", val));
}

} // End namespace Shotgun
