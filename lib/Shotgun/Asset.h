//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#ifndef __ASSET_H__
#define __ASSET_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>
#include <Shotgun/TaskMixin.h>
#include <Shotgun/NoteMixin.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Asset : public Entity, public TaskMixin, public NoteMixin
{
    friend class Shotgun;
    friend class Element;
    friend class DeliveryItem;
    friend class Reference;
    friend class Entity;
 
protected:
    Asset(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Asset create(Shotgun *sg, 
                        const std::string &showCode,
                        const std::string &assetName,
                        const std::string &assetType,
                        const std::string &assetSource = "");
    static Assets find(Shotgun *sg, SgMap &findMap);
    
public:
    Asset();
    Asset(const Asset &ref);
    virtual ~Asset();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); }
    const std::string sgType() const { return getAttrValueAsString("sg_asset_type"); }
    const std::string sgStatus() const { return getAttrValueAsString("sg_status_list"); }
    const std::string sgPreviewQt() const { return getAttrValueAsString("sg_asset_preview_qt"); }
    const std::string sgSource() const { return getAttrValueAsString("sg_asset_source"); }
    const SgArray sgParents() const { return getAttrValueAsArray("parents"); }
    const Elements sgElements() const;
    const Assets sgAssets() const;
    const Shots sgShots() const;

    Asset &operator=(const Asset &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __ASSET_H__
