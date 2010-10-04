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

namespace Shotgun {

// *****************************************************************************
class Project : Shotgun::Entity
{
%TypeHeaderCode
    #include <Shotgun/Project.h>
%End
 
public:
    Project(const Shotgun::Project &ref);
    virtual ~Project();

    virtual const std::string sgName() const throw(Shotgun::SgError);
    virtual const std::string sgCode() const throw(Shotgun::SgError);

    // Overrides for base entity methods that don't work correctly 
    // for this entity type
    virtual const std::string sgProjectName() const throw(Shotgun::SgError);
    virtual const std::string sgProjectCode() const throw(Shotgun::SgError);

    static std::string type();

    // ===================================================================
    // This dynamicCast SIP function that has %MethodCode directive is not 
    // defined in C++. It should only provide the type of the input argument,
    // but not its name in the header.
    // ===================================================================

    // This function should not have the /Factory/ annotation.
    static Shotgun::Project *dynamicCast(Shotgun::Entity *) throw(Shotgun::SgError);
%MethodCode
    if (Shotgun::Project *p = dynamic_cast<Shotgun::Project *>(a0))
    {
        sipRes = p;
    }
    else
    {
        throw Shotgun::SgEntityDynamicCastError("Project");
    }
%End

protected:
    Project(Shotgun::Shotgun *sg, const xmlrpc_c::value &attrs);
};

}; // End namespace Shotgun
