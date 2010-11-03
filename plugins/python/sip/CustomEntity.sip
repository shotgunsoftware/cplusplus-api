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
template <int>
class CustomEntity : SG::Entity
{
%TypeHeaderCode
    #include <Shotgun/CustomEntity.h>
%End
 
public:
    // This constructor is not necessary for Python. It would cause confusion
    // for the typedefs defined below.
    //CustomEntity(const SG::CustomEntity &ref);
    virtual ~CustomEntity();

    static std::string entityType();
    static std::string classType();

protected:
    CustomEntity(SG::Shotgun *sg, const xmlrpc_c::value &attrs);
};

// *****************************************************************************
// Can't specialize each typedef as:
//    typedef SG::CustomEntity<1> CustomEntity01;
//    typedef SG::CustomEntity<2> CustomEntity02;
//    ...
// But the following syntax works somehow.
// *****************************************************************************
typedef SG::CustomEntity<int> CustomEntity01;
typedef SG::CustomEntity<int> CustomEntity02;
typedef SG::CustomEntity<int> CustomEntity03;
typedef SG::CustomEntity<int> CustomEntity04;
typedef SG::CustomEntity<int> CustomEntity05;
typedef SG::CustomEntity<int> CustomEntity06;
typedef SG::CustomEntity<int> CustomEntity07;
typedef SG::CustomEntity<int> CustomEntity08;
typedef SG::CustomEntity<int> CustomEntity09;
typedef SG::CustomEntity<int> CustomEntity10;
typedef SG::CustomEntity<int> CustomEntity11;
typedef SG::CustomEntity<int> CustomEntity12;
typedef SG::CustomEntity<int> CustomEntity13;
typedef SG::CustomEntity<int> CustomEntity14;
typedef SG::CustomEntity<int> CustomEntity15;
typedef SG::CustomEntity<int> CustomEntity16;
typedef SG::CustomEntity<int> CustomEntity17;
typedef SG::CustomEntity<int> CustomEntity18;
typedef SG::CustomEntity<int> CustomEntity19;
typedef SG::CustomEntity<int> CustomEntity20;

// *****************************************************************************
typedef std::vector<SG::CustomEntity01 *> CustomEntity01Ptrs;
typedef std::vector<SG::CustomEntity02 *> CustomEntity02Ptrs;
typedef std::vector<SG::CustomEntity03 *> CustomEntity03Ptrs;
typedef std::vector<SG::CustomEntity04 *> CustomEntity04Ptrs;
typedef std::vector<SG::CustomEntity05 *> CustomEntity05Ptrs;
typedef std::vector<SG::CustomEntity06 *> CustomEntity06Ptrs;
typedef std::vector<SG::CustomEntity07 *> CustomEntity07Ptrs;
typedef std::vector<SG::CustomEntity08 *> CustomEntity08Ptrs;
typedef std::vector<SG::CustomEntity09 *> CustomEntity09Ptrs;
typedef std::vector<SG::CustomEntity10 *> CustomEntity10Ptrs;
typedef std::vector<SG::CustomEntity11 *> CustomEntity11Ptrs;
typedef std::vector<SG::CustomEntity12 *> CustomEntity12Ptrs;
typedef std::vector<SG::CustomEntity13 *> CustomEntity13Ptrs;
typedef std::vector<SG::CustomEntity14 *> CustomEntity14Ptrs;
typedef std::vector<SG::CustomEntity15 *> CustomEntity15Ptrs;
typedef std::vector<SG::CustomEntity16 *> CustomEntity16Ptrs;
typedef std::vector<SG::CustomEntity17 *> CustomEntity17Ptrs;
typedef std::vector<SG::CustomEntity18 *> CustomEntity18Ptrs;
typedef std::vector<SG::CustomEntity19 *> CustomEntity19Ptrs;
typedef std::vector<SG::CustomEntity20 *> CustomEntity20Ptrs;

}; // End namespace SG

