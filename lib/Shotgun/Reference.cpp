//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Reference.h>
#include <Shotgun/Asset.h>
#include <Shotgun/Sequence.h>
#include <Shotgun/Shot.h>
#include <Shotgun/Show.h>

namespace Shotgun {

// *****************************************************************************
Reference::Reference(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "CustomEntity02";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Reference::Reference()
    : Entity(NULL)
{
    m_type = "CustomEntity02";
    m_attrs = NULL;
}

// *****************************************************************************
Reference::Reference(const Reference &ref)
    : Entity(ref.m_sg)
{
    m_type = "CustomEntity02";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Reference::~Reference()
{
    // Nothing
}

// *****************************************************************************
Reference Reference::create(Shotgun *sg, 
                            const std::string &showCode,
                            const std::string &referencePath,
                            const std::string &referencePurpose,
                            const Strings &linkAssetNames,
                            const Strings &linkSequenceNames,
                            const Strings &linkShotNames,
                            const Strings &tags)
{
    // Check if the reference already exists. 
    try
    {
        Reference reference = sg->findReferenceByName(showCode, referencePath);

        std::string err = "Reference \"" + referencePath + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        Show show = sg->findShowByCode(showCode);

        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(show.asLink());
        attrsMap["code"] = toXmlrpcValue(referencePath);
        attrsMap["sg_purpose"] = toXmlrpcValue(referencePurpose);

        // Shotgun is currently resticting to one entity for the field.
        if (linkAssetNames.size() > 0)
        {
            try
            {
                Asset asset = sg->findAssetByName(showCode, linkAssetNames[0]);
                
                attrsMap["sg_asset"] = toXmlrpcValue(asset.asLink());
            }
            catch (SgEntityNotFoundError)
            {
                // Do nothing
            }
        }

        // Shotgun is currently resticting to one entity for the field.
        if (linkSequenceNames.size() > 0)
        {
            try
            {
                Sequence sequence = sg->findSequenceByName(showCode, linkSequenceNames[0]);
                
                attrsMap["sg_sequence"] = toXmlrpcValue(sequence.asLink());
            }
            catch (SgEntityNotFoundError)
            {
                // Do nothing
            }
        }

        // Shotgun is currently resticting to one entity for the field.
        if (linkShotNames.size() > 0)
        {
            try
            {
                Shot shot = sg->findShotByName(linkShotNames[0]);
                
                attrsMap["sg_shot"] = toXmlrpcValue(shot.asLink());
            }
            catch (SgEntityNotFoundError)
            {
                // Do nothing
            }
        }

        if (tags.size() > 0)
        {
            attrsMap["tag_list"] = toXmlrpcValue(tags);
        }
        
        // TODO: need to update the thumbnail and quicktime associated with 
        // the reference.

        // Call the base class function to create an entity
        return Reference(sg, createEntity(sg, "CustomEntity02", attrsMap));
    }
}

// *****************************************************************************
References Reference::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create a Shot for each of them
    References references;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            references.push_back(Reference(sg, result[i]));
        }
    }

    return references;
}

// *****************************************************************************
void Reference::sgAsset(const SgMap &val)
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
void Reference::sgSequence(const SgMap &val)
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
void Reference::sgShot(const SgMap &val)
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
