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
List Shot::populateReturnFields()
{
    return List("id")
           .append("project")
           .append("created_at")
           .append("updated_at")
           .append("code")
           .append("sg_continuity")
           .append("description")
           .append("elements")
           .append("sg_estimated_frame_render_hours")
           .append("sg_final_daily")
           .append("sg_latest_daily")
           .append("sg_lens")
           .append("sg_prod_vfx__")
           .append("sg_sequence")
           .append("sg_shot_notifications")
           .append("project_names")
           .append("sg_status_list")
           .append("sg_turnover_")
           .append("sg_type")
           .append("sg_omit_")
           .append("sg_on_hold_")
           .append("sg_cbb_")
           .append("smart_cut_duration")
           .append("smart_cut_in")
           .append("smart_cut_out")
           .append("smart_cut_summary_display")
           .append("smart_duration_summary_display")
           .append("smart_head_duration")
           .append("smart_head_in")
           .append("smart_head_out")
           .append("smart_tail_duration")
           .append("smart_tail_in")
           .append("smart_tail_out")
           .append("smart_working_duration")
           .append("sg_tippett_working_length")
           .append("sg_actual_plate_resolution")
           .append("sg_storage___tier")
           .append("sg_storage___filesystem")
           .append("sg_storage___filesystem_used_percentage")
           .append("sg_storage___size_gb")
           .append("sg_slate_burnin_info")
           .append("sg_slate_header_info")
           .append("sg_pixel_aspect");
}

// *****************************************************************************
void Shot::sgSequence(const Dict &val)
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
    List elementLinkArray;

    for (size_t i = 0; i < val.size(); i++)
    {
        elementLinkArray.append(val[i].asLink());
    }

    setAttrValue("elements", toXmlrpcValue(elementLinkArray));
}

// *****************************************************************************
void Shot::sgElements(const List &val)
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

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::Shot &shot)
{
    return toStdString(shot.attrs());
}

// *****************************************************************************
std::string toStdString(const Shotgun::Shots &shots)
{
    Shotgun::List list;
    for (size_t i = 0; i < shots.size(); i++)
    {
        list.append(shots[i].attrs());
    }
    
    return toStdString(list);
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Shot &shot)
{
    output << toStdString(shot);
    return output;
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Shots &shots)
{
    output << toStdString(shots);
    return output;
}
