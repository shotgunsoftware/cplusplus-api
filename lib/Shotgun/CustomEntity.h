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

#ifndef __SG_CUSTOM_ENTITY_H__
#define __SG_CUSTOM_ENTITY_H__

#include <string>
#include <sstream>
#include <iomanip>

#include <Shotgun/config.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>

namespace SG {

// *****************************************************************************
/// \class template CustomEntity class
template <int ID>
class CustomEntity : public Entity
{
    friend class Shotgun;
 
public:
    // -------------------------------------------------------------------------
    /// A copy constructor.
    CustomEntity(const CustomEntity<ID> &ref);

    /// A destructor that does nothing.
    virtual ~CustomEntity();

    // -------------------------------------------------------------------------
    /// The string representation of CustomEntity<ID> entity type.
    static std::string entityType() { return getEntityType(); }

    /// The string representation of CustomEntity<ID> class type.
    static std::string classType() { return getEntityType(); }

    // -------------------------------------------------------------------------
    CustomEntity &operator=(const CustomEntity<ID> &that)
    {
        if (this != &that)
        {
            Entity::operator=(that);
        }

        return *this;
    }

    // -------------------------------------------------------------------------
    friend std::ostream& operator<<(std::ostream &output, const CustomEntity<ID> &t)
    {
        output << t.str();
        return output;
    }

protected:
    // -------------------------------------------------------------------------
    /// A constructor.
    ///
    /// \param sg - instantiated Shotgun object pointer
    /// \param attrs - raw attribute map for a Shotgun entity
    CustomEntity(Shotgun *sg, const Json::Value &attrs);

    // -------------------------------------------------------------------------
    /// A CustomEntity<ID> entity factory function. 
    ///
    /// \param sg - instantiated Shotgun object pointer
    /// \param attrs - raw attribute map for a Shotgun entity
    /// \return a newly-created CustomEntity<ID> * as its base Entity * type
    static Entity *factory(Shotgun *sg, const Json::Value &attrs);

    // -------------------------------------------------------------------------
    /// Builds a list of default "return_fields" which are the attributes 
    /// exposed to the users when a CustomEntity<ID> entity is created or searched.
    ///
    /// \return a list of default "return_fields" name strings.
    static List defaultReturnFields();

    // -------------------------------------------------------------------------
    /// The string representation of CustomEntity<ID> entity type.
    static std::string getEntityType();
};

// *****************************************************************************
template <int ID>
CustomEntity<ID>::CustomEntity(Shotgun *sg, const Json::Value &attrs)
    : Entity(sg)
{
    m_entityType = m_classType = CustomEntity<ID>::getEntityType();

	if (!attrs.isNull())
    {
        m_attrs = new Json::Value(attrs);
    }
}

// *****************************************************************************
template <int ID>
CustomEntity<ID>::CustomEntity(const CustomEntity<ID> &ref)
    : Entity(ref.m_sg)
{
    m_entityType = m_classType = CustomEntity<ID>::getEntityType();
    m_attrs = new Json::Value(*ref.m_attrs);
}

// *****************************************************************************
template <int ID>
CustomEntity<ID>::~CustomEntity()
{
    // Nothing
}

// *****************************************************************************
template <int ID>
Entity *CustomEntity<ID>::factory(Shotgun *sg, const Json::Value &attrs) 
{ 
    return new CustomEntity<ID>(sg, attrs); 
}

// *****************************************************************************
template <int ID>
List CustomEntity<ID>::defaultReturnFields()
{
    return List("id")
           .append("project")
           .append("created_at")
           .append("updated_at")
           .append("code");
}

// *****************************************************************************
template <int ID>
std::string CustomEntity<ID>::getEntityType()
{
    std::ostringstream nameStream;
    nameStream << "CustomEntity" << std::setfill('0') << std::setw(2) << ID;
    return nameStream.str(); 
}

// *****************************************************************************
// These are the CustomEntity types currently available in Shotgun.
typedef CustomEntity<1> CustomEntity01;
typedef CustomEntity<2> CustomEntity02;
typedef CustomEntity<3> CustomEntity03;
typedef CustomEntity<4> CustomEntity04;
typedef CustomEntity<5> CustomEntity05;
typedef CustomEntity<6> CustomEntity06;
typedef CustomEntity<7> CustomEntity07;
typedef CustomEntity<8> CustomEntity08;
typedef CustomEntity<9> CustomEntity09;
typedef CustomEntity<10> CustomEntity10;
typedef CustomEntity<11> CustomEntity11;
typedef CustomEntity<12> CustomEntity12;
typedef CustomEntity<13> CustomEntity13;
typedef CustomEntity<14> CustomEntity14;
typedef CustomEntity<15> CustomEntity15;
typedef CustomEntity<16> CustomEntity16;
typedef CustomEntity<17> CustomEntity17;
typedef CustomEntity<18> CustomEntity18;
typedef CustomEntity<19> CustomEntity19;
typedef CustomEntity<20> CustomEntity20;

// *****************************************************************************
typedef std::vector<CustomEntity01 *> CustomEntity01Ptrs;
typedef std::vector<CustomEntity02 *> CustomEntity02Ptrs;
typedef std::vector<CustomEntity03 *> CustomEntity03Ptrs;
typedef std::vector<CustomEntity04 *> CustomEntity04Ptrs;
typedef std::vector<CustomEntity05 *> CustomEntity05Ptrs;
typedef std::vector<CustomEntity06 *> CustomEntity06Ptrs;
typedef std::vector<CustomEntity07 *> CustomEntity07Ptrs;
typedef std::vector<CustomEntity08 *> CustomEntity08Ptrs;
typedef std::vector<CustomEntity09 *> CustomEntity09Ptrs;
typedef std::vector<CustomEntity10 *> CustomEntity10Ptrs;
typedef std::vector<CustomEntity11 *> CustomEntity11Ptrs;
typedef std::vector<CustomEntity12 *> CustomEntity12Ptrs;
typedef std::vector<CustomEntity13 *> CustomEntity13Ptrs;
typedef std::vector<CustomEntity14 *> CustomEntity14Ptrs;
typedef std::vector<CustomEntity15 *> CustomEntity15Ptrs;
typedef std::vector<CustomEntity16 *> CustomEntity16Ptrs;
typedef std::vector<CustomEntity17 *> CustomEntity17Ptrs;
typedef std::vector<CustomEntity18 *> CustomEntity18Ptrs;
typedef std::vector<CustomEntity19 *> CustomEntity19Ptrs;
typedef std::vector<CustomEntity20 *> CustomEntity20Ptrs;

} // End namespace SG

#endif    // End #ifdef __SG_CUSTOM_ENTITY_H__
