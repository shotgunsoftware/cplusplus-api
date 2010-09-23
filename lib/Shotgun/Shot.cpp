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

#include <iostream>

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Shot.h>
#include <Shotgun/Sequence.h>
#include <Shotgun/Project.h>

namespace Shotgun {

// *****************************************************************************
Shot::Shot(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg), TaskMixin(), NoteMixin()
{
    m_type = "Shot";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Shot::Shot(const Shot &ref)
    : Entity(ref.m_sg)
{
    m_type = "Shot";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Shot::~Shot()
{
    // Nothing
}

// *****************************************************************************
Shot *Shot::create(Shotgun *sg, 
                   const std::string &projectCode,
                   const std::string &shotName,
                   const std::string &sequenceName)
{
    // Check if the shot already exists
    try
    {
#warning TODO: Include project (& sequence?) in search
        Shot *shot = sg->findShotByName(shotName);
        delete shot;

        std::string err = "Shot \"" + shotName + "\" already exists.";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
#warning TODO: Fix this
//         Sequence *seq;
//         try
//         {
//             seq = sg->findSequenceByName(projectCode, sequenceName);
//         }
//         catch (SgEntityNotFoundError)
//         {
//             seq = sg->createSequence(sn.project(), sn.sequence());
//         }

        // Other attributes will be filled by the python code
        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(sg->getProjectLink(projectCode));
        attrsMap["code"] = toXmlrpcValue(shotName);
//         attrsMap["sg_sequence"] = toXmlrpcValue(seq->asLink());
//         delete seq;
        
        return sg->createEntity<Shot>(Dict(attrsMap));
    }
}

// *****************************************************************************
SgArray Shot::populateReturnFields(const SgArray &extraReturnFields)
{
    SgArray returnFields = extraReturnFields;

    returnFields.push_back(toXmlrpcValue("id"));
    returnFields.push_back(toXmlrpcValue("project"));
    returnFields.push_back(toXmlrpcValue("created_at"));
    returnFields.push_back(toXmlrpcValue("updated_at"));

    returnFields.push_back(toXmlrpcValue("code"));
    returnFields.push_back(toXmlrpcValue("sg_continuity"));
    returnFields.push_back(toXmlrpcValue("description"));
    returnFields.push_back(toXmlrpcValue("elements"));
    returnFields.push_back(toXmlrpcValue("sg_estimated_frame_render_hours"));
    returnFields.push_back(toXmlrpcValue("sg_final_daily"));
    returnFields.push_back(toXmlrpcValue("sg_latest_daily"));
    returnFields.push_back(toXmlrpcValue("sg_lens"));
    returnFields.push_back(toXmlrpcValue("sg_prod_vfx__"));
    returnFields.push_back(toXmlrpcValue("sg_sequence"));
    returnFields.push_back(toXmlrpcValue("sg_shot_notifications"));
    returnFields.push_back(toXmlrpcValue("project_names"));
    returnFields.push_back(toXmlrpcValue("sg_status_list"));
    returnFields.push_back(toXmlrpcValue("sg_turnover_"));
    returnFields.push_back(toXmlrpcValue("sg_type"));
    returnFields.push_back(toXmlrpcValue("sg_omit_"));
    returnFields.push_back(toXmlrpcValue("sg_on_hold_"));
    returnFields.push_back(toXmlrpcValue("sg_cbb_"));
    returnFields.push_back(toXmlrpcValue("smart_cut_duration"));
    returnFields.push_back(toXmlrpcValue("smart_cut_in"));
    returnFields.push_back(toXmlrpcValue("smart_cut_out"));
    returnFields.push_back(toXmlrpcValue("smart_cut_summary_display"));
    returnFields.push_back(toXmlrpcValue("smart_duration_summary_display"));
    returnFields.push_back(toXmlrpcValue("smart_head_duration"));
    returnFields.push_back(toXmlrpcValue("smart_head_in"));
    returnFields.push_back(toXmlrpcValue("smart_head_out"));
    returnFields.push_back(toXmlrpcValue("smart_tail_duration"));
    returnFields.push_back(toXmlrpcValue("smart_tail_in"));
    returnFields.push_back(toXmlrpcValue("smart_tail_out"));
    returnFields.push_back(toXmlrpcValue("smart_working_duration"));
    returnFields.push_back(toXmlrpcValue("sg_tippett_working_length"));
    returnFields.push_back(toXmlrpcValue("sg_actual_plate_resolution"));
    returnFields.push_back(toXmlrpcValue("sg_storage___tier"));
    returnFields.push_back(toXmlrpcValue("sg_storage___filesystem"));
    returnFields.push_back(toXmlrpcValue("sg_storage___filesystem_used_percentage"));
    returnFields.push_back(toXmlrpcValue("sg_storage___size_gb"));
    returnFields.push_back(toXmlrpcValue("sg_slate_burnin_info"));
    returnFields.push_back(toXmlrpcValue("sg_slate_header_info"));
    returnFields.push_back(toXmlrpcValue("sg_pixel_aspect"));

    return returnFields;
}

// *****************************************************************************
void Shot::sgSequence(const SgMap &val)
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
const ElementPtrs Shot::sgElements() const
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
void Shot::sgElements(const Elements &val)
{
    SgArray elementLinkArray;

    for (size_t i = 0; i < val.size(); i++)
    {
        elementLinkArray.push_back(toXmlrpcValue(val[i].asLink()));
    }

    setAttrValue("elements", toXmlrpcValue(elementLinkArray));
}

// *****************************************************************************
void Shot::sgElements(const SgArray &val)
{
    for (size_t i = 0; i < val.size(); i++)
    {
        try
        {
            Entity::validateLink(val[i]);
        }
        catch (SgAttrLinkError &error)
        {
            throw SgAttrSetValueError("elements", error.what());
        }
    }

    setAttrValue("elements", toXmlrpcValue(val));
}

// *****************************************************************************
const Sequence *Shot::sgSequence() const
{
    const Entity *entity = getAttrValueAsEntityPtr("sg_sequence");
    if (const Sequence *sequence = dynamic_cast<const Sequence *>(entity))
    {
        return sequence;
    }
    else
    {
        throw SgEntityDynamicCastError("Sequence");
    } 
}

} // End namespace Shotgun
