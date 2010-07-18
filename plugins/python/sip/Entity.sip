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

namespace Shotgun {

// *****************************************************************************
class Entity
{
%TypeHeaderCode
    #include <Shotgun/Entity.h>
%End

protected:
    // (1) Even if this ctor is protected, it shoule be put here to prevent a
    //     default public ctor being generated. See the complex example in the
    //     "SIP reference guide".
    //
    //         http://www.riverbankcomputing.co.uk/static/Docs/sip4/index.html
    //
    // (2) The Shotgun type needs its namespace attached.
    // (3) TODO: may need a /TransferThis/ annotation
    Entity(Shotgun::Shotgun *sg);

public:
    virtual ~Entity();

    enum InvalidAttrMode
    {
        INVALID_ATTR_THROW_EXCEPTION = 0,
        INVALID_ATTR_USE_DEFAULT
    };

    const int sgId() const;
    const time_t sgDateCreated() const;
    const time_t sgDateUpdated() const;
    virtual const std::string sgShowName() const;
    virtual const std::string sgShowCode() const;
    virtual const std::string sgName() const;
    
    // Can't use both version. Otherwise it will complain something like this:
    // Shotgun::Entity::sg() has overloaded functions with the same Python signature
    //
    //const Shotgun::Shotgun *sg() const;
    Shotgun::Shotgun *sg();

    void setInvalidAttrMode(InvalidAttrMode mode);
    const InvalidAttrMode getInvalidAttrMode() const;
    void printAttrs() const;
    const std::string entityType() const;
    const xmlrpc_c::value &attrs() const;
    const std::string str() const;
    const Shotgun::SgMap asLink() const;

    const std::string linkEntityType(const std::string &linkName) const;

    // Get a attribute's value of a generic data type
    const xmlrpc_c::value getAttrValue(const std::string &attrName) const throw(Shotgun::SgAttrError);
    static const xmlrpc_c::value getAttrValue(const std::string &attrName, 
                                              const Shotgun::SgMap &attrsMap) throw(Shotgun::SgAttrError);

    const Shotgun::Strings getAttrValueAsTags(const std::string &attrName) const throw(Shotgun::SgAttrError);
    static const Shotgun::Strings getAttrValueAsTags(const std::string &attrName,
                                                        const Shotgun::SgMap &attrsMap) throw(Shotgun::SgAttrError);

    Shotgun::Entity *getAttrValueAsEntityPtr(const std::string &attrName) 
                            throw(Shotgun::SgAttrError, Shotgun::SgEntityError) /Factory/;
    static Shotgun::Entity *getAttrValueAsEntityPtr(Shotgun::Shotgun *sg,
                                                       const std::string &attrName,
                                                       const Shotgun::SgMap &attrsMap) 
                            throw(Shotgun::SgAttrError, Shotgun::SgEntityError) /Factory/;

    Shotgun::EntityPtrs getAttrValueAsMultiEntityPtr(const std::string &attrName) 
                            throw(Shotgun::SgAttrError, Shotgun::SgEntityError) /Factory/;
    static Shotgun::EntityPtrs getAttrValueAsMultiEntityPtr(Shotgun::Shotgun *sg,
                                                               const std::string &attrName,
                                                               const Shotgun::SgMap &attrsMap) 
                            throw(Shotgun::SgAttrError, Shotgun::SgEntityError) /Factory/;

    const std::string getAttrValueAsUserLogin(const std::string &attrName) const 
                            throw(Shotgun::SgAttrError, Shotgun::SgEntityError);
    static const std::string getAttrValueAsUserLogin(Shotgun::Shotgun *sg,
                                                     const std::string &attrName,
                                                     const Shotgun::SgMap &attrsMap) 
                            throw(Shotgun::SgAttrError, Shotgun::SgEntityError);

    const std::string getAttrValueAsQtURL(const std::string &attrName) const throw(Shotgun::SgAttrError);
    static const std::string getAttrValueAsQtURL(const std::string &attrName,
                                                 const Shotgun::SgMap &attrsMap) throw(Shotgun::SgAttrError);

    const std::string getAttrValueAsQtPath(const std::string &attrName) const throw(Shotgun::SgAttrError);
    static const std::string getAttrValueAsQtPath(const std::string &attrName,
                                                  const Shotgun::SgMap &attrsMap) throw(Shotgun::SgAttrError);

    // Set a attribute's value - Omitted the optional "parent_entity" for now
    void setAttrValue(const std::string &attrName,
                      const xmlrpc_c::value &attrValue,
                      const Shotgun::SgArray &multiValues = Shotgun::SgArray()) throw(Shotgun::SgAttrError);
    void setAttrValue(const Shotgun::SgMap &attrPairs) throw(Shotgun::SgAttrError);

    // -----------------------------------------------------------------------------------
    // The "In" or "Out" annotation is used to specify that the argument (which 
    // should be a pointer type - reference is fine, too) is either used to 
    // 
    //     - pass a value to the function. ( /In/ ) 
    // OR  - return a value as an element of a tuple. ( /Out/ )
    // 
    // Both "In" and "Out" are specified for the same argument here. In Python, 
    // the syntax of using the following function should be like this as if it 
    // has a return value:
    // 
    //     findMap = Shotgun.Entity.addOneConditionToFindMap(findMap,
    //                                                          "login", "is", "jeanshen")
    // -----------------------------------------------------------------------------------

    // Add one more condition to the search map - this is a convenience function
    static void addOneConditionToFindMap(Shotgun::SgMap &findMap /In, Out/,
                                         const std::string &filterName,
                                         const std::string &filterOp,
                                         const xmlrpc_c::value &filterValue) throw(Shotgun::SgAttrError);

    // Build a findMap with no condition - this is a convenience function
    static Shotgun::SgMap buildFindMapWithNoFilter(Shotgun::Shotgun *sg,
                                                      const std::string &entityType,
                                                      const std::string &showCode = "",
                                                      const int limit = 0,
                                                      const Shotgun::SgArray &extraReturnFields = Shotgun::SgArray(),
                                                      const bool retiredOnly = false) throw(Shotgun::SgEntityError, Shotgun::SgAttrError);

    // Build a findMap with just one condition - this is a convenience function
    static Shotgun::SgMap buildFindMapWithSingleFilter(Shotgun::Shotgun *sg,
                                                          const std::string &entityType,
                                                          const std::string &filterName,
                                                          const std::string &filterOp,
                                                          const xmlrpc_c::value &filterValue,
                                                          const std::string &showCode = "",
                                                          const int limit = 0,
                                                          const Shotgun::SgArray &extraReturnFields = Shotgun::SgArray(),
                                                          const bool retiredOnly = false) throw(Shotgun::SgEntityError, Shotgun::SgAttrError);

    // ------------------------------------------------------------------------
    SIP_PYOBJECT __str__();
%MethodCode
    sipRes = PyString_FromString(sipCpp->str().c_str());
%End

    // ------------------------------------------------------------------------
    SIP_PYOBJECT __repr__();
%MethodCode
    sipRes = PyString_FromString(sipCpp->str().c_str());
%End

};

}; // End namespace Shotgun - IMPORTANT: has to have the semi-colon
