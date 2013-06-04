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

#ifndef __SG_EXCEPTIONS_H__
#define __SG_EXCEPTIONS_H__

#include <Shotgun/config.h>
#include <Shotgun/types.h>

namespace SG {

class Dict;
class List;
class Fields;

// *****************************************************************************
/// This is a very basic Shotgun exception that can be used to throw any error.
/// We suggest to derive from it and create more specific exceptions.
class SG_API SgError : public std::exception
{
public:
	SgError() : m_msg("") {}
    SgError(const std::string &msg) { m_msg = msg; }
    SgError(const char *msg) { m_msg = msg; }

    virtual ~SgError() throw() {}

    virtual const char *what() const throw()
    {
        return m_msg.c_str();
    }

protected:
    std::string m_msg;
};

// *****************************************************************************
/// This exception is thrown if Shotgun server URL is not set.
class SG_API SgServerURLNotSetError : public SgError
{
public:
    SgServerURLNotSetError();

    virtual ~SgServerURLNotSetError() throw() {}
};

// *****************************************************************************
/// "SgAttrError" is nothing more than it's base class, "SgError". It is just an 
/// extra container for the attribute-specific exceptions.
class SG_API SgAttrError : public SgError
{
public:
	SgAttrError() : SgError("") {}
    SgAttrError(const std::string &msg) : SgError(msg) {}
    SgAttrError(const char *msg) : SgError(msg) {}

    virtual ~SgAttrError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if the given attribute does not exist.
class SG_API SgAttrNotFoundError : public SgAttrError
{
public:
    SgAttrNotFoundError(const std::string &attrName);

    virtual ~SgAttrNotFoundError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if the attribute has a different type from the
/// one expected.
class SG_API SgAttrTypeError : public SgAttrError
{
public:
    SgAttrTypeError(const std::string &attrName,
                    const Json::ValueType wrongType,
                    const Json::ValueType correctType);
    SgAttrTypeError(const std::string &attrName,
                    const std::string &msg = "");

    virtual ~SgAttrTypeError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if the attribute does not have a valid value.
/// It is usually caused by a nil value on Shotgun side.
class SG_API SgAttrValueError : public SgAttrError
{
public:
    SgAttrValueError(const std::string &attrName);

    virtual ~SgAttrValueError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if an entity link is missing a required field, 
/// such as "id" or "type".
class SG_API SgAttrLinkError : public SgAttrError
{
public:
    SgAttrLinkError(const Dict &link);

    virtual ~SgAttrLinkError() throw() {}
};


// *****************************************************************************
/// This exception is thrown if setting attribute value(s) for an entity fails.
class SG_API SgAttrSetValueError : public SgAttrError
{
public:
    SgAttrSetValueError(const Fields &fields,
                        const std::string &errMsg = "");

    virtual ~SgAttrSetValueError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if the attribute map is empty.
class SG_API SgEmptyAttrMapError : public SgAttrError
{
public:
    SgEmptyAttrMapError();

    virtual ~SgEmptyAttrMapError() throw() {}
};

// *****************************************************************************
/// "SgEntityError" is nothing more than it's base class, "SgError". It is just 
/// an extra container for the entity-specific exceptions.
class SG_API SgEntityError : public SgError
{
public:
	SgEntityError() : SgError("") {}
    SgEntityError(const std::string &msg) : SgError(msg) {}
    SgEntityError(const char *msg) : SgError(msg) {}

    virtual ~SgEntityError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if a XML-RPC call fails.
class SG_API SgEntityJsonrpcError : public SgEntityError
{
public:
    SgEntityJsonrpcError(const std::string &msg);

    virtual ~SgEntityJsonrpcError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if an entity is not found in Shotgun.
class SG_API SgEntityNotFoundError : public SgEntityError
{
public:
    SgEntityNotFoundError(const std::string &entityType = "" );

    virtual ~SgEntityNotFoundError() throw() {}
};

// *****************************************************************************
/// This exception is throw if a given type of entity is not registered.
class SG_API SgEntityNotRegisteredError : public SgEntityError
{
public:
    SgEntityNotRegisteredError(const std::string &entityType);

    virtual ~SgEntityNotRegisteredError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if dynamic_casting to a specified type of entity
/// fails.
class SG_API SgEntityDynamicCastError : public SgEntityError
{
public:
    SgEntityDynamicCastError(const std::string &castType);

    virtual ~SgEntityDynamicCastError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if creating a new entity fails.
class SG_API SgEntityCreateError : public SgEntityError
{
public:
    SgEntityCreateError(const std::string &err);

    virtual ~SgEntityCreateError() throw() {}
};

// *****************************************************************************
/// "SgXmlrpcValueError" is nothing more than it's base class, "SgError". It is 
/// just an extra container for the Json::Value related exceptions.
class SG_API SgJsonrpcValueError : public SgError
{
public:
	SgJsonrpcValueError() : SgError("") {}
    SgJsonrpcValueError(const std::string &msg) : SgError(msg) {}
    SgJsonrpcValueError(const char *msg) : SgError(msg) {}

    virtual ~SgJsonrpcValueError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if an instantiated Json::Value has a different
/// type than expected.
class SG_API SgJsonrpcValueTypeError : public SgJsonrpcValueError
{
public:
    SgJsonrpcValueTypeError(const Json::Value &value,
                           const Json::ValueType wrongType,
                           const Json::ValueType correctType);

    virtual ~SgJsonrpcValueTypeError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if the Json::Value is of TYPE_NIL, i.e. 
/// non-existent.
class SG_API SgJsonrpcValueIsNilError : public SgJsonrpcValueError
{
public:
    SgJsonrpcValueIsNilError();

    virtual ~SgJsonrpcValueIsNilError() throw() {}
};

// *****************************************************************************
/// "SgListError" is nothing more than it's base class, "SgError". It is 
/// just an extra container for the List class related exceptions.
class SG_API SgListError : public SgError
{
public:
	SgListError() : SgError("") {}
    SgListError(const std::string &msg) : SgError(msg) {}
    SgListError(const char *msg) : SgError(msg) {}

    virtual ~SgListError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if the index of a List is out of range.
class SG_API SgListIndexOutOfRangeError : public SgListError
{
public:
    SgListIndexOutOfRangeError(const int index,
                               const int first,
                               const int last);

    virtual ~SgListIndexOutOfRangeError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if a Json::Value can't be converted to a List.
class SG_API SgListConversionError : public SgListError
{
public:
    SgListConversionError(const Json::Value &value);

    virtual ~SgListConversionError() throw() {}
};

// *****************************************************************************
/// "SgDictError" is nothing more than it's base class, "SgError". It is 
/// just an extra container for the Dict class related exceptions.
class SG_API SgDictError : public SgError
{
public:
	SgDictError() : SgError("") {}
    SgDictError(const std::string &msg) : SgError(msg) {}
    SgDictError(const char *msg) : SgError(msg) {}

    virtual ~SgDictError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if the given key does not exist in a Dict.
class SG_API SgDictKeyNotFoundError : public SgDictError
{
public:
    SgDictKeyNotFoundError(const std::string &key);

    virtual ~SgDictKeyNotFoundError() throw() {}
};

// *****************************************************************************
/// This exception is thrown if a Json::Value can't be converted to a Dict.
class SG_API SgDictConversionError : public SgDictError
{
public:
    SgDictConversionError(const Json::Value &value);

    virtual ~SgDictConversionError() throw() {}
};

} // End namespace SG

#endif    // End #ifdef __SG_EXCEPTIONS_H__
