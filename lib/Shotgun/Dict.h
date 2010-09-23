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
    Dict &add(const std::string &key, const T &value);

    // Return the value of a given key
    template <typename  T>
    const T value(const std::string &key) const;

    // --------------------------------------------------------------------
    // The [] operator that returns the value of a given key. The syntax of
    // using this operator is kind of complex, which makes it not worth to
    // use it. For example,
    //     std::string nameStr = dict.operator[]<std::string>("name");
    //                  int id = dict.operator[]<int>("id");
    // Instead use template function, value(key).
    // --------------------------------------------------------------------
    template <typename  T>
    const T operator[](const std::string &key) const;

    const SgMap &value() const { return m_value; }
    const bool empty() const { return m_value.empty(); }
    const int size() const { return m_value.size(); }
    const bool find(const std::string &key);
    Dict &remove(const std::string &key);

    Dict &operator=(const Dict &that)
    {
        if (this != &that)
        {
            m_value = that.m_value;
        }

        return *this;
    }

protected:
    SgMap m_value;
};

// *****************************************************************************
template <typename T>
Dict &Dict::add(const std::string &key, const T &value)
{
    // Remove the (key, value) pair first if the key is found since 
    // xmlrpc_c::value type can't be reassigned once it's instantiated.
    remove(key);
    m_value[key] = toXmlrpcValue(value);

    return *this;
}

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

    T outVal;
    fromXmlrpcValue(value, outVal);
    return outVal;

#if 0
    // The template function doesn't work since xmlrpc_c::value has to be casted to a
    // specific derived xmlrpc_c::value type first, which the compiler doesn't like.
    return fromXmlrpcValue<T>(value);
#endif
}

// *****************************************************************************
template <typename  T>
const T Dict::operator[](const std::string &key) const
{
    return value<T>(key);
}

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::Dict &dict);
std::ostream& operator<<(std::ostream &output, const Shotgun::Dict &dict);

#endif    // End #ifdef __DICT_H__
