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
class Method
{
%TypeHeaderCode
    #include <Shotgun/Method.h>
%End

protected:
    // (1) Even if this ctor is protected, it shoule be put here to prevent a 
    //     default public ctor being generated. See the complex example in the
    //     "SIP reference guide".
    //
    //         http://www.riverbankcomputing.co.uk/static/Docs/sip4/index.html
    //
    // (2) The Shotgun type needs its namespace attached.
    // (3) TODO: may need a /TransferThis/ annotation
    Method(Shotgun::Shotgun *sg, const std::string &methodName);
    virtual ~Method();

public:
    const std::string &methodName() const;
    Shotgun::MethodSignatures &signature() throw (Shotgun::SgEntityXmlrpcError); 
    std::string &help() throw (Shotgun::SgEntityXmlrpcError);
    xmlrpc_c::value call() throw (Shotgun::SgEntityXmlrpcError);
    xmlrpc_c::value call(const xmlrpc_c::paramList &params) throw (Shotgun::SgEntityXmlrpcError);
};

}; // End namespace Shotgun - IMPORTANT: has to have the semi-colon
