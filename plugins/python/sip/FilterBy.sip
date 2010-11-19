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

namespace SG {

// *****************************************************************************
class FilterBy
{
%TypeHeaderCode
    #include <Shotgun/FilterBy.h>
%End

public:
    FilterBy();

    // ===================================================================
    // These SIP functions that have %MethodCode directive are not defined 
    // in C++. They are actually calling the C++ template functions. 
    // ===================================================================

    // -------------------------------------------------------------------
    FilterBy(const std::string &path,
             const std::string &relation,
             const xmlrpc_c::value &value);
%MethodCode
    sipCpp = new SG::FilterBy(*a0, *a1, *a2);
%End

    // -------------------------------------------------------------------
    FilterBy(const std::string &path,
             const std::string &relation,
             const SG::Dict &value);
%MethodCode
    sipCpp = new SG::FilterBy(*a0, *a1, toXmlrpcValue(*a2));
%End

    // -------------------------------------------------------------------
    FilterBy(const std::string &path,
             const std::string &relation,
             const SG::List &value);
%MethodCode
    sipCpp = new SG::FilterBy(*a0, *a1, toXmlrpcValue(*a2));
%End

    // -------------------------------------------------------------------
    SG::FilterBy &And(const std::string &path,
                      const std::string &relation,
                      const xmlrpc_c::value &value);
%MethodCode
    sipRes = &sipCpp->And(*a0, *a1, *a2);
%End

    // -------------------------------------------------------------------
    SG::FilterBy &And(const std::string &path,
                      const std::string &relation,
                      const SG::Dict &value);
%MethodCode
    sipRes = &sipCpp->And(*a0, *a1, toXmlrpcValue(*a2));
%End

    // -------------------------------------------------------------------
    SG::FilterBy &And(const std::string &path,
                      const std::string &relation,
                      const SG::List &value);
%MethodCode
    sipRes = &sipCpp->And(*a0, *a1, toXmlrpcValue(*a2));
%End

    // -------------------------------------------------------------------
    SG::FilterBy &And(const SG::FilterBy &that);

    // -------------------------------------------------------------------
    SG::FilterBy &Or(const std::string &path,
                     const std::string &relation,
                     const xmlrpc_c::value &value);
%MethodCode
    sipRes = &sipCpp->Or(*a0, *a1, *a2);
%End

    // -------------------------------------------------------------------
    SG::FilterBy &Or(const std::string &path,
                     const std::string &relation,
                     const SG::Dict &value);
%MethodCode
    sipRes = &sipCpp->Or(*a0, *a1, toXmlrpcValue(*a2));
%End

    // -------------------------------------------------------------------
    SG::FilterBy &Or(const std::string &path,
                     const std::string &relation,
                     const SG::List &value);
%MethodCode
    sipRes = &sipCpp->Or(*a0, *a1, toXmlrpcValue(*a2));
%End

    // -------------------------------------------------------------------
    SG::FilterBy &Or(const SG::FilterBy &that);

    // -------------------------------------------------------------------
    const SG::Dict &filters() const;
    const bool empty() const;
    const int size() const;
    void clear();

    // ------------------------------------------------------------------------
    SIP_PYOBJECT __str__();
%MethodCode
    sipRes = PyString_FromString(sipCpp->str().c_str());
%End

    // ------------------------------------------------------------------------
    SIP_PYOBJECT __repr__();
%MethodCode
    sipRes = PyString_FromString(sipCpp->str().c_str());
%End

};

}; // End namespace SG
