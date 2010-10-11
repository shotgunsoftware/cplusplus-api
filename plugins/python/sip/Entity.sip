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

%ConvertToSubClassCode
    // Downcast to subclass
    if (sipCpp->entityType() == "Asset")
    {
        sipType = sipType_Shotgun_Asset;
    }
    else if (sipCpp->entityType() == "Delivery")
    {
        sipType = sipType_Shotgun_Delivery;
    }
    else if (sipCpp->entityType() == "Element")
    {
        sipType = sipType_Shotgun_Element;
    }
    else if (sipCpp->entityType() == "Group")
    {
        sipType = sipType_Shotgun_Group;
    }
    else if (sipCpp->entityType() == "HumanUser")
    {
        sipType = sipType_Shotgun_HumanUser;
    }
    else if (sipCpp->entityType() == "Note")
    {
        sipType = sipType_Shotgun_Note;
    }
    else if (sipCpp->entityType() == "Playlist")
    {
        sipType = sipType_Shotgun_Playlist;
    }
    else if (sipCpp->entityType() == "Project")
    {
        sipType = sipType_Shotgun_Project;
    }
    else if (sipCpp->entityType() == "PublishEvent")
    {
        sipType = sipType_Shotgun_PublishEvent;
    }
    else if (sipCpp->entityType() == "ReviewItem")
    {
        sipType = sipType_Shotgun_ReviewItem;
    }
    else if (sipCpp->entityType() == "Review")
    {
        sipType = sipType_Shotgun_Review;
    }
    else if (sipCpp->entityType() == "Sequence")
    {
        sipType = sipType_Shotgun_Sequence;
    }
    else if (sipCpp->entityType() == "Shot")
    {
        sipType = sipType_Shotgun_Shot;
    }
    else if (sipCpp->entityType() == "Task")
    {
        sipType = sipType_Shotgun_Task;
    }
    else if (sipCpp->entityType() == "Version")
    {
        sipType = sipType_Shotgun_Version;
    }
    else
    {
        sipType = sipType_Shotgun_Entity;
    }
%End

public:
    virtual ~Entity();

    // ------------------------------------------------------------------------
    // Can't have both in SIP
    //const Shotgun::Shotgun *sg() const;
    Shotgun::Shotgun *sg();

    // ------------------------------------------------------------------------
    virtual const int sgId() const throw(Shotgun::SgError);
    virtual const time_t sgDateCreated() const throw(Shotgun::SgError);
    virtual const time_t sgDateUpdated() const throw(Shotgun::SgError);
    virtual const std::string sgProjectName() const throw(Shotgun::SgError);
    virtual const std::string sgProjectCode() const throw(Shotgun::SgError);

    // ------------------------------------------------------------------------
    const std::string entityType() const;
    const xmlrpc_c::value &attrs() const;
    const std::string str() const;
    const Shotgun::Dict asLink() const;
    const std::string linkEntityType(const std::string &linkName) const;
    
    // ------------------------------------------------------------------------
    // Get a attribute's value as a generic xmlrpc_c::value type
    virtual const xmlrpc_c::value getAttrValue(const std::string &attrName) const throw(Shotgun::SgError);
    static const xmlrpc_c::value getAttrValue(const std::string &attrName, 
                                              const Shotgun::Dict &attrsMap) throw(Shotgun::SgError);

    // ------------------------------------------------------------------------
    virtual const Shotgun::Strings getAttrValueAsTags(const std::string &attrName) const throw(Shotgun::SgError);
    static const Shotgun::Strings getAttrValueAsTags(const std::string &attrName,
                                                     const Shotgun::Dict &attrsMap) throw(Shotgun::SgError);

    // ------------------------------------------------------------------------
    virtual const Shotgun::Entity *getAttrValueAsEntity(const std::string &attrName) const throw(Shotgun::SgError) /Factory/;
    static const Shotgun::Entity *getAttrValueAsEntity(Shotgun::Shotgun *sg,
                                                       const std::string &attrName,
                                                       const Shotgun::Dict &attrsMap) throw(Shotgun::SgError) /Factory/;

    // ------------------------------------------------------------------------
    virtual const Shotgun::EntityPtrs getAttrValueAsEntities(const std::string &attrName) const throw(Shotgun::SgError) /Factory/;
    static const Shotgun::EntityPtrs getAttrValueAsEntities(Shotgun::Shotgun *sg,
                                                            const std::string &attrName,
                                                            const Shotgun::Dict &attrsMap) throw(Shotgun::SgError) /Factory/;

    // ------------------------------------------------------------------------
    virtual const std::string getAttrValueAsUserLogin(const std::string &attrName) const throw(Shotgun::SgError);
    static const std::string getAttrValueAsUserLogin(Shotgun::Shotgun *sg,
                                                     const std::string &attrName,
                                                     const Shotgun::Dict &attrsMap) throw(Shotgun::SgError);

    // ------------------------------------------------------------------------
    virtual void setAttrValue(const Shotgun::Fields &fields) throw(Shotgun::SgError); 

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

    Entity(Shotgun::Shotgun *sg);
};

}; // End namespace Shotgun - IMPORTANT: has to have the semi-colon
