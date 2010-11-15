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

namespace SG {

// *****************************************************************************
class Entity
{
%TypeHeaderCode
    #include <Shotgun/Entity.h>
%End

%ConvertToSubClassCode
    // Downcast to subclass - the class' namespace needs to be included 

    std::string classType = sipCpp->namespaceStr() + "::" + sipCpp->classType();
    sipType = sipFindType(classType.c_str());
%End

public:
    virtual ~Entity();

    // ------------------------------------------------------------------------
    // Can't have both in SIP
    //const SG::Shotgun *sg() const;
    SG::Shotgun *sg();

    // ------------------------------------------------------------------------
    virtual const int sgId() const throw(SG::SgError);
    virtual const time_t sgDateCreated() const throw(SG::SgError);
    virtual const time_t sgDateUpdated() const throw(SG::SgError);
    virtual const std::string sgProjectName() const throw(SG::SgError);
    virtual const std::string sgProjectCode() const throw(SG::SgError);

    // ------------------------------------------------------------------------
    const std::string entityType() const;
    const std::string classType() const;
    virtual const std::string namespaceStr() const;

    const xmlrpc_c::value &attrs() const;
    const std::string str() const;
    const SG::Dict asLink() const;
    const std::string linkEntityType(const std::string &linkName) const;
    
    // ------------------------------------------------------------------------
    // Get a attribute's value as a generic xmlrpc_c::value type
    virtual const xmlrpc_c::value getAttrValue(const std::string &attrName) const throw(SG::SgError);
    static const xmlrpc_c::value getAttrValue(const std::string &attrName, 
                                              const SG::Dict &attrsMap) throw(SG::SgError);

    // ------------------------------------------------------------------------
    virtual const SG::Strings getAttrValueAsTags(const std::string &attrName) const throw(SG::SgError);
    static const SG::Strings getAttrValueAsTags(const std::string &attrName,
                                                const SG::Dict &attrsMap) throw(SG::SgError);

    // ------------------------------------------------------------------------
    virtual SG::Entity *getAttrValueAsEntity(const std::string &attrName) const throw(SG::SgError) /Factory/;
    static SG::Entity *getAttrValueAsEntity(SG::Shotgun *sg,
                                            const std::string &attrName,
                                            const SG::Dict &attrsMap) throw(SG::SgError) /Factory/;

    // ------------------------------------------------------------------------
    virtual std::vector<SG::Entity *> getAttrValueAsEntities(const std::string &attrName) const throw(SG::SgError) /Factory/;
    static std::vector<SG::Entity *> getAttrValueAsEntities(SG::Shotgun *sg,
                                                            const std::string &attrName,
                                                            const SG::Dict &attrsMap) throw(SG::SgError) /Factory/;

    // ------------------------------------------------------------------------
    virtual const std::string getAttrValueAsUserLogin(const std::string &attrName) const throw(SG::SgError);
    static const std::string getAttrValueAsUserLogin(SG::Shotgun *sg,
                                                     const std::string &attrName,
                                                     const SG::Dict &attrsMap) throw(SG::SgError);

    // ------------------------------------------------------------------------
    virtual const std::string getAttrValueAsQtURL(const std::string &attrName) const throw(SG::SgError);
    static const std::string getAttrValueAsQtURL(const std::string &attrName,
                                                 const SG::Dict &attrsMap) throw(SG::SgError);

    // ------------------------------------------------------------------------
    virtual const std::string getAttrValueAsQtPath(const std::string &attrName,
                                                   const std::string &sgAttachmentURL) const throw(SG::SgError);
    static const std::string getAttrValueAsQtPath(const std::string &attrName,
                                                  const std::string &sgAttachmentURL,
                                                  const SG::Dict &attrsMap) throw(SG::SgError);

    // ------------------------------------------------------------------------
    virtual void setAttrValue(const SG::Fields &fields) throw(SG::SgError); 

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

protected:
    // ------------------------------------------------------------------------
    // Even if this ctor is protected, it shoule be put here to prevent a
    // default public ctor being generated. See the complex example in the
    // "SIP reference guide".
    //
    //     http://www.riverbankcomputing.co.uk/static/Docs/sip4/index.html
    // ------------------------------------------------------------------------

    Entity(SG::Shotgun *sg);
};

// *****************************************************************************
typedef std::vector<SG::Entity *> EntityPtrs;

}; // End namespace SG - IMPORTANT: has to have the semi-colon
