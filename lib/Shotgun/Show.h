//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#ifndef __SHOW_H__
#define __SHOW_H__

#include <Shotgun/Entity.h>
// #include <TipUtil/text.h>

#define TIPSHOTGUN_SHOW_DEFAULT_HANDLE_DURATION 8
#define TIPSHOTGUN_SHOW_DEFAULT_START_FRAME 101

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Show : public Entity
{
    friend class Shotgun;
    friend class Entity; // So that the base Entity class can call Show::find(..)
 
protected:
    Show(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Show create(Shotgun *sg, 
                       const std::string &showName, 
                       const std::string &showCode);
    static Shows find(Shotgun *sg, SgMap &findMap);
    
public:
    Show();
    Show(const Show &ref);
    virtual ~Show();

    const std::string sgName() const { return getAttrValueAsString("name"); }
    const std::string sgCode() const { return getAttrValueAsString("code"); }
    const std::string sgStatus() const { return getAttrValueAsString("sg_status"); }
    const bool sgArchiveWatcher() const { return getAttrValueAsBool("sg_archive_watcher"); }
    const bool sgPubStillsWatcher() const { return getAttrValueAsBool("sg_pub_stills_watcher"); }
    const bool sgGenerateShotAliases() const { return getAttrValueAsBool("sg_generate_shot_aliases"); }
    const bool sgSendDailiesNotices() const { return getAttrValueAsBool("sg_send_dailies_notices"); }
    const bool sgPolishShotNotifications() const { return getAttrValueAsBool("sg_polish_shot_notifications"); }
    const bool sgReportStorageInformation() const { return getAttrValueAsBool("sg_report_storage_information"); }
    const int sgDefaultStartFrame() const { return getAttrValueAsInt("sg_default_start_frame"); }
    //TODO: check this attr's type
    //const std::string sgMSProjectSchedule() const { return getAttrValueAsString("sg_ms_project_schedule"); }

    // Overrides for base entity methods that don't work correctly 
    // for this entity type
    const std::string sgShowName() const { return sgName(); }
    const std::string sgShowCode() const { return sgCode(); }

    Show &operator=(const Show &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __SHOW_H__
