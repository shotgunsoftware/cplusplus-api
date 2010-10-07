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

#ifndef __USER_H__
#define __USER_H__

#include <Shotgun/Entity.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class HumanUser : public Entity
{
    friend class Shotgun;
    friend class Task;
 
public:
    HumanUser(const HumanUser &ref);
    virtual ~HumanUser();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("name"); }
    const std::string sgEmail() const { return getAttrValueAsString("email"); }
    const std::string sgLogin() const { return getAttrValueAsString("login"); }
    const Dict sgPermissionGroup() const { return getAttrValueAsDict("permission_rule_set"); }

    // Set an attribute's value
    void sgName(const std::string &val);
    void sgEmail(const std::string &val);
    void sgLogin(const std::string &val);

    static std::string type() { return std::string("HumanUser"); }

    HumanUser &operator=(const HumanUser &that)
    {
        Entity::operator=(that);
        return *this;
    }

protected:
    HumanUser(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Entity *factory(Shotgun *sg, const xmlrpc_c::value &attrs) { return new HumanUser(sg, attrs); }
    static List populateReturnFields();
};

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::HumanUser &user);
std::string toStdString(const Shotgun::HumanUsers &users);
std::ostream& operator<<(std::ostream &output, const Shotgun::HumanUser &user);
std::ostream& operator<<(std::ostream &output, const Shotgun::HumanUsers &users);

#endif    // End #ifdef __USER_H__
