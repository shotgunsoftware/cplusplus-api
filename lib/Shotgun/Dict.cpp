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

#include <Shotgun/Dict.h>

namespace SG {

// *****************************************************************************
Dict::Dict() : m_value(new std::map<std::string, Json::Value>())
{
}

// *****************************************************************************
Dict::Dict(const Dict &ref) : m_value(ref.m_value)
{
}

// *****************************************************************************
Dict::Dict(const std::map<std::string, Json::Value> &map)
{
	m_value = new std::map<std::string, Json::Value>(map);
}

// *****************************************************************************
Dict::Dict(const Json::Value &value)
{
	if (value.isObject())
    {
        m_value = new std::map<std::string, Json::Value>();
		for (Json::ValueIterator itr = value.begin(); itr != value.end(); itr++ )
			(*m_value)[itr.memberName()] = Json::Value(value[itr.memberName()]);
    }
    else
    {
        throw SgDictConversionError(value);
    }
}

// *****************************************************************************
const Json::Value Dict::value(const std::string &key) const
{
    std::map<std::string, Json::Value>::const_iterator foundIter = m_value->find(key);
    if (foundIter != m_value->end())
    {
        return (*foundIter).second;
    }
    else
    {
        throw SgDictKeyNotFoundError(key);
    }
}

const std::map<std::string, Json::Value> &Dict::value() const
{ 
    return *m_value; 
}

// *****************************************************************************
const Json::Value Dict::operator[](const std::string &key) const
{
    return value(key);
}

// *****************************************************************************
const bool Dict::find(const std::string &key) const
{
    std::map<std::string, Json::Value>::const_iterator foundIter = m_value->find(key);
    if (foundIter != m_value->end())
    {
        return true;
    }

    return false;
}

// *****************************************************************************
Dict &Dict::erase(const std::string &key)
{
    m_value->erase(key);

    return *this;
}

const int Dict::size()
{ 
    return m_value->size(); 
}

void Dict::clear() 
{ 
    m_value->clear(); 
}

const bool Dict::empty() const 
{ 
    return m_value->empty(); 
}
} // End namespace SG
