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

#ifndef __SORTBY_H__
#define __SORTBY_H__

#include <string>

#include <Shotgun/types.h>
#include <Shotgun/List.h>
#include <Shotgun/Dict.h>

namespace Shotgun {

// *****************************************************************************
class SortBy
{
public:
    SortBy();
    SortBy(const List &sorts);

    SortBy(const std::string &fieldName,
           const std::string &direction = "asc")
    {
         then(fieldName, direction);      
    }

    const List &sorts() const { return m_sorts; }
    const bool empty() const { return m_sorts.empty(); }
    const int size() const { return m_sorts.size(); }
    void clear() { m_sorts.clear(); }

    SortBy &operator=(const SortBy &that)
    {
        if (this != &that)
        {
            m_sorts = that.m_sorts;
        }

        return *this;
    }

    SortBy &then(const std::string &fieldName,
                 const std::string &direction = "asc");
    SortBy &then(const SortBy &that);

protected:
    List m_sorts;
};

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::SortBy &order);
std::ostream& operator<<(std::ostream &output, const Shotgun::SortBy &order);

#endif    // End #ifdef __SORTBY_H__
