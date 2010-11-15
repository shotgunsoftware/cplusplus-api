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
class Shotgun
{
%TypeHeaderCode
#include <Shotgun/Shotgun.h>
%End

public:
    Shotgun(const std::string &serverURL = SG_DEFAULT_URL,
            const std::string &authName = SG_AUTHENTICATION_NAME,
            const std::string &authKey = SG_AUTHENTICATION_KEY) throw(SG::SgError);
    virtual ~Shotgun();

    const std::string &serverURL() const;
    const std::string &authName() const;
    const std::string &authKey() const;
    const SG::Dict &authMap() const;

    SG::Method *method(const std::string &methodName);

    //------------------------------------------------------------------------
    SG::Entity *createEntity(const std::string &entityType,
                             const SG::Dict &data,
                             const SG::List &extraReturnFields = SG::List()) throw(SG::SgError) /Factory/;

    //------------------------------------------------------------------------
    SG::Entity *findEntity(const std::string &entityType,
                           const SG::FilterBy &filterList = SG::FilterBy(),
                           const SG::List &extraReturnFields = SG::List(),
                           const bool retiredOnly = false,
                           const SG::SortBy &order = SG::SortBy()) throw(SG::SgError) /Factory/;

    //------------------------------------------------------------------------
    SG::EntityPtrs findEntities(const std::string &entityType,
                                const SG::FilterBy &filterList = SG::FilterBy(),
                                const int limit = 0,
                                const SG::List &extraReturnFields = SG::List(),
                                const bool retiredOnly = false,
                                const SG::SortBy &order = SG::SortBy()) throw(SG::SgError) /Factory/;

    //------------------------------------------------------------------------
    bool deleteEntity(const std::string &entityType, const int id) const throw(SG::SgError);
};

}; // End namespace SG
