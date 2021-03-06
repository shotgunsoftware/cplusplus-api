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

#ifndef __SG_DICT_H__
#define __SG_DICT_H__

#include <string>

#include <Shotgun/types.h>
#include <Shotgun/exceptions.h>

namespace SG {

// *****************************************************************************
/// \class Dict
/// A Dict class is basically a wrapper around a std::map<std::string, xmlrpc_c::value> 
/// container. 
class Dict
{
public:
    // -------------------------------------------------------------------------
    /// A default constructor.
    Dict();

    /// A copy constructor.
    Dict(const Dict &ref);

    /// A constructor that takes a std::map.
    Dict(const std::map<std::string, xmlrpc_c::value> &map);

    /// A constructor that should only be used within the Shotgun lib.
    /// It checks whether the input is a xmlrpc_c::value::TYPE_STRUCT type.
    /// If so, it converts the input to the std::map container. Otherwise, it 
    /// throws an exception.
    Dict(const xmlrpc_c::value &value);

    /// A template constructor that takes a (key, value) pair, and add
    /// that pair to the std::map container.
    template <typename T>
    Dict(const std::string &key, const T &value);

    // -------------------------------------------------------------------------
    /// A template function that adds a (key, value) pair to the std::map container.
    template <typename T>
    Dict &add(const std::string &key, const T &value);

    // -------------------------------------------------------------------------
    /// A template function that returns the value of a given key. 
    template <typename  T>
    const T value(const std::string &key) const;

    // -------------------------------------------------------------------------
    /// Returns the value of a given key. The return value is of type, 
    /// xmlrpc_c::value. It should only be called within the Shotgun lib.
    const xmlrpc_c::value value(const std::string &key) const;

    // -------------------------------------------------------------------------
    /// This [] operator that returns the value of a given key. The return 
    /// value is of type, xmlrpc_c::value. It should only be called within 
    /// the Shotgun lib.
    const xmlrpc_c::value operator[](const std::string &key) const;

    // -------------------------------------------------------------------------
    /// Returns the std::map container that the Dict class wraps around.
    const std::map<std::string, xmlrpc_c::value> &value() const { return m_value; }

    // -------------------------------------------------------------------------
    /// Returns whether the std::map container is empty.
    const bool empty() const { return m_value.empty(); }

    // -------------------------------------------------------------------------
    /// Returns the size of the std::map container.
    const int size() const { return m_value.size(); }

    // -------------------------------------------------------------------------
    /// Returns the string representation of the Dict class.
    const std::string str() const { return toStdString(m_value); }

    // -------------------------------------------------------------------------
    /// Returns whether a given key exists.
    const bool find(const std::string &key) const;

    // -------------------------------------------------------------------------
    /// Removes all the contents from the std::map container, leaving it with a size of 0.
    void clear() { m_value.clear(); }

    // -------------------------------------------------------------------------
    /// Removes a single element with the given key from the std::map container.
    Dict &erase(const std::string &key);

    // -------------------------------------------------------------------------
    Dict &operator=(const Dict &that)
    {
        if (this != &that)
        {
            m_value = that.m_value;
        }

        return *this;
    }

    // -------------------------------------------------------------------------
    friend std::ostream& operator<<(std::ostream &output, const Dict &dict)
    {
        output << dict.str();
        return output;
    }

protected:
    std::map<std::string, xmlrpc_c::value> m_value; ///< The std::map container.
};

// *****************************************************************************
template <typename T>
Dict::Dict(const std::string &key, const T &value)
{
     add<T>(key, value);      
}

// *****************************************************************************
template <typename T>
Dict &Dict::add(const std::string &key, const T &value)
{
    // Remove the (key, value) pair first if the key is found since 
    // xmlrpc_c::value type can't be reassigned once it's instantiated.
    erase(key);
    m_value[key] = toXmlrpcValue(value);

    return *this;
}

// *****************************************************************************
template <typename  T>
const T Dict::value(const std::string &key) const
{
    std::map<std::string, xmlrpc_c::value>::const_iterator foundIter = m_value.find(key);
    if (foundIter != m_value.end())
    {
        T outVal;
        fromXmlrpcValue((*foundIter).second, outVal);
        return outVal;

#if 0
        // The template function doesn't work since xmlrpc_c::value has to be casted to a
        // specific derived xmlrpc_c::value type first, which the compiler doesn't like.
        return fromXmlrpcValue<T>(value);
#endif
    }
    else
    {
        throw SgDictKeyNotFoundError(key);           
    }
}

} // End namespace SG

#endif    // End #ifdef __SG_DICT_H__
