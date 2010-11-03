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

#ifndef __SITEREFERENCE_H__
#define __SITEREFERENCE_H__

#include <Shotgun/CustomEntity.h>

namespace SiteSG {

// *****************************************************************************
/// \class SiteReference
/// This is an example on how to derive from one of the basic Shotgun entity 
/// classes. It differs from any of the basic Shotgun entity classes in that 
/// it needs to be registered separately before use. All the basic Shotgun 
/// entity classes defined in this library will be registered when an instance 
/// of the Shotgun class object is created.
class SiteReference : public SG::CustomEntity02
{
    friend class SiteShotgun;
 
public:
    // -------------------------------------------------------------------------
    /// A copy constructor.
    SiteReference(const SiteReference &ref);

    /// A destructor that does nothing.
    virtual ~SiteReference();

    // -------------------------------------------------------------------------
    /// The string representation of SiteReference entity type.
    static std::string entityType() { return SG::CustomEntity02::getEntityType(); }

    /// The string representation of SiteReference class type.
    static std::string classType() { return std::string("SiteReference"); }

    // -------------------------------------------------------------------------
    /// Returns the namespace of the class. It is needed in SIP-wrapped python to
    /// correctly downcast to sub-class.
    virtual const std::string namespaceStr() const { return std::string("SiteSG"); }

    // -------------------------------------------------------------------------
    /// These are site-specific convenience functions
    virtual const std::string sgCode() const { return getAttrValueAsString("code"); }

    // -------------------------------------------------------------------------
    SiteReference &operator=(const SiteReference &that)
    {
        if (this != &that)
        {
            SG::CustomEntity02::operator=(that);
        }

        return *this;
    }

    // -------------------------------------------------------------------------
    friend std::ostream& operator<<(std::ostream &output, const SiteReference &siteReference)
    {
        output << siteReference.str();
        return output;
    }

protected:
    // -------------------------------------------------------------------------
    /// A constructor.
    ///
    /// \param sg - instantiated Shotgun object pointer
    /// \param attrs - raw attribute map for a Shotgun entity
    SiteReference(SG::Shotgun *sg, const xmlrpc_c::value &attrs);

    // -------------------------------------------------------------------------
    /// A SiteReference entity factory function.
    ///
    /// \param sg - instantiated Shotgun object pointer
    /// \param attrs - raw attribute map for a Shotgun entity
    /// \return a newly-created SiteReference * as its base Entity * type
    static SG::Entity *factory(SG::Shotgun *sg, const xmlrpc_c::value &attrs) { return new SiteReference(sg, attrs); }

    // -------------------------------------------------------------------------
    /// Builds a list of default "return_fields" which are the attributes
    /// exposed to the users when a SiteReference entity is created or searched.
    ///
    /// \return a list of default "return_fields" name strings
    static SG::List defaultReturnFields();
};

// *****************************************************************************
typedef std::vector<SiteReference *> SiteReferencePtrs;

} // End namespace SiteSG

#endif    // End #ifdef __SITEREFERENCE_H__
