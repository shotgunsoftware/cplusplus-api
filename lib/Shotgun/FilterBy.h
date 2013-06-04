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

#ifndef __SG_FILTERBY_H__
#define __SG_FILTERBY_H__

#include <string>

#include <Shotgun/config.h>
#include <Shotgun/types.h>
#include <Shotgun/List.h>
#include <Shotgun/Dict.h>

namespace SG {

// *****************************************************************************
/*!
 \class FilterBy
 A FilterBy class is a wrapper around a "filters" Dict. "filters" format is 
 specified as a <general_condition> hash, which contains <simple_conditions>
 hashes, even more <general_condition> hashes, or no conditions.

 \htmlonly
 <pre>
 <br>
 <b>general_condition</b>: { <br>
     'logical_operator': 'and' | 'or',               # Logical operator to apply to all conditions <br>
     'conditions': [                                 # Array of <b>general_condition</b>'s or <b>simple_condition</b>'s <br>
         <b>general_condition</b> | <b>simple_condition</b>,       # An empty array signifies no conditions. <br>
         ... <br>
     ] <br>
 } <br>

 <b>simple_condition</b>: { <br>
     'path': string,                                 # Field name to filter on, which can be either: <br>
                                                     # (1) field_name <br>
                                                     # (2) join_field_name.entity_type.field_name <br>
     'relation': string,                             # Comparison operator <br>
     'values': [                                     # Array of field values to compare with.  If the comparison <br>
         field_value,                                # operator accepts only one value, specify a single-element <br>
         ...                                         # array (e.g. [0]) <br>
     ] <br>
 }
 </pre>  
 \endhtmlonly
*/
class SG_API FilterBy
{
public:
    // -------------------------------------------------------------------------
    /// A default constructor.
    FilterBy();

    /// A copy constructor.
    FilterBy(const FilterBy &ref);

    /// A constructor that takes a filters Dict.
    FilterBy(const Dict &filters);

    /// A template constructor that adds one simple condition to the "filters".
    template <typename T>
    FilterBy(const std::string &path,
             const std::string &relation,
             const T &value);

    // -------------------------------------------------------------------------
    /// A template logic "and" function that adds one simple condition to the "filters".
    template <typename T>
    FilterBy &And(const std::string &path,
                  const std::string &relation,
                  const T &value);

    // -------------------------------------------------------------------------
    /// A logic "and" function that adds one general condition to the "filters".
    FilterBy &And(const FilterBy &that);

    // -------------------------------------------------------------------------
    /// A template logic "or" function that adds one condition to the "filters".
    template <typename T>
    FilterBy &Or(const std::string &path,
                 const std::string &relation,
                 const T &value);
    
    // -------------------------------------------------------------------------
    /// A logic "or" function that adds one general condition to the "filters".
    FilterBy &Or(const FilterBy &that);

    // -------------------------------------------------------------------------
    /// Returns the "filters" dict.
    const Dict &filters() const;

    // -------------------------------------------------------------------------
    /// Returns whether the "filters" dict is empty.
    const bool empty() const;

    // -------------------------------------------------------------------------
    /// Returns the size of the "filters" dict.
	unsigned int size();

    // -------------------------------------------------------------------------
    /// Returns the string representation of the FilterBy class.
    const std::string str() const { return m_filters->str(); }

    // -------------------------------------------------------------------------
    /// Removes all the contents from the "filters" dict.
    void clear();

    // -------------------------------------------------------------------------
    FilterBy &operator=(const FilterBy &that)
    {
        if (this != &that)
        {
            m_filters = that.m_filters;
        }

        return *this;
    }

    // -------------------------------------------------------------------------
    friend std::ostream& operator<<(std::ostream &output, const FilterBy &filterBy)
    {
        output << filterBy.str();
        return output;
    }

protected:
    // -------------------------------------------------------------------------
    /// Adds a simple condition to the "filters" with a specified logic operator.
    FilterBy &op(const std::string &logicOperator,
                 const std::string &path,
                 const std::string &relation,
                 const Json::Value &value);

    // -------------------------------------------------------------------------
    /// Adds a general condition to the "filters" with a specified logic operator.
    FilterBy &op(const std::string &logicOperator,
                 const FilterBy &that);

    Dict *m_filters; ///< The "filters" dict.
};

// *****************************************************************************
template <typename T>
FilterBy::FilterBy(const std::string &path,
                   const std::string &relation,
                   const T &value)
{
     m_filters = new Dict();
     op("and", path, relation, toJsonrpcValue(value));      
}

// *****************************************************************************
template <typename T>
FilterBy &FilterBy::And(const std::string &path,
                        const std::string &relation,
                        const T &value)
{
    return op("and", path, relation, toJsonrpcValue(value));
}

// *****************************************************************************
template <typename T>
FilterBy &FilterBy::Or(const std::string &path,
                       const std::string &relation,
                       const T &value)
{
    return op("or", path, relation, toJsonrpcValue(value));
}

} // End namespace SG

#endif    // End #ifdef __SG_FILTERBY_H__
