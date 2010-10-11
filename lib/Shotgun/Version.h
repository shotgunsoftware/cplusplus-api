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

#ifndef __VERSION_H__
#define __VERSION_H__

#include <string>

#include <Shotgun/Entity.h>
#include <Shotgun/NoteMixin.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Version : public Entity, public NoteMixin
{
    friend class Shotgun;
    
public:
    Version(const Version &ref);
    virtual ~Version();

    static std::string type() { return std::string("Version"); }

    // -------------------------------------------------------------------------
    Version &operator=(const Version &that)
    {
        if (this != &that)
        {
            Entity::operator=(that);
        }

        return *this;
    }

    // -------------------------------------------------------------------------
    friend std::ostream& operator<<(std::ostream &output, const Version &version)
    {
        output << version.str();
        return output;
    }

protected:
    Version(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Entity *factory(Shotgun *sg, const xmlrpc_c::value &attrs) { return new Version(sg, attrs); }
    static List defaultReturnFields();
};

// *****************************************************************************
typedef std::vector<Version *> VersionPtrs;

} // End namespace Shotgun

#endif    // End #ifdef __VERSION_H__
