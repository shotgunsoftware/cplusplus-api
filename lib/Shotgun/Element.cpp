//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Element.h>
#include <Shotgun/Show.h>

namespace Shotgun {

// *****************************************************************************
Element::Element(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Element";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Element::Element()
    : Entity(NULL)
{
    m_type = "Element";
    m_attrs = NULL;
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
                        const std::string &showCode,
                        const std::string &elementName,
                        const std::string &elementType)
{
    // Check if the element already exists
    try
    {
        Element element = sg->findElementByName(showCode, elementName);

        std::string err = "Element \"" + elementName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        Show show = sg->findShowByCode(showCode);

        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(show.asLink());
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
