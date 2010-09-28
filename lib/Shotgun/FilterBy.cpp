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

#include <Shotgun/FilterBy.h>

namespace Shotgun {

// *****************************************************************************
FilterBy::FilterBy() : m_filters(Dict())
{
}

// *****************************************************************************
FilterBy::FilterBy(const Dict &filters) : m_filters(filters)
{
}

// *****************************************************************************
FilterBy &FilterBy::op(const std::string &logicOperator,
                       const std::string &path,
                       const std::string &relation,
                       const xmlrpc_c::value &value)
{
    // -------------------------------------------------------------------
    // The new simple condition
    Dict newCondition = Dict("path", path)
                        .add("relation", relation);

    // The value has to be converted to an array
    List valueList;
    if (value.type() == xmlrpc_c::value::TYPE_ARRAY)
    {
        fromXmlrpcValue(value, valueList);
    }
    else
    {
        valueList.append(value);
    }
    newCondition.add("values", valueList);
 
    // -------------------------------------------------------------------
    // Add the new simple condition to the conditions list
    List conditions;
    if (!m_filters.empty()) 
    {
        // The Original m_filters map now becomes a condition
        conditions.append(m_filters);
    }
    conditions.append(newCondition);

    // -------------------------------------------------------------------
    // Update the filters
    m_filters.clear();
    m_filters.add("logical_operator", logicOperator)
             .add("conditions", conditions);

    return *this;
}

// *****************************************************************************
FilterBy &FilterBy::op(const std::string &logicOperator,
                       const FilterBy &that)
{
    List conditions;
    conditions.append(m_filters);
    conditions.append(that.m_filters);

    // -------------------------------------------------------------------
    // Update the filters
    m_filters.clear();
    m_filters.add("logical_operator", logicOperator)
             .add("conditions", conditions);

    return *this;
}

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::FilterBy &filterList)
{
    return toStdString(filterList.filters());
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::FilterBy &filterList)
{
    output << toStdString(filterList);

    return output;
}

