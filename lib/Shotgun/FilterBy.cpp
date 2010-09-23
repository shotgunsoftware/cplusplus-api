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
FilterBy::FilterBy() : m_filters(SgMap())
{
}

// *****************************************************************************
FilterBy::FilterBy(const SgMap &filters) : m_filters(filters)
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
    SgMap newCondition;
    newCondition["path"] = toXmlrpcValue(path);
    newCondition["relation"] = toXmlrpcValue(relation);

    // The value has to be converted to an array
    SgArray valueArray;
    if (value.type() == xmlrpc_c::value::TYPE_ARRAY)
    {
        valueArray = xmlrpc_c::value_array(value).vectorValueValue();
    }
    else
    {
        valueArray.push_back(value);
    }
    newCondition["values"] = toXmlrpcValue(valueArray);
 
    // -------------------------------------------------------------------
    // Add the new simple condition to the conditions list
    SgArray conditions;
    if (!m_filters.empty()) 
    {
        // The Original m_filters map now becomes a condition
        conditions.push_back(toXmlrpcValue(m_filters));
    }
    conditions.push_back(toXmlrpcValue(newCondition));

    // -------------------------------------------------------------------
    // Update the filters
    m_filters.clear();
    m_filters["logical_operator"] = toXmlrpcValue(logicOperator);
    m_filters["conditions"] = toXmlrpcValue(conditions);

    return *this;
}

// *****************************************************************************
FilterBy &FilterBy::op(const std::string &logicOperator,
                       const FilterBy &that)
{
    SgArray conditions;
    conditions.push_back(toXmlrpcValue(m_filters));
    conditions.push_back(toXmlrpcValue(that.m_filters));

    // -------------------------------------------------------------------
    // Update the filters
    m_filters.clear();
    m_filters["logical_operator"] = toXmlrpcValue(logicOperator);
    m_filters["conditions"] = toXmlrpcValue(conditions);

    return *this;
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const FilterBy &filterList)
{
    output << filterList.filters();

    return output;
}

} // End namespace Shotgun

