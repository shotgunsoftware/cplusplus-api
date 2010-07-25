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

#ifndef __PROJECT_H__
#define __PROJECT_H__

#include <Shotgun/Entity.h>


namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Project : public Entity
{
    friend class Shotgun;
    friend class Entity; // So that the base Entity class can call Project::find(..)
 
public:
    Project(const Project &ref);
    virtual ~Project();

    virtual const std::string sgName() const { return getAttrValueAsString("name"); }
    virtual const std::string sgCode() const { return getAttrValueAsString("code"); }

    // Overrides for base entity methods that don't work correctly 
    // for this entity type
    virtual const std::string sgProjectName() const { return sgName(); }
    virtual const std::string sgProjectCode() const { return sgCode(); }

    Project &operator=(const Project &that)
    {
        Entity::operator=(that);
        return *this;
    }

protected:
    Project(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Project create(Shotgun *sg, 
                       const std::string &projectName, 
                       const std::string &projectCode);
    static Projects find(Shotgun *sg, SgMap &findMap);


};

} // End namespace Shotgun

#endif    // End #ifdef __PROJECT_H__
