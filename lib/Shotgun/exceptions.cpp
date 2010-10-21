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

#include <exceptions.h>
#include <Dict.h>
#include <List.h>
#include <Fields.h>

namespace SG {

// *****************************************************************************
SgServerURLNotSetError::SgServerURLNotSetError() 
    : SgError("SgServerURLNotSetError: ")
{
    m_msg += "Shotgun server URL is not set.";
}

// *****************************************************************************
SgAttrNotFoundError::SgAttrNotFoundError(const std::string &attrName) 
    : SgAttrError("SgAttrNotFoundError: ")
{
    m_msg += "Attribute, '" + attrName + "', is not found.";
}

// *****************************************************************************
SgAttrTypeError::SgAttrTypeError(const std::string &attrName,
                                 const xmlrpc_c::value::type_t wrongType,
                                 const xmlrpc_c::value::type_t correctType) 
    : SgAttrError("SgAttrTypeError: ")
{
    m_msg += "Attribute, '" + attrName + ", ";
    m_msg += "is not of '" + xmlrpcValueTypeStr(wrongType) + "'. ";
    m_msg += "It is of '" + xmlrpcValueTypeStr(correctType) + "'.";
}

// *****************************************************************************
SgAttrTypeError::SgAttrTypeError(const std::string &attrName,
                                 const std::string &msg) 
    : SgAttrError("SgAttrTypeError: ")
{
    m_msg += "Type error for attribute, '" + attrName + ".\n ";
    m_msg += msg;
}

// *****************************************************************************
SgAttrValueError::SgAttrValueError(const std::string &attrName) 
    : SgAttrError("SgAttrValueError: ")
{
    m_msg += "Attribute, '" + attrName + "', does not have a valid value.";
}

// *****************************************************************************
SgAttrLinkError::SgAttrLinkError(const Dict &link) 
    : SgAttrError("SgAttrLinkError: ")
{
    m_msg += "The given link is missing one or more of the required fields: \"id\", \"type\"\n";
    m_msg += link.str();
}

// *****************************************************************************
SgAttrSetValueError::SgAttrSetValueError(const Fields &fields,
                                         const std::string &errMsg) 
    : SgAttrError("SgAttrSetValueError: ")
{
    m_msg += "Failed to set values for attribute list, " + fields.str();
    if (errMsg != "")
    {
        m_msg += "\n" + errMsg;
    }
}

// *****************************************************************************
SgEmptyAttrMapError::SgEmptyAttrMapError() 
    : SgAttrError("SgEmptyAttrMapError: ")
{
    m_msg += "Empty attribute map.";
}

// *****************************************************************************
SgEntityXmlrpcError::SgEntityXmlrpcError(const std::string &msg) 
    : SgEntityError("SgEntityXmlrpcError: ") 
{
    m_msg += msg;
}

// *****************************************************************************
SgEntityNotFoundError::SgEntityNotFoundError(const std::string &entityType) 
    : SgEntityError("SgEntityNotFoundError: ")
{
    if (entityType == "")
    {
        m_msg += "entity not found.";
    }
    else
    {
        m_msg += "Shotgun \"" + entityType + "\" entity not found.";
    }
}

// *****************************************************************************
SgEntityClassNotRegisteredError::SgEntityClassNotRegisteredError(const std::string &entityType)
    : SgEntityError("SgEntityClassNotRegisteredError: ")
{
    m_msg += "Can't find entry for \"" + entityType + "\" entity in class registry.";
}

// *****************************************************************************
SgEntityDynamicCastError::SgEntityDynamicCastError(const std::string &castType) 
    : SgEntityError("SgEntityDynamicCastError: ")
{
    m_msg += "dynamic_casting to type \"" + castType + "\" failed.";
}

// *****************************************************************************
SgEntityCreateError::SgEntityCreateError(const std::string &err) 
    : SgEntityError("SgEntityCreateError: ")
{
    m_msg += err;
}

// *****************************************************************************
SgXmlrpcValueTypeError::SgXmlrpcValueTypeError(const xmlrpc_c::value &value,
                                               const xmlrpc_c::value::type_t wrongType,
                                               const xmlrpc_c::value::type_t correctType) 
    : SgXmlrpcValueError("SgXmlrpcValueTypeError: ")
{
    m_msg += toStdString(value) + ", ";
    m_msg += "is not of '" + xmlrpcValueTypeStr(wrongType) + "'. ";
    m_msg += "It is of '" + xmlrpcValueTypeStr(correctType) + "'.";
}

// *****************************************************************************
SgXmlrpcValueIsNilError::SgXmlrpcValueIsNilError()
    : SgXmlrpcValueError("SgXmlrpcValueIsNilError: ")
{
    m_msg += "the value is nil (non-existent)";
}

// *****************************************************************************
SgListIndexOutOfRangeError::SgListIndexOutOfRangeError(const int index,
                                                       const int first,
                                                       const int last)
    : SgListError("SgListIndexOutOfRangeError: ")
{
    m_msg += "index, " + toStdString(index) + ", is out of range [";
    m_msg += toStdString(first) + ", " + toStdString(last) + "].";
}

// *****************************************************************************
SgListConversionError::SgListConversionError(const xmlrpc_c::value &value)
    : SgListError("SgListConversionError: ")
{
    m_msg += "xmlrpc_c::value, " + toStdString(value) + ", is not an array type. Failed to convert it to List type";
}

// *****************************************************************************
SgDictKeyNotFoundError::SgDictKeyNotFoundError(const std::string &key)
    : SgDictError("SgDictKeyNotFoundError: ")
{
    m_msg += "key, \"" + key + "\", not found.";
}

// *****************************************************************************
SgDictConversionError::SgDictConversionError(const xmlrpc_c::value &value)
    : SgDictError("SgDictConversionError: ")
{
    m_msg += "xmlrpc_c::value, " + toStdString(value) + ", is not a struct type. Failed to convert it to Dict type";
}

} // End namespace SG
