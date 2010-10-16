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
/*!
 \class SortBy
 A SortBy class is a wrapper around a "sorts" List. It contains a list of 
 result sort orders ("sorts") when searching a Shotgun entity. Each element
 of the list constains a field name and its corrresponding sort order. 
 The "sorts" list looks like this:
 
 \htmlonly
 <pre>
 <br>
 'sorts': [                                                         # OPTIONAL: Array of result sort orders <br>
             {'field_name': string, 'direction': 'asc' | 'desc'},   # REQUIRED: Field name and sort order <br>
                                                                    # (ascending or descending).  The default <br>
                                                                    # sort order is {'field_name': 'id', 'direction': 'asc'}
             ...                                                    <br>
          ],
 </pre>
 \endhtmlonly
*/

class SortBy
{
public:
    /// A Default constructor.
    SortBy();

    /// A copy constructor.
    SortBy(const SortBy &ref);

    /// A constructor that takes a sorts List.
    SortBy(const List &sorts);

    /// A constructor that adds one field and its sort order to the "sorts" list.
    SortBy(const std::string &fieldName,
           const std::string &direction = "asc")
    {
         then(fieldName, direction);      
    }

    /// Adds one field and its sort order to the "sorts" list. 
    SortBy &then(const std::string &fieldName,
                 const std::string &direction = "asc");

    /// Extends the "sorts" list with another "sorts" list.
    SortBy &then(const SortBy &that);

    /// Returns the "sorts" list.
    const List &sorts() const { return m_sorts; }

    /// Returns whether the "sorts" list is empty.
    const bool empty() const { return m_sorts.empty(); }

    /// Returns the size of the "sorts" list.
    const int size() const { return m_sorts.size(); }

    /// Returns the string representation of the SortBy class.
    const std::string str() const { return m_sorts.str(); }

    /// Removes all the contents from the "sorts" list.
    void clear() { m_sorts.clear(); }

    SortBy &operator=(const SortBy &that)
    {
        if (this != &that)
        {
            m_sorts = that.m_sorts;
        }

        return *this;
    }

    friend std::ostream& operator<<(std::ostream &output, const SortBy &sortBy)
    {
        output << sortBy.str();
        return output;
    }

protected:
    List m_sorts; ///< The "sorts" list.
};

} // End namespace Shotgun

#endif    // End #ifdef __SORTBY_H__
