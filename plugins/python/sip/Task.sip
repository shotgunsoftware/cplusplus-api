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
class Task : Shotgun::Entity
{
%TypeHeaderCode
    #include <Shotgun/Task.h>
%End
 
protected:
    Task(Shotgun::Shotgun *sg, const xmlrpc_c::value &attrs);

public:
    Task();
    Task(const Shotgun::Task &ref);
    virtual ~Task();

    // Get an attribute's value
    const std::string sgName() const throw(Shotgun::SgAttrError);
    const std::string sgColor() const throw(Shotgun::SgAttrError);
    const std::string sgEndDate() const throw(Shotgun::SgAttrError);
    const int sgDuration() const throw(Shotgun::SgAttrError);
    const bool sgMilestone() const throw(Shotgun::SgAttrError);
    const std::string sgStartDate() const throw(Shotgun::SgAttrError);
    const std::string sgStatus() const throw(Shotgun::SgAttrError);
    const std::string sgType() const throw(Shotgun::SgAttrError);
    const int sgViewOrder() const throw(Shotgun::SgAttrError);
    const std::string sgDueDate() const throw(Shotgun::SgAttrError);

    // ------------------------------------------------------------------------
    // Add a /Factory/ annotation which specifies that the value returned by 
    // the function (which should be a wrapped C structure or C++ class instance) 
    // is a newly created instance and is owned by Python.
    // ------------------------------------------------------------------------
    Shotgun::Entity *sgLink() throw(Shotgun::SgAttrError, Shotgun::SgEntityError) /Factory/;
    const Shotgun::EntityPtrs sgAssignees() const throw(Shotgun::SgAttrError, Shotgun::SgEntityError) /Factory/;
    const std::string sgLinkEntityType() const throw(Shotgun::SgAttrError);

    // Set an attribute's value
    void sgStatus(const std::string &val) throw(Shotgun::SgAttrError);
    void sgViewOrder(const int val) throw(Shotgun::SgAttrError);
    void sgAssignees(const Shotgun::Strings &val) throw(Shotgun::SgAttrError);
};

}; // End namespace Shotgun - IMPORTANT: must have the semi-colon
