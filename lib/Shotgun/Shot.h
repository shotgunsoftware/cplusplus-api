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
#include <Shotgun/Version.h>
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
    friend class Version;
    friend class Element;
    friend class ReviewItem;
    friend class Reference;
    friend class Note;
    friend class Asset;
    friend class Entity;
 
public:
    Shot(const Shot &ref);
    virtual ~Shot();

    // Set an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); }
    const std::string sgDescription() const { return getAttrValueAsString("description"); } 
    const Elements sgElements() const;
    const Sequence sgSequence() const { return Sequence(m_sg, getAttrValueAsEntityAttrMap("sg_sequence")); } 
    const std::string sgProject() const { return sgProjectName(); }
    const std::string sgStatus() const { return getAttrValueAsString("sg_status_list"); } 
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

    // Set an attribute's value
    void sgSequence(const SgMap &val);
    void sgElements(const Elements &val); // An array of Element entities
    void sgElements(const SgArray &val); // An array of entity links

    Shot &operator=(const Shot &that)
    {
        Entity::operator=(that);
        return *this;
    }

protected:
    Shot(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Shot create(Shotgun *sg, 
                       const std::string &projectName,
                       const std::string &shotName,
                       const std::string &sequenceName="");
    static Shots find(Shotgun *sg, SgMap &findMap);
};

} // End namespace Shotgun

#endif    // End #ifdef __SHOT_H__
