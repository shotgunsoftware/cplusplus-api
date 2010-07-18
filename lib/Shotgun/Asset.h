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
                        const std::string &projectCode,
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
