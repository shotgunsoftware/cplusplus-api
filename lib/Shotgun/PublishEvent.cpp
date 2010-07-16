//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/PublishEvent.h>
#include <Shotgun/Show.h>

namespace Shotgun {

// *****************************************************************************
PublishEvent::PublishEvent(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "PublishEvent";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
PublishEvent::PublishEvent()
    : Entity(NULL)
{
    m_type = "PublishEvent";
    m_attrs = NULL;
}

// *****************************************************************************
PublishEvent::PublishEvent(const PublishEvent &ref)
    : Entity(ref.m_sg)
{
    m_type = "PublishEvent";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
PublishEvent::~PublishEvent()
{
    // Nothing
}

// *****************************************************************************
PublishEvent PublishEvent::create(Shotgun *sg, 
                                  const std::string &showCode,
                                  const std::string &publishEventName,
                                  const std::string &publishEventSource,
                                  const std::string &publishEventType,
                                  const int publishEventVersion,
                                  const std::string &publishEventResolution)
{
    // Check if the publishEvent already exists
    try
    {
        PublishEvent publishEvent = sg->findPublishEventByName(showCode, publishEventName);

        std::string err = "PublishEvent \"" + publishEventName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        Show show = sg->findShowByCode(showCode);

        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(show.asLink());
        attrsMap["code"] = toXmlrpcValue(publishEventName);
        attrsMap["sg_file"] = toXmlrpcValue(publishEventSource);
        attrsMap["sg_type"] = toXmlrpcValue(publishEventType);
        attrsMap["sg_resolution"] = toXmlrpcValue(publishEventResolution);

        if (publishEventVersion != TIPSHOTGUN_INVALID_VERSION_NUM)
        {
            attrsMap["sg_rev"] = toXmlrpcValue(publishEventVersion);
        }

        // Call the base class function to create an entity
        return PublishEvent(sg, createEntity(sg, "PublishEvent", attrsMap));
    }
}

// *****************************************************************************
PublishEvents PublishEvent::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create a Shot for each of them
    PublishEvents publishEvents;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            publishEvents.push_back(PublishEvent(sg, result[i]));
        }
    }

    return publishEvents;
}

// *****************************************************************************
void PublishEvent::sgPreviewHDQT(const std::string &val)
{
    SgMap qtLink;
 
    qtLink["content_type"] = toXmlrpcValue("video/quicktime");
    qtLink["url"] = toXmlrpcValue(TIPSHOTGUN_ATTACHMENT_URL + val);
    // TODO: If "name" is omitted, it'll be defaulted to the same as the "url".
    //qtLink["name"] = ; 

    setAttrValue("sg_preview_hd_qt", toXmlrpcValue(qtLink));
}

// *****************************************************************************
void PublishEvent::sgPreviewQT(const std::string &val)
{
    SgMap qtLink;
 
    qtLink["content_type"] = toXmlrpcValue("video/quicktime");
    qtLink["url"] = toXmlrpcValue(TIPSHOTGUN_ATTACHMENT_URL + val);
    // TODO: If "name" is omitted, it'll be defaulted to the same as the "url".
    //qtLink["name"] = ; 

    setAttrValue("sg_preview_qt", toXmlrpcValue(qtLink));
}

} // End namespace Shotgun
