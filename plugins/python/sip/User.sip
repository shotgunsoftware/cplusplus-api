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
class User : Shotgun::Entity
{
%TypeHeaderCode
    #include <Shotgun/User.h>
%End

protected:
    User(Shotgun::Shotgun *sg, const xmlrpc_c::value &attrs);

public:
    User();
    User(const Shotgun::User &ref);
    virtual ~User();

    // --------------------------------------------------------------------------
    // NOTE: There are two ways of throwing the exceptions. Either one can be 
    //       used to acheive the same exception handling in Python.
    //
    // (1) throw(Shotgun::SgAttrNotFoundError, Shotgun::SgAttrTypeError, 
    //           Shotgun::SgAttrValueError, Shotgun::SgEmptyAttrMapError);
    //
    //    - More specific
    //    - More typing in .sip code
    //    - From Python side, can be used combined or separately
    //      e.g.
    //          except SgAttrValueError, err:  
    //      OR
    //          except (SgAttrNotFoundError, SgAttrTypeError, SgAttrValueError), err:
    //
    // (2) throw(Shotgun::SgAttrError);
    //
    //    - More generic to all attribute-related exceptions since it's the base
    //      class for each of the attribute-specific exceptions.
    //    - Less typing in .sip code
    //    - From Python side, can't be more specific. But it should be okay in
    //      this Shotgun case.
    //      e.g.
    //          except SgAttrError, err:
    //
    // We are using (2) in our .sip code.
    // --------------------------------------------------------------------------

    // Get an attribute's value
    const std::string sgName() const throw(Shotgun::SgAttrError);
    const bool sgCode() const throw(Shotgun::SgAttrError);
    const std::string sgDepartment() const throw(Shotgun::SgAttrError);
    const std::string sgEmail() const throw(Shotgun::SgAttrError);
    const std::string sgLogin() const throw(Shotgun::SgAttrError);
    const std::string sgRole() const throw(Shotgun::SgAttrError);
    const Shotgun::SgMap sgPermissionGroup() const throw(Shotgun::SgAttrError);

    // Set an attribute's value
    void sgName(const std::string &val) throw(Shotgun::SgAttrError);
    void sgDepartment(const std::string &val) throw(Shotgun::SgAttrError);
    void sgEmail(const std::string &val) throw(Shotgun::SgAttrError);
    void sgLogin(const std::string &val) throw(Shotgun::SgAttrError);
};

}; // End namespace Shotgun - IMPORTANT: has to have the semi-colon

