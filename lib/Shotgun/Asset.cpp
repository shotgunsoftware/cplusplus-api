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
