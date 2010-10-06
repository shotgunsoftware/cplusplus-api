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
class Shot : Shotgun::Entity, Shotgun::TaskMixin, Shotgun::NoteMixin
{
%TypeHeaderCode
    #include <Shotgun/Shot.h>
%End

public:
    Shot(const Shotgun::Shot &ref);
    virtual ~Shot();

    // Get an attribute's value
    const std::string sgName() const throw(Shotgun::SgError);
    const std::string sgDescription() const throw(Shotgun::SgError);
    const Shotgun::ElementPtrs sgElements() const throw(Shotgun::SgError) /Factory/;
    const Shotgun::Sequence *sgSequence() const throw(Shotgun::SgError) /Factory/;
    const std::string sgProject() const throw(Shotgun::SgError);
    const std::string sgStatus() const throw(Shotgun::SgError);
    const int sgCutDuration() const throw(Shotgun::SgError);
    const int sgCutIn() const throw(Shotgun::SgError);
    const int sgCutOut() const throw(Shotgun::SgError);
    const std::string sgCutSummary() const throw(Shotgun::SgError);
    const std::string sgDurationSummary() const throw(Shotgun::SgError);
    const int sgHeadDuration() const throw(Shotgun::SgError);
    const int sgHeadIn() const throw(Shotgun::SgError);
    const int sgHeadOut() const throw(Shotgun::SgError);
    const int sgTailDuration() const throw(Shotgun::SgError);
    const int sgTailIn() const throw(Shotgun::SgError);
    const int sgTailOut() const throw(Shotgun::SgError);
    const int sgWorkingDuration() const throw(Shotgun::SgError);

    // Set an attribute's value
    void sgSequence(const Shotgun::Dict &val) throw(Shotgun::SgError);
    void sgElements(const Shotgun::Elements &val) throw(Shotgun::SgError); 
    void sgElements(const Shotgun::List &val) throw(Shotgun::SgError); 

    static std::string type();

protected:
    Shot(Shotgun::Shotgun *sg, const xmlrpc_c::value &attrs);
};

}; // End namespace Shotgun
