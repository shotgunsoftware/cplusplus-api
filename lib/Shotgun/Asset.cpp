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
#include <Shotgun/Project.h>

namespace Shotgun {

// *****************************************************************************
Asset::Asset(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg), TaskMixin(), NoteMixin()
{
    m_type = "Asset";
    m_attrs = new xmlrpc_c::value(attrs);
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
Asset *Asset::create(Shotgun *sg, 
                     const std::string &projectCode,
                     const std::string &assetName,
                     const std::string &assetType,
                     const std::string &assetSource)
{
    // Check if the asset already exists
    try
    {
        Asset *asset = sg->findAssetByName(projectCode, assetName);
        delete asset;

        std::string err = "Asset \"" + assetName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(sg->getProjectLink(projectCode));
        attrsMap["code"] = toXmlrpcValue(assetName);
        attrsMap["sg_asset_type"] = toXmlrpcValue(assetType);

        if (assetSource != "")
        {
            attrsMap["sg_asset_source"] = toXmlrpcValue(assetSource);
        }

        return sg->createEntity<Asset>(Dict(attrsMap));
    }
}

// *****************************************************************************
SgArray Asset::populateReturnFields()
{
    SgArray returnFields;
    
    returnFields.push_back(toXmlrpcValue("id"));
    returnFields.push_back(toXmlrpcValue("project"));
    returnFields.push_back(toXmlrpcValue("created_at"));
    returnFields.push_back(toXmlrpcValue("updated_at"));

    returnFields.push_back(toXmlrpcValue("code"));
    returnFields.push_back(toXmlrpcValue("sg_asset_type"));
    returnFields.push_back(toXmlrpcValue("sg_status_list"));
    returnFields.push_back(toXmlrpcValue("sg_asset_preview_qt"));
    returnFields.push_back(toXmlrpcValue("sg_asset_source"));
    returnFields.push_back(toXmlrpcValue("elements"));
    returnFields.push_back(toXmlrpcValue("parents"));
    returnFields.push_back(toXmlrpcValue("assets"));
    returnFields.push_back(toXmlrpcValue("shots"));

    return returnFields;
}

// *****************************************************************************
const ElementPtrs Asset::sgElements() const
{
    ElementPtrs elements;

    EntityPtrs entities = getAttrValueAsMultiEntityPtr("elements");
    for (size_t i = 0; i < entities.size(); i++)
    {
        if (Element *element = dynamic_cast<Element *>(entities[i]))
        {
            elements.push_back(element);
        }
    }

    return elements;
}

// *****************************************************************************
const AssetPtrs Asset::sgAssets() const
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
const ShotPtrs Asset::sgShots() const
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

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::Asset &asset)
{
    return toStdString(asset.attrs());
}

// *****************************************************************************
std::string toStdString(const Shotgun::Assets &assets)
{
    Shotgun::SgArray array;
    for (size_t i = 0; i < assets.size(); i++)
    {
        array.push_back(assets[i].attrs());
    }
    
    return toStdString(Shotgun::toXmlrpcValue(array));
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Asset &asset)
{
    output << toStdString(asset);
    return output;
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Assets &assets)
{
    output << toStdString(assets);
    return output;
}
