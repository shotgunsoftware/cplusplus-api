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
#include <Shotgun/Element.h>
#include <Shotgun/Project.h>

namespace Shotgun {

// *****************************************************************************
Element::Element(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Element";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Element::Element(const Element &ref)
    : Entity(ref.m_sg)
{
    m_type = "Element";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Element::~Element()
{
    // Nothing
}

// *****************************************************************************
List Element::populateReturnFields()
{
    return List("id")
           .append("project")
           .append("created_at")
           .append("updated_at")
           .append("code")
           .append("assets")
           .append("shots")
           .append("tag_list")
           .append("sg_element_type");
}

// *****************************************************************************
// Don't put this implementation in .h file since Shot class is forward-declared.
const AssetPtrs Element::sgAssets() const
{
    AssetPtrs assets;

    EntityPtrs entities = getAttrValueAsMultiEntityPtr("assets");
    for (size_t i = 0; i < entities.size(); i++)
    {
        if (Asset *asset = dynamic_cast<Asset *>(entities[i]))
        {
            assets.push_back(asset);
        }
    }

    return assets;
}

// *****************************************************************************
// Don't put this implementation in .h file since Shot class is forward-declared.
const ShotPtrs Element::sgShots() const
{
    ShotPtrs shots;

    EntityPtrs entities = getAttrValueAsMultiEntityPtr("shots");
    for (size_t i = 0; i < entities.size(); i++)
    {
        if (Shot *shot = dynamic_cast<Shot *>(entities[i]))
        {
            shots.push_back(shot);
        }
    }

    return shots;
}

// *****************************************************************************
void Element::sgAssets(const Assets &val)
{
    List assetLinkList;

    for (size_t i = 0; i < val.size(); i++)
    {
        assetLinkList.append(val[i].asLink());
    }

    setAttrValue("assets", toXmlrpcValue(assetLinkList));
}

// *****************************************************************************
void Element::sgAssets(const List &val)
{
    for (size_t i = 0; i < val.size(); i++)
    {
        try
        {
            Entity::validateLink(val[i]);
        }
        catch (SgAttrLinkError &error)
        {
            throw SgAttrSetValueError("assets", error.what());
        }
    }

    setAttrValue("assets", toXmlrpcValue(val));
}

// *****************************************************************************
void Element::sgShots(const Shots &val)
{
    List shotLinkList;

    for (size_t i = 0; i < val.size(); i++)
    {
        shotLinkList.append(val[i].asLink());
    }

    setAttrValue("shots", toXmlrpcValue(shotLinkList));
}

// *****************************************************************************
void Element::sgShots(const List &val)
{
    for (size_t i = 0; i < val.size(); i++)
    {
        try
        {
            Entity::validateLink(val[i]);
        }
        catch (SgAttrLinkError &error)
        {
            throw SgAttrSetValueError("shots", error.what());
        }
    }

    setAttrValue("shots", toXmlrpcValue(val));
}

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::Element &element)
{
    return toStdString(element.attrs());
}

// *****************************************************************************
std::string toStdString(const Shotgun::Elements &elements)
{
    Shotgun::List list;
    for (size_t i = 0; i < elements.size(); i++)
    {
        list.append(elements[i].attrs());
    }
    
    return toStdString(list);
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Element &element)
{
    output << toStdString(element);
    return output;
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Elements &elements)
{
    output << toStdString(elements);
    return output;
}
