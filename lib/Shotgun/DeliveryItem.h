//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#ifndef __DELIVERY_ITEM_H__
#define __DELIVERY_ITEM_H__

#include <iostream>
#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Asset.h>
#include <Shotgun/Shot.h>
#include <Shotgun/Sequence.h>
#include <Shotgun/Delivery.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class DeliveryItem : public Entity
{
    friend class Shotgun;
    friend class Entity;
 
protected:
    DeliveryItem(Shotgun *sg, const xmlrpc_c::value &attrs);

    static DeliveryItem create(Shotgun *sg, 
                               const std::string &showCode,
                               const std::string &deliveryItemName,
                               const SgMap &deliveryLink = SgMap());
    static DeliveryItems find(Shotgun *sg, SgMap &findMap);
    
public:
    DeliveryItem();
    DeliveryItem(const DeliveryItem &ref);
    virtual ~DeliveryItem();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); } 
    const Asset sgAsset() const { return Asset(m_sg, getAttrValueAsEntityAttrMap("sg_asset")); } 
    const Delivery sgDelivery() const { return Delivery(m_sg, getAttrValueAsEntityAttrMap("sg_delivery")); } 
    const std::string sgStagingStatus() const { return getAttrValueAsString("sg_staging_status"); } 
    const std::string sgStagingQt() const { return getAttrValueAsQtPath("sg_staging_qt"); } 
    const std::string sgProcessingStatus() const { return getAttrValueAsString("sg_processing_status"); } 
    const std::string sgQualityControlStatus() const { return getAttrValueAsString("sg_quality_control_status"); } 
    const std::string sgDataSize() const { return getAttrValueAsString("sg_data_size"); } 
    const std::string sgFiles() const { return getAttrValueAsString("sg_files"); } 
    const std::string sgNotes() const { return getAttrValueAsString("sg_notes"); } 
    const int sgPriority() const { return getAttrValueAsInt("sg_priority"); } 
    const std::string sgProcessingType() const { return getAttrValueAsString("sg_processing_type"); } 
    const std::string sgPublishType() const { return getAttrValueAsString("sg_publish_type"); } 
    const Sequence sgSequence() const { return Sequence(m_sg, getAttrValueAsEntityAttrMap("sg_sequence")); } 
    const Shot sgShot() const { return Shot(m_sg, getAttrValueAsEntityAttrMap("sg_shot")); } 
    const std::string sgTippettName() const { return getAttrValueAsString("sg_tippett_name"); } 
    const std::string sgTippettPath() const { return getAttrValueAsString("sg_tippett_path"); } 
    const int sgTippettStartFrame() const { return getAttrValueAsInt("sg_tippett_start_frame"); } 
    const std::string sgWranglerNotes() const { return getAttrValueAsString("sg_wrangler_notes"); } 
    const std::string sgPath() const { return sgDelivery().sgPath(); }

    // Set an attribute's value
    void sgName(const std::string &val) { setAttrValue("code", toXmlrpcValue(val)); }
    void sgAsset(const Asset &val) { setAttrValue("sg_asset", toXmlrpcValue(val.asLink())); }
    void sgAsset(const SgMap &val);
    void sgDelivery(const Delivery &val) { setAttrValue("sg_delivery", toXmlrpcValue(val.asLink())); }
    void sgDelivery(const SgMap &val);
    void sgStagingStatus(const std::string &val) { setAttrValue("sg_staging_status", toXmlrpcValue(val)); }
    void sgStagingQt(const std::string &val) { setAttrValue("sg_staging_qt", toXmlrpcValue(val)); }
    void sgProcessingStatus(const std::string &val) { setAttrValue("sg_processing_status", toXmlrpcValue(val)); }
    void sgQualityControlStatus(const std::string &val) { setAttrValue("sg_quality_control_status", toXmlrpcValue(val)); }
    void sgDataSize(const std::string &val) { setAttrValue("sg_data_size", toXmlrpcValue(val)); }
    void sgFiles(const std::string &val) { setAttrValue("sg_files", toXmlrpcValue(val)); }
    void sgNotes(const std::string &val) { setAttrValue("sg_notes", toXmlrpcValue(val)); }
    void sgPriority(const int val) { setAttrValue("sg_priority", toXmlrpcValue(val)); }
    void sgProcessingType(const std::string &val) { setAttrValue("sg_processing_type", toXmlrpcValue(val)); }
    void sgPublishType(const std::string &val) { setAttrValue("sg_publish_type", toXmlrpcValue(val)); }
    void sgSequence(const Sequence &val) { setAttrValue("sg_sequence", toXmlrpcValue(val.asLink())); }
    void sgSequence(const SgMap &val);
    void sgShot(const Shot &val) { setAttrValue("sg_shot", toXmlrpcValue(val.asLink())); }
    void sgShot(const SgMap &val);
    void sgTippettName(const std::string &val) { setAttrValue("sg_tippett_name", toXmlrpcValue(val)); }
    void sgTippettPath(const std::string &val) { setAttrValue("sg_tippett_path", toXmlrpcValue(val)); }
    void sgTippettStartFrame(const int val) { setAttrValue("sg_tippett_start_frame", toXmlrpcValue(val)); }
    void sgWranglerNotes(const std::string &val) { setAttrValue("sg_wrangler_notes", toXmlrpcValue(val)); }

    DeliveryItem &operator=(const DeliveryItem &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __DELIVERY_ITEM_H__
