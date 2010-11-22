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
class List
{
%TypeHeaderCode
    #include <Shotgun/List.h>
%End

public:
    List();

    // ===================================================================
    // These SIP functions that have %MethodCode directive are not defined
    // in C++. They are actually calling the C++ template functions. 
    // ===================================================================

    // -------------------------------------------------------------------
    List(const xmlrpc_c::value &value);
%MethodCode
    sipCpp = new SG::List(*a0);
%End

    // -------------------------------------------------------------------
    SG::List &append(const xmlrpc_c::value &value);
%MethodCode
    sipRes = &sipCpp->append(*a0);
%End
   
    // -------------------------------------------------------------------
    SG::List &extend(const SG::List &that);

    // -------------------------------------------------------------------
    const xmlrpc_c::value value(const int index) const;
    const xmlrpc_c::value operator[](const int index) const;

    // -------------------------------------------------------------------
    const std::vector<xmlrpc_c::value> &value() const;
    const bool empty() const;
    const int size() const;
    void clear();
    void erase(const int index);
    void erase(const int first, const int last);

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

