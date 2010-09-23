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

#ifndef __DICT_H__
#define __DICT_H__

#include <string>

#include <Shotgun/Type.h>

namespace Shotgun {

// *****************************************************************************
class Dict
{
public:
    Dict();
    Dict(const SgMap &map);

    template <typename T>
    Dict(const std::string &key, const T &value)
    {
         add(key, value);      
    }

    template <typename T>
    Dict &add(const std::string &key, const T &value)
    {
        // Remove the (key, value) pair first if the key is found since 
        // xmlrpc_c::value type can't be reassigned once it's instantiated.
        remove(key);
        m_value[key] = toXmlrpcValue(value);

        return *this;
    }

    const SgMap &value() const { return m_value; }
    const bool empty() const { return m_value.empty(); }
    const int size() const { return m_value.size(); }
    const bool find(const std::string &key);
    Dict &remove(const std::string &key);

    template <typename  T>
    const T value(const std::string &key) const;

    template <typename  T>
    const T operator[](const std::string &key) const;

    Dict &operator=(const Dict &that)
    {
        if (this != &that)
        {
            m_value = that.m_value;
        }

        return *this;
    }

    friend std::ostream& operator<<(std::ostream &output, const Dict &dict);

protected:
    template <typename T>
    const T fromXmlrpcValue(const xmlrpc_c::value &value) const;

    SgMap m_value;
};

// *****************************************************************************
template <typename  T>
const T Dict::value(const std::string &key) const
{
    xmlrpc_c::value value;

    SgMap::const_iterator foundIter = m_value.find(key);
    if (foundIter != m_value.end())
    {
        value = (*foundIter).second;
    }
    else
    {
        value = xmlrpc_c::value_nil();           
    }

    return fromXmlrpcValue<T>(value);
}

// *****************************************************************************
template <typename  T>
const T Dict::operator[](const std::string &key) const
{
    return value<T>(key);
}

// *****************************************************************************
template <typename T>
const T Dict::fromXmlrpcValue(const xmlrpc_c::value &value) const
{
    std::cout << xmlrpcValueTypeStr(value.type()) << std::endl;

#if 0
    if (value.type() == xmlrpc_c::value::TYPE_INT)
    {
        return T(xmlrpc_c::value_int(value));
    }
    else if (value.type() == xmlrpc_c::value::TYPE_BOOLEAN)
    {
        return T(xmlrpc_c::value_boolean(value));
    }
    else if (value.type() == xmlrpc_c::value::TYPE_DOUBLE)
    {
        return T(xmlrpc_c::value_double(value));
    }
    else if (value.type() == xmlrpc_c::value::TYPE_DATETIME)
    {
        return T(xmlrpc_c::value_datetime(value));
    }
    else if (value.type() == xmlrpc_c::value::TYPE_STRING)
    {
        return T(xmlrpc_c::value_string(value));
    }
    else if (value.type() == xmlrpc_c::value::TYPE_BYTESTRING)
    {
        return T((xmlrpc_c::value_bytestring(value)).length());
    }
    else if (value.type() == xmlrpc_c::value::TYPE_ARRAY)
    {
        return T((xmlrpc_c::value_array(value)).vectorValueValue());
    }
    else if (value.type() == xmlrpc_c::value::TYPE_STRUCT)
    {
        return T(SgMap(xmlrpc_c::value_struct(value)));
    }
    else if (value.type() == xmlrpc_c::value::TYPE_NIL)
    {
        // TODO: ???
        return T("nil");
    }
#endif

    return std::string("whatever");
}

} // End namespace Shotgun

#endif    // End #ifdef __DICT_H__
