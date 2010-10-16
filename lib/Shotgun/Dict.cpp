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

#include <Shotgun/Dict.h>

namespace Shotgun {

// *****************************************************************************
Dict::Dict() : m_value(SgMap())
{
}

// *****************************************************************************
Dict::Dict(const Dict &ref) : m_value(ref.m_value)
{
}

// *****************************************************************************
Dict::Dict(const SgMap &map) : m_value(map)
{
}

// *****************************************************************************
Dict::Dict(const xmlrpc_c::value &value)
{
    if (value.type() == xmlrpc_c::value::TYPE_STRUCT)
    {
        m_value = SgMap(xmlrpc_c::value_struct(value));
    }
    else
    {
        throw SgDictConversionError(value);
    }
}

// *****************************************************************************
const xmlrpc_c::value Dict::value(const std::string &key) const
{
    SgMap::const_iterator foundIter = m_value.find(key);
    if (foundIter != m_value.end())
    {
        return (*foundIter).second;
    }
    else
    {
        throw SgDictKeyNotFoundError(key);
    }
}

// *****************************************************************************
const xmlrpc_c::value Dict::operator[](const std::string &key) const
{
    return value(key);
}
 
// *****************************************************************************
const bool Dict::find(const std::string &key) const
{
    SgMap::const_iterator foundIter = m_value.find(key);
    if (foundIter != m_value.end())
    {
        return true;
    }

    return false;
}

// *****************************************************************************
Dict &Dict::erase(const std::string &key)
{
    m_value.erase(key);

    return *this;
}

} // End namespace Shotgun
