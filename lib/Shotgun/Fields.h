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

#ifndef __SG_FIELDS_H__
#define __SG_FIELDS_H__

#include <string>

#include <Shotgun/types.h>
#include <Shotgun/List.h>
#include <Shotgun/Dict.h>

namespace SG {

// *****************************************************************************
/*!
 \class Fields
 A Fields class is a specialized "fields" List. "fields" is specified as a
 list of fields to update for a Shotgun entity.

 \htmlonly
 <pre>
 <br>
 'fields': [                                                     # REQUIRED: Array of fields to update <br>
     { <br>
         'field_name': string,                                   # REQUIRED: Field name <br>
         'value': field_value,                                   # REQUIRED: Field value <br>
         'multi_entity_update_mode': 'set' | 'add' | 'remove',   # OPTIONAL: Update mode for multi-valued <br>
                                                                 # data types (e.g. multi_entity) <br>
         'parent_entity': {'type': string, 'id': int}            # OPTIONAL: For update on fields with an <br>
                                                                 # associated parent entity, you specify the <br>
                                                                 # parent entity here <br>
     }, <br>
     ... <br>
 ]
 </pre>
 \endhtmlonly
*/
class Fields : public List
{
public:
    // -------------------------------------------------------------------------
    /// A default constructor.
    Fields();

    /// A copy constructor.
    Fields(const Fields &ref);

    /// A constructor that takes a std::vector<xmlrpc_c::value>.
    Fields(const std::vector<xmlrpc_c::value> &fields);

    /// A template constructor that adds one field to the "fields" list.
    template <typename T>
    Fields(const std::string &fieldName,
           const T &fieldValue,
           const std::string &multiEntityUpdateMode = "",
           const Dict &parentEntity = Dict());

    // -------------------------------------------------------------------------
    /// A template function that adds one field to the "fields" list.
    template <typename T>
    Fields &append(const std::string &fieldName,
                   const T &fieldValue,
                   const std::string &multiEntityUpdateMode = "",
                   const Dict &parentEntity = Dict());

    // -------------------------------------------------------------------------
    /// Extends the "fields" list with a second "fields" list.
    Fields &extend(const Fields &that);

    // -------------------------------------------------------------------------
    /// Returns the std::vector container for the "fields" list.
    const std::vector<xmlrpc_c::value> &fields() const { return value(); }

    // -------------------------------------------------------------------------
    Fields &operator=(const Fields &that)
    {
        if (this != &that)
        {
            List::operator=(that) ;
        }

        return *this;
    }

    // -------------------------------------------------------------------------
    friend std::ostream& operator<<(std::ostream &output, const Fields &fields)
    {
        output << fields.str();
        return output;
    }
};

// *****************************************************************************
template <typename T>
Fields::Fields(const std::string &fieldName,
               const T &fieldValue,
               const std::string &multiEntityUpdateMode,
               const Dict &parentEntity)
{
     append(fieldName, fieldValue, multiEntityUpdateMode, parentEntity);      
}

// *****************************************************************************
template <typename T>
Fields &Fields::append(const std::string &fieldName,
                       const T &fieldValue,
                       const std::string &multiEntityUpdateMode,
                       const Dict &parentEntity)
{
    Dict field = Dict("field_name", fieldName)
                 .add("value", fieldValue);

    if (multiEntityUpdateMode != "")
    {
        field.add("multi_entity_update_mode", multiEntityUpdateMode);
    }

    if (!parentEntity.empty())
    {
        field.add("parent_entity", parentEntity);
    }

    m_value.push_back(toXmlrpcValue(field));

    return *this;
}

} // End namespace SG

#endif    // End #ifdef __SG_FIELDS_H__
