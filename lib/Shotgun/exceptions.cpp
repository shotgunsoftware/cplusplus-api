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

namespace Shotgun {

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
    m_msg += "The given link is missing one or more of the required fields: \"id\", \"type\", \"name\"\n";
    m_msg += toStdString(link);
}

// *****************************************************************************
SgAttrLinkError::SgAttrLinkError(const xmlrpc_c::value &link,
                                 const xmlrpc_c::value::type_t &type) 
    : SgAttrError("SgAttrLinkError: ")
{
    m_msg += "The given link has the wrong type: \"" + xmlrpcValueTypeStr(type);
    m_msg += "\", it should be type of \"TYPE_STRUCT\"\n";
    m_msg += toStdString(link);
}

// *****************************************************************************
SgAttrSetValueError::SgAttrSetValueError(const std::string &fieldName,
                                         const std::string &errMsg) 
    : SgAttrError("SgAttrSetValueError: ")
{
    m_msg += "Failed to set value for attribute, '" + fieldName + "'";
    if (errMsg != "")
    {
        m_msg += "\n" + errMsg;
    }
}

// *****************************************************************************
SgAttrSetValueError::SgAttrSetValueError(const char *fieldName,
                                         const std::string &errMsg) 
    : SgAttrError("SgAttrSetValueError: ")
{
    m_msg += "Failed to set value for attribute, '" + std::string(fieldName) + "'";
    if (errMsg != "")
    {
        m_msg += "\n" + errMsg;
    }
}

// *****************************************************************************
SgAttrSetValueError::SgAttrSetValueError(const Dict &fieldNameValuePairs,
                                         const std::string &errMsg) 
    : SgAttrError("SgAttrSetValueError: ")
{
    m_msg += "Failed to set values for attribute list, " + toStdString(fieldNameValuePairs);
    if (errMsg != "")
    {
        m_msg += "\n" + errMsg;
    }
}

// *****************************************************************************
SgAttrSetValueError::SgAttrSetValueError(const List &fields,
                                         const std::string &errMsg) 
    : SgAttrError("SgAttrSetValueError: ")
{
    m_msg += "Failed to set values for attribute list, " + toStdString(fields);
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
SgEntityFunctionNotFoundError::SgEntityFunctionNotFoundError(const std::string &entityType, 
                                                             const std::string &funcMapName) 
    : SgEntityError("SgEntityFunctionNotFoundError: ")
{
    m_msg += "Can't find entry for \"" + entityType + "\" entity in function map \"";
    m_msg += funcMapName + "\". Check Shotgun class' constructor.";
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
SgApiError::SgApiError(const std::string &api) 
    : SgError("SgApiError: ")
{
    m_msg += api + " is not supported.";
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
SgListError::SgListError(const int index,
                         const int first,
                         const int last)
    : SgError("SgListError: ")
{
    m_msg += "index, " + toStdString(index) + ", is out of range [";
    m_msg += toStdString(first) + ", " + toStdString(last) + "].";
}

// *****************************************************************************
SgListError::SgListError(const xmlrpc_c::value &value)
    : SgError("SgListError: ")
{
    m_msg += "xmlrpc_c::value, " + toStdString(value) + ", is not an array type. Failed to convert it to List type";
}

// *****************************************************************************
SgDictError::SgDictError(const std::string &key)
    : SgError("SgDictError: ")
{
    m_msg += "key, \"" + key + "\", not found.";
}

// *****************************************************************************
SgDictError::SgDictError(const xmlrpc_c::value &value)
    : SgError("SgDictError: ")
{
    m_msg += "xmlrpc_c::value, " + toStdString(value) + ", is not a struct type. Failed to convert it to Dict type";
}

} // End namespace Shotgun
