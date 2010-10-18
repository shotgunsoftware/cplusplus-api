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

#include <Shotgun/List.h>

namespace SG {

// *****************************************************************************
List::List() : m_value(std::vector<xmlrpc_c::value>())
{
}

// *****************************************************************************
List::List(const List &ref) : m_value(ref.m_value)
{
}

// *****************************************************************************
List::List(const std::vector<xmlrpc_c::value> &array) : m_value(array)
{
}

// *****************************************************************************
List &List::extend(const List &that)
{
    m_value.insert(m_value.end(), that.m_value.begin(), that.m_value.end());

    return *this;
}

// *****************************************************************************
const xmlrpc_c::value List::value(const int index) const
{
    if (index >= 0 && index < m_value.size())
    {
        return m_value[index];
    }
    else
    {
        throw SgListIndexOutOfRangeError(index, 0, m_value.size());
    }
}

// *****************************************************************************
const xmlrpc_c::value List::operator[](const int index) const
{
    return value(index);
}

// *****************************************************************************
void List::erase(const int index)
{
    m_value.erase(m_value.begin() + index);
}

// *****************************************************************************
void List::erase(const int first, const int last)
{
    m_value.erase(m_value.begin() + first, m_value.begin() + last);
}

} // End namespace SG
