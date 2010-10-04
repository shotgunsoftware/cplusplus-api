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
class Note : Shotgun::Entity
{
%TypeHeaderCode
    #include <Shotgun/Note.h>
%End

public:
    Note(const Shotgun::Note &ref);
    virtual ~Note();

    // Get an attribute's value
    const std::string sgAuthor() const throw(Shotgun::SgError);
    const std::string sgBody() const throw(Shotgun::SgError);
    const std::string sgStatus() const throw(Shotgun::SgError);
    const std::string sgSubject() const throw(Shotgun::SgError);
    const std::string sgType() const throw(Shotgun::SgError);
    Shotgun::Review *getLinkedReview() throw(Shotgun::SgError) /Factory/;
    Shotgun::Shot *getLinkedShot() throw(Shotgun::SgError) /Factory/;
    Shotgun::Version *getLinkedVersion() throw(Shotgun::SgError) /Factory/;

    // Both sgCc() and sgTo() could be a mixed list of HumanUser and Group entities.
    // sgLinks() is a list of mixed types of entities. If we want to these 
    // functions to return a list of entities instead of a list of mini maps, 
    // check function, sgAssignees() in "Task.h".
    const Shotgun::List sgCc() const throw(Shotgun::SgError);
    const Shotgun::List sgTo() const throw(Shotgun::SgError);
    const Shotgun::List sgLinks() const throw(Shotgun::SgError);

    static std::string type();

    // ===================================================================
    // This dynamicCast SIP function that has %MethodCode directive is not
    // defined in C++. It should only provide the type of the input argument,
    // but not its name in the header.
    // ===================================================================

    // This function should not have the /Factory/ annotation.
    static Shotgun::Note *dynamicCast(Shotgun::Entity *) throw(Shotgun::SgError);
%MethodCode
    if (Shotgun::Note *p = dynamic_cast<Shotgun::Note *>(a0))
    {
        sipRes = p;
    }
    else
    {
        throw Shotgun::SgEntityDynamicCastError("Note");
    }
%End

protected:
    Note(Shotgun::Shotgun *sg, const xmlrpc_c::value &attrs);
};

}; // End namespace Shotgun
