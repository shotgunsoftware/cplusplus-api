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

namespace SG {

// *****************************************************************************
/// \class List
/// A List class is basically a wrapper around a std::vector<xmlrpc_c::value> 
/// container. 
class List
{
public:
    /// A default constructor.
    List();

    /// A copy constructor.
    List(const List &ref);

    /// A constructor that takes a std::vector<xmlrpc_c::value>.
    List(const std::vector<xmlrpc_c::value> &array);

    /// A template construtor that adds an element to the std::vector container.
    template <typename T>
    List(const T &value)
    {
         append(value);      
    }

    /// A template function that adds an element to the std::vector container.
    template <typename T>
    List &append(const T &value)
    {
        m_value.push_back(toXmlrpcValue(value));

        return *this;
    }
    
    /// Extends the std::vector container with the given List.
    List &extend(const List &that);

    /// A template function that returns the value of an element with the
    /// given index. 
    template <typename T>
    const T value(const int index) const;

    /// Returns the value of an element with the given index. This function 
    /// should only be used within the Shotgun lib
    const xmlrpc_c::value value(const int index) const;
    
    /// Returns the value of an element with the given index. The value is of
    /// type, xmlrpc_c::value. This function should only be used within the 
    /// Shotgun lib.
    const xmlrpc_c::value operator[](const int index) const;

    /// Returns the std::vector container that the List class wraps around.
    const std::vector<xmlrpc_c::value> &value() const { return m_value; }

    /// Returns whether the std::vector container is empty.
    const bool empty() const { return m_value.empty(); }

    /// Returns the size of the std::vector container.
    const int size() const { return m_value.size(); }

    /// Returns the string representation of the List class. 
    const std::string str() const { return toStdString(m_value); }

    /// Removes all the contents from the std::vector container, leaving it with 
    /// a size of 0.
    void clear() { m_value.clear(); }

    /// Removes a single element with the given index from the std::vector container.
    void erase(const int index);

    /// Removes a range of elements with the given indices from the std::vector container.
    void erase(const int first, const int last);

    List &operator=(const List &that)
    {
        if (this != &that)
        {
            m_value = that.m_value;
        }

        return *this;
    }

    friend std::ostream& operator<<(std::ostream &output, const List &list)
    {
        output << list.str();
        return output;
    }

protected:
    std::vector<xmlrpc_c::value> m_value; ///< The std::vector container.
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
        throw SgListIndexOutOfRangeError(index, 0, m_value.size());
    }
}

} // End namespace SG

#endif    // End #ifdef __LIST_H__
