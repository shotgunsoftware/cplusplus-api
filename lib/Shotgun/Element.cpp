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
Element Element::create(Shotgun *sg, 
                        const std::string &projectCode,
                        const std::string &elementName,
                        const std::string &elementType)
{
    // Check if the element already exists
    try
    {
        Element element = sg->findElementByName(projectCode, elementName);

        std::string err = "Element \"" + elementName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        Project project = sg->findProjectByCode(projectCode);

        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(project.asLink());
        attrsMap["code"] = toXmlrpcValue(elementName);
        attrsMap["sg_element_type"] = toXmlrpcValue(elementType);

        // Call the base class function to create an entity
        return Element(sg, createEntity(sg, "Element", attrsMap));
    }
}

// *****************************************************************************
Elements Element::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create a Shot for each of them
    Elements elements;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            elements.push_back(Element(sg, result[i]));
        }
    }

    return elements;
}

// *****************************************************************************
// Don't put this implementation in .h file since Shot class is forward-declared.
const Assets Element::sgAssets() const
{
    Assets assets;

    SgArray entities = getAttrValueAsMultiEntityAttrMap("assets");
    for (size_t i = 0; i < entities.size(); i++)
    {
        assets.push_back(Asset(m_sg, entities[i]));
    }

    return assets;
}

// *****************************************************************************
// Don't put this implementation in .h file since Shot class is forward-declared.
const Shots Element::sgShots() const
{
    Shots shots;

    SgArray entities = getAttrValueAsMultiEntityAttrMap("shots");
    for (size_t i = 0; i < entities.size(); i++)
    {
        shots.push_back(Shot(m_sg, entities[i]));
    }

    return shots;
}

// *****************************************************************************
void Element::sgAssets(const Assets &val)
{
    SgArray assetLinkArray;

    for (size_t i = 0; i < val.size(); i++)
    {
        assetLinkArray.push_back(toXmlrpcValue(val[i].asLink()));
    }

    setAttrValue("assets", toXmlrpcValue(assetLinkArray));
}

// *****************************************************************************
void Element::sgAssets(const SgArray &val)
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
    SgArray shotLinkArray;

    for (size_t i = 0; i < val.size(); i++)
    {
        shotLinkArray.push_back(toXmlrpcValue(val[i].asLink()));
    }

    setAttrValue("shots", toXmlrpcValue(shotLinkArray));
}

// *****************************************************************************
void Element::sgShots(const SgArray &val)
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
