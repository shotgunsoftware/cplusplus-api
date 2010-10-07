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

#include <Shotgun/types.h>

namespace Shotgun {

class Dict;
class List;

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
    SgAttrNotFoundError(const std::string &attrName);

    virtual ~SgAttrNotFoundError() throw() {}
};

// *****************************************************************************
class SgAttrTypeError : public SgAttrError
{
public:
    SgAttrTypeError(const std::string &attrName,
                    const xmlrpc_c::value::type_t wrongType,
                    const xmlrpc_c::value::type_t correctType);
    SgAttrTypeError(const std::string &attrName,
                    const std::string &msg = "");

    virtual ~SgAttrTypeError() throw() {}
};

// *****************************************************************************
class SgAttrValueError : public SgAttrError
{
public:
    SgAttrValueError(const std::string &attrName);

    virtual ~SgAttrValueError() throw() {}
};


// *****************************************************************************
class SgAttrLinkError : public SgAttrError
{
public:
    SgAttrLinkError(const Dict &link);
    SgAttrLinkError(const xmlrpc_c::value &link,
                    const xmlrpc_c::value::type_t &type);

    virtual ~SgAttrLinkError() throw() {}
};


// *****************************************************************************
class SgAttrSetValueError : public SgAttrError
{
public:
    SgAttrSetValueError(const std::string &fieldName,
                        const std::string &errMsg = "");
    SgAttrSetValueError(const char *fieldName,
                        const std::string &errMsg = "");
    SgAttrSetValueError(const Fields &fields,
                        const std::string &errMsg = "");

    virtual ~SgAttrSetValueError() throw() {}
};

// *****************************************************************************
class SgEmptyAttrMapError : public SgAttrError
{
public:
    SgEmptyAttrMapError();

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
    SgEntityXmlrpcError(const std::string &msg);

    virtual ~SgEntityXmlrpcError() throw() {}
};

// *****************************************************************************
class SgEntityNotFoundError : public SgEntityError
{
public:
    SgEntityNotFoundError(const std::string &entityType = "" );

    virtual ~SgEntityNotFoundError() throw() {}
};

// *****************************************************************************
class SgEntityFunctionNotFoundError : public SgEntityError
{
public:
    SgEntityFunctionNotFoundError(const std::string &entityType, 
                                  const std::string &funcMapName);

    virtual ~SgEntityFunctionNotFoundError() throw() {}
};

// *****************************************************************************
class SgEntityDynamicCastError : public SgEntityError
{
public:
    SgEntityDynamicCastError(const std::string &castType);

    virtual ~SgEntityDynamicCastError() throw() {}
};

// *****************************************************************************
class SgEntityCreateError : public SgEntityError
{
public:
    SgEntityCreateError(const std::string &err);

    virtual ~SgEntityCreateError() throw() {}
};

// *****************************************************************************
class SgApiError : public SgError
{
public:
    SgApiError(const std::string &api);

    virtual ~SgApiError() throw() {}
};

// *****************************************************************************
class SgXmlrpcValueError : public SgError
{
public:
    SgXmlrpcValueError(const std::string &msg = "") : SgError(msg) {}
    SgXmlrpcValueError(const char *msg = "") : SgError(msg) {}

    virtual ~SgXmlrpcValueError() throw() {}
};

// *****************************************************************************
class SgXmlrpcValueTypeError : public SgXmlrpcValueError
{
public:
    SgXmlrpcValueTypeError(const xmlrpc_c::value &value,
                           const xmlrpc_c::value::type_t wrongType,
                           const xmlrpc_c::value::type_t correctType);

    virtual ~SgXmlrpcValueTypeError() throw() {}
};

// *****************************************************************************
class SgXmlrpcValueIsNilError : public SgXmlrpcValueError
{
public:
    SgXmlrpcValueIsNilError();

    virtual ~SgXmlrpcValueIsNilError() throw() {}
};

// *****************************************************************************
class SgListError : public SgError
{
public:
    SgListError(const int index,
                const int first,
                const int last);
    SgListError(const xmlrpc_c::value &value);

    virtual ~SgListError() throw() {}
};

// *****************************************************************************
class SgDictError : public SgError
{
public:
    SgDictError(const std::string &key);
    SgDictError(const xmlrpc_c::value &value);

    virtual ~SgDictError() throw() {}
};

} // End namespace Shotgun

#endif    // End #ifdef __EXCEPTIONS_H__
