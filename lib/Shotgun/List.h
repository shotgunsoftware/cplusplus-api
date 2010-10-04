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

#ifndef __LIST_H__
#define __LIST_H__

#include <string>

#include <Shotgun/types.h>
#include <Shotgun/exceptions.h>

namespace Shotgun {

// *****************************************************************************
class List
{
public:
    List();
    List(const SgArray &array);

    template <typename T>
    List(const T &value)
    {
         append(value);      
    }

    template <typename T>
    List &append(const T &value)
    {
        m_value.push_back(toXmlrpcValue(value));

        return *this;
    }
    
    List &extend(const List &that);

    template <typename T>
    const T value(const int index) const;
    // This function should only be used within the Shotgun lib
    const xmlrpc_c::value value(const int index) const;
    
    template <typename T>
    const T operator[](const int index) const;
    // This function should only be used within the Shotgun lib
    const xmlrpc_c::value operator[](const int index) const;

    const SgArray &value() const { return m_value; }
    const bool empty() const { return m_value.empty(); }
    const int size() const { return m_value.size(); }
    void clear() { m_value.clear(); }
    void erase(const int index);
    void erase(const int first, const int last);

    List &operator=(const List &that)
    {
        if (this != &that)
        {
            m_value = that.m_value;
        }

        return *this;
    }

protected:
    SgArray m_value;
};

// *****************************************************************************
template <typename T>
const T List::value(const int index) const
{
    if (index >= 0 && index < m_value.size())
    {
        T outVal;
        fromXmlrpcValue(m_value[index], outVal);
        return outVal;
    }
    else
    {
        throw SgListError(index, 0, m_value.size());
    }
}

// *****************************************************************************
template <typename T>
const T List::operator[](const int index) const
{
    return value<T>(index);    
}

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::List &list);
std::ostream& operator<<(std::ostream &output, const Shotgun::List &list);

#endif    // End #ifdef __LIST_H__
