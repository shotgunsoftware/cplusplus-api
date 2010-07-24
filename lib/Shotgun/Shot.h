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

#ifndef __SHOT_H__
#define __SHOT_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Daily.h>
#include <Shotgun/Sequence.h>
#include <Shotgun/Element.h>
#include <Shotgun/TaskMixin.h>
#include <Shotgun/NoteMixin.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Shot : public Entity, public TaskMixin, public NoteMixin
{
    friend class Shotgun;
    friend class Daily;
    friend class Element;
    friend class ReviewItem;
    friend class Reference;
    friend class Note;
    friend class Asset;
    friend class Entity;
 
protected:
    Shot(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Shot create(Shotgun *sg, 
                       const std::string &shotName,
                       const std::string &shotType = "");
    static Shots find(Shotgun *sg, SgMap &findMap);
    
public:
    Shot();
    Shot(const Shot &ref);
    virtual ~Shot();

    // Set an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); }
    const bool sgCbb() const { return getAttrValueAsBool("sg_cbb_"); } 
    const int sgContinuity() const { return getAttrValueAsInt("sg_continuity"); }
    const std::string sgDescription() const { return getAttrValueAsString("description"); } 
    const Elements sgElements() const;
    const int sgEstimatedFrameRenderHours() const { return getAttrValueAsInt("sg_estimated_frame_render_hours"); }
    const Daily sgFinalDaily() const { return Daily(m_sg, getAttrValueAsEntityAttrMap("sg_final_daily")); } 
    const Daily sgLatestDaily() const { return Daily(m_sg, getAttrValueAsEntityAttrMap("sg_latest_daily")); } 
    const int sgLens() const { return getAttrValueAsInt("sg_lens"); }
    const bool sgOmit() const { return getAttrValueAsBool("sg_omit_"); } 
    const bool sgOnHold() const { return getAttrValueAsBool("sg_on_hold_"); } 
    const std::string sgProdVFX() const { return getAttrValueAsString("sg_prod_vfx__"); }
    const Sequence sgSequence() const { return Sequence(m_sg, getAttrValueAsEntityAttrMap("sg_sequence")); } 
    const std::string sgShotNotifications() const { return getAttrValueAsString("sg_shot_notifications"); } 
    const std::string sgProject() const { return sgProjectName(); }
    const std::string sgStatus() const { return getAttrValueAsString("sg_status_list"); } 
    const bool sgTurnover() const { return getAttrValueAsBool("sg_turnover_"); }
    const std::string sgType() const { return getAttrValueAsString("sg_type"); }
    const std::string sgActualPlateResolution() const { return getAttrValueAsString("sg_actual_plate_resolution"); }
    // TODO: const std::string sgActualPlateImageFormat() const { return getActualPlateImageFormat(); } 
    const std::string sgStorageTier() const { return getAttrValueAsString("sg_storage___tier"); } 
    const std::string sgStorageFilesystem() const { return getAttrValueAsString("sg_storage___filesystem"); } 
    const std::string sgStorageFilesystemUsedPercentage() const { return getAttrValueAsString("sg_storage___filesystem_used_percentage"); } 
    const int sgStorageSizeGb() const { return getAttrValueAsInt("sg_storage___size_gb"); } 
    const double sgPixelAspect() const { return getAttrValueAsDouble("sg_pixel_aspect"); }
    const std::string sgSlateBurninInfo() const { return getAttrValueAsString("sg_slate_burnin_info"); }
    const std::string sgSlateHeaderInfo() const { return getAttrValueAsString("sg_slate_header_info"); }
    const int sgCutDuration() const { return getAttrValueAsInt("smart_cut_duration"); }
    const int sgCutIn() const { return getAttrValueAsInt("smart_cut_in"); }
    const int sgCutOut() const { return getAttrValueAsInt("smart_cut_out"); }
    const std::string sgCutSummary() const { return getAttrValueAsString("smart_cut_summary_display"); }
    const std::string sgDurationSummary() const { return getAttrValueAsString("smart_duration_summary_display"); }
    const int sgHeadDuration() const { return getAttrValueAsInt("smart_head_duration"); }
    const int sgHeadIn() const { return getAttrValueAsInt("smart_head_in"); }
    const int sgHeadOut() const { return getAttrValueAsInt("smart_head_out"); }
    const int sgTailDuration() const { return getAttrValueAsInt("smart_tail_duration"); }
    const int sgTailIn() const { return getAttrValueAsInt("smart_tail_in"); }
    const int sgTailOut() const { return getAttrValueAsInt("smart_tail_out"); }
    const int sgWorkingDuration() const { return getAttrValueAsInt("smart_working_duration"); }
    const std::string sgTippettWorkingLength() const { return getTippettWorkingLength(); }

    // Set an attribute's value
    void sgCbb(const bool val) { setAttrValue("sg_cbb_", toXmlrpcValue(val)); }
    void sgFinalDaily(const Daily &val) { setAttrValue("sg_final_daily", toXmlrpcValue(val.asLink())); }
    void sgFinalDaily(const SgMap &val);
    void sgLatestDaily(const Daily &val) { setAttrValue("sg_latest_daily", toXmlrpcValue(val.asLink())); }
    void sgLatestDaily(const SgMap &val);
    void sgOmit(const bool val) { setAttrValue("sg_omit_", toXmlrpcValue(val)); }
    void sgOnHold(const bool val) { setAttrValue("sg_on_hold_", toXmlrpcValue(val)); }
    void sgSequence(const Sequence &val) { setAttrValue("sg_sequence", toXmlrpcValue(val.asLink())); }
    void sgSequence(const SgMap &val);
    void sgShotNotifications(const std::string &val) { setAttrValue("sg_shot_notifications", toXmlrpcValue(val)); }
    void sgStatus(const std::string &val) { setAttrValue("sg_status_list", toXmlrpcValue(val)); }
    void sgStorageTier(const std::string &val) { setAttrValue("sg_storage___tier", toXmlrpcValue(val)); }
    void sgStorageFilesystem(const std::string &val) { setAttrValue("sg_storage___filesystem", toXmlrpcValue(val)); }
    void sgStorageFilesystemUsedPercentage(const std::string &val) { setAttrValue("sg_storage___filesystem_used_percentage", toXmlrpcValue(val)); }
    void sgStorageSizeGb(const int val) { setAttrValue("sg_storage___size_gb", toXmlrpcValue(val)); }
    void sgElements(const Elements &val); // An array of Element entities
    void sgElements(const SgArray &val); // An array of entity links

    Shot &operator=(const Shot &that)
    {
        Entity::operator=(that);
        return *this;
    }

protected:
    // TODO: const std::string getActualPlateImageFormat() const; // need to search the studio database
    const std::string getTippettWorkingLength() const;
};

} // End namespace Shotgun

#endif    // End #ifdef __SHOT_H__
