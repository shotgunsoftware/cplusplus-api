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

#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <Shotgun/Type.h>

namespace Shotgun {

// *****************************************************************************
class SgError : public std::exception
{
public:
    SgError(const std::string &msg = "") { m_msg = msg; }
    SgError(const char *msg = "") { m_msg = msg; }

    virtual ~SgError() throw() {}

    virtual const char *what() const throw()
    {
        return m_msg.c_str();
    }

protected:
    std::string m_msg;
};

// *****************************************************************************
// "SgAttrError" is nothing more than it's base class, "SgError". It is just an 
// extra container for the attribute-specific exceptions
class SgAttrError : public SgError
{
public:
    SgAttrError(const std::string &msg = "") : SgError(msg) {}
    SgAttrError(const char *msg = "") : SgError(msg) {}

    virtual ~SgAttrError() throw() {}
};

// *****************************************************************************
class SgAttrNotFoundError : public SgAttrError
{
public:
    SgAttrNotFoundError(const std::string &attrName) : SgAttrError("SgAttrNotFoundError: ")
    {
        m_msg += "Attribute, '" + attrName + "', is not found.";
    }

    virtual ~SgAttrNotFoundError() throw() {}
};

// *****************************************************************************
class SgAttrTypeError : public SgAttrError
{
public:
    SgAttrTypeError(const std::string &attrName,
                    const xmlrpc_c::value::type_t wrongType,
                    const xmlrpc_c::value::type_t correctType) : SgAttrError("SgAttrTypeError: ")
    {
        m_msg += "Attribute, '" + attrName + ", ";
        m_msg += "is not of '" + xmlrpcValueTypeStr(wrongType) + "'. ";
        m_msg += "It is of '" + xmlrpcValueTypeStr(correctType) + "'.";
    }

    virtual ~SgAttrTypeError() throw() {}
};

// *****************************************************************************
class SgAttrValueError : public SgAttrError
{
public:
    SgAttrValueError(const std::string &attrName) : SgAttrError("SgAttrValueError: ")
    {
        m_msg += "Attribute, '" + attrName + "', does not have a valid value.";
    }

    virtual ~SgAttrValueError() throw() {}
};


// *****************************************************************************
class SgAttrLinkError : public SgAttrError
{
public:
    SgAttrLinkError(const SgMap &link) : SgAttrError("SgAttrLinkError: ")
    {
        m_msg += "The given link is missing one or more of the required fields: \"id\", \"type\", \"name\"\n";
        m_msg += toStdString(link);
    }

    SgAttrLinkError(const xmlrpc_c::value &link,
                    const xmlrpc_c::value::type_t &type) : SgAttrError("SgAttrLinkError: ")
    {
        m_msg += "The given link has the wrong type: \"" + xmlrpcValueTypeStr(type);
        m_msg += "\", it should be type of \"TYPE_STRUCT\"\n";
        m_msg += toStdString(link);
    }

    virtual ~SgAttrLinkError() throw() {}
};


// *****************************************************************************
class SgAttrSetValueError : public SgAttrError
{
public:
    SgAttrSetValueError(const std::string &attrName,
                        const std::string &errMsg = "") : SgAttrError("SgAttrSetValueError: ")
    {
        m_msg += "Failed to set value for attribute, '" + attrName + "'";
        if (errMsg != "")
        {
            m_msg += "\n" + errMsg;
        }
    }

    SgAttrSetValueError(const SgMap &attrPairs,
                        const std::string &errMsg = "") : SgAttrError("SgAttrSetValueError: ")
    {
        m_msg += "Failed to set values for attribute list, " + toStdString(attrPairs);
        if (errMsg != "")
        {
            m_msg += "\n" + errMsg;
        }
    }

    virtual ~SgAttrSetValueError() throw() {}
};

// *****************************************************************************
class SgEmptyAttrMapError : public SgAttrError
{
public:
    SgEmptyAttrMapError() : SgAttrError("SgEmptyAttrMapError: ")
    {
        m_msg += "Empty attribute map.";
    }

    virtual ~SgEmptyAttrMapError() throw() {}
};

// *****************************************************************************
class SgEntityError : public SgError
{
public:
    SgEntityError(const std::string &msg = "") : SgError(msg) {}
    SgEntityError(const char *msg = "") : SgError(msg) {}

    virtual ~SgEntityError() throw() {}
};

// *****************************************************************************
class SgEntityXmlrpcError : public SgEntityError
{
public:
    SgEntityXmlrpcError(const std::string &msg) : SgEntityError("SgEntityXmlrpcError: ") 
    {
        m_msg += msg;
    }

    virtual ~SgEntityXmlrpcError() throw() {}
};

// *****************************************************************************
class SgEntityNotFoundError : public SgEntityError
{
public:
    SgEntityNotFoundError(const std::string &entityType = "" ) : SgEntityError("SgEntityNotFoundError: ")
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

    virtual ~SgEntityNotFoundError() throw() {}
};

// *****************************************************************************
class SgEntityFunctionNotFoundError : public SgEntityError
{
public:
    SgEntityFunctionNotFoundError(const std::string &entityType, 
                                  const std::string &funcMapName) : SgEntityError("SgEntityFunctionNotFoundError: ")
    {
        m_msg += "Can't find entry for \"" + entityType + "\" entity in function map \"";
        m_msg += funcMapName + "\". Check Shotgun class' constructor.";
    }

    virtual ~SgEntityFunctionNotFoundError() throw() {}
};

// *****************************************************************************
class SgEntityDynamicCastError : public SgEntityError
{
public:
    SgEntityDynamicCastError(const std::string &castType) : SgEntityError("SgEntityDynamicCastError: ")
    {
        m_msg += "dynamic_casting to type \"" + castType + "\" failed.";
    }

    virtual ~SgEntityDynamicCastError() throw() {}
};

// *****************************************************************************
class SgEntityCreateError : public SgEntityError
{
public:
    SgEntityCreateError(const std::string &err) : SgEntityError("SgEntityCreateError: ")
    {
        m_msg += err;
    }

    virtual ~SgEntityCreateError() throw() {}
};

// *****************************************************************************
class SgApiError : public SgError
{
public:
    SgApiError(const std::string &api) : SgError("SgApiError: ")
    {
        m_msg += api + " is not supported.";
    }

    virtual ~SgApiError() throw() {}
};

// *****************************************************************************
class SgXmlrpcValueTypeError : public SgError
{
public:
    SgXmlrpcValueTypeError(const xmlrpc_c::value &value,
                           const xmlrpc_c::value::type_t wrongType,
                           const xmlrpc_c::value::type_t correctType) : SgError("SgXmlrpcValueTypeError: ")
    {
        m_msg += toStdString(value) + ", ";
        m_msg += "is not of '" + xmlrpcValueTypeStr(wrongType) + "'. ";
        m_msg += "It is of '" + xmlrpcValueTypeStr(correctType) + "'.";
    }

    virtual ~SgXmlrpcValueTypeError() throw() {}
};

} // End namespace Shotgun

#endif    // End #ifdef __EXCEPTIONS_H__
