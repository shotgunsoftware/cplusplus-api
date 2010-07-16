//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Asset.h>
#include <Shotgun/Show.h>

namespace Shotgun {

// *****************************************************************************
Asset::Asset(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg), TaskMixin(), NoteMixin()
{
    m_type = "Asset";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Asset::Asset()
    : Entity(NULL)
{
    m_type = "Asset";
    m_attrs = NULL;
}

// *****************************************************************************
Asset::Asset(const Asset &ref)
    : Entity(ref.m_sg)
{
    m_type = "Asset";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Asset::~Asset()
{
    // Nothing
}

// *****************************************************************************
Asset Asset::create(Shotgun *sg, 
                    const std::string &showCode,
                    const std::string &assetName,
                    const std::string &assetType,
                    const std::string &assetSource)
{
    // Check if the asset already exists
    try
    {
        Asset asset = sg->findAssetByName(showCode, assetName);

        std::string err = "Asset \"" + assetName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        Show show = sg->findShowByCode(showCode);

        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(show.asLink());
        attrsMap["code"] = toXmlrpcValue(assetName);
        attrsMap["sg_asset_type"] = toXmlrpcValue(assetType);

        if (assetSource != "")
        {
            attrsMap["sg_asset_source"] = toXmlrpcValue(assetSource);
        }

        // Call the base class function to create an entity
        return Asset(sg, createEntity(sg, "Asset", attrsMap));
    }
}

// *****************************************************************************
Assets Asset::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create a Shot for each of them
    Assets assets;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            assets.push_back(Asset(sg, result[i]));
        }
    }

    return assets;
}

// *****************************************************************************
const Elements Asset::sgElements() const
{
    Elements elements;

    SgArray entities = getAttrValueAsMultiEntityAttrMap("elements");
    for (size_t i = 0; i < entities.size(); i++)
    {
        elements.push_back(Element(m_sg, entities[i]));
    }

    return elements;
}

// *****************************************************************************
const Assets Asset::sgAssets() const
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
const Shots Asset::sgShots() const
{
    Shots shots;

    SgArray entities = getAttrValueAsMultiEntityAttrMap("shots");
    for (size_t i = 0; i < entities.size(); i++)
    {
        shots.push_back(Shot(m_sg, entities[i]));
    }

    return shots;
}

} // End namespace Shotgun
