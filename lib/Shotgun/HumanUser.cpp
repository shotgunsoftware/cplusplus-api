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

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/HumanUser.h>

namespace Shotgun {

// *****************************************************************************
HumanUser::HumanUser(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "HumanUser";
    m_attrs = new xmlrpc_c::value(attrs);
}


// *****************************************************************************
HumanUser::HumanUser(const HumanUser &ref)
    : Entity(ref.m_sg)
{
    m_type = "HumanUser";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
HumanUser::~HumanUser()
{
    // Nothing
}

// *****************************************************************************
List HumanUser::populateReturnFields()
{
    return List("id")
           .append("project")
           .append("created_at")
           .append("updated_at")
           .append("name")
           .append("admin")
           .append("sg_department")
           .append("email")
           .append("login")
           .append("sg_role")
           .append("permission_rule_set");
}

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::HumanUser &user)
{
    return toStdString(user.attrs());
}

// *****************************************************************************
std::string toStdString(const Shotgun::HumanUsers &users)
{
    Shotgun::List list;
    for (size_t i = 0; i < users.size(); i++)
    {
        list.append(users[i].attrs());
    }
    
    return toStdString(list);
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::HumanUser &user)
{
    output << toStdString(user);
    return output;
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::HumanUsers &users)
{
    output << toStdString(users);
    return output;
}
