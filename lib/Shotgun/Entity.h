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

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <iostream>
#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/FilterBy.h>
#include <Shotgun/SortBy.h>
#include <Shotgun/Method.h>

namespace Shotgun {

class Shotgun;
class TaskMixin;
class NoteMixin;

// *****************************************************************************
class Entity
{
    friend class TaskMixin;
    friend class NoteMixin;

public:
    virtual ~Entity();

    enum InvalidAttrMode
    {
        INVALID_ATTR_THROW_EXCEPTION = 0,
        INVALID_ATTR_USE_DEFAULT
    };

#warning This needs to be re-done.  There are NO attributes that are common to ALL entities!
    // These are the generic entity attributes shared by all entities
    virtual const int sgId() const { return getAttrValueAsInt("id"); }
    virtual const time_t sgDateCreated() const { return getAttrValueAsDatetime("created_at"); }
    virtual const time_t sgDateUpdated() const { return getAttrValueAsDatetime("updated_at"); }

    // These two have to be overridden for Project entity
    virtual const std::string sgProjectName() const { return getProjectName(); }
    virtual const std::string sgProjectCode() const { return getProjectCode(); }
    // Has to define a virtual sgName() here since it's called within sgLink().
    virtual const std::string sgName() const { return std::string(""); }

    const Shotgun *sg() const { return m_sg; }
    Shotgun *sg() { return m_sg; }

    void setInvalidAttrMode(InvalidAttrMode mode) { m_invalidAttrMode = mode; }
    const InvalidAttrMode getInvalidAttrMode() const { return m_invalidAttrMode; }
    void printAttrs() const;
    const std::string entityType() const { return m_type; }
    const xmlrpc_c::value &attrs() const { return *m_attrs; }
    const std::string str() const { return toStdString(*m_attrs); }
    const SgMap asLink() const;

    // If an entity has a link attribute, this returns the entity type 
    // of the link.
    const std::string linkEntityType(const std::string &linkName) const;
    
    // Get a attribute's value of a generic data type
    virtual const xmlrpc_c::value getAttrValue(const std::string &attrName) const;
    static const xmlrpc_c::value getAttrValue(const std::string &attrName, 
                                              const SgMap &attrsMap);

    // Get a attribute's value of a specific data type
    virtual const int getAttrValueAsInt(const std::string &attrName, 
                                        const int defaultVal = 0) const; 
    static const int getAttrValueAsInt(const std::string &attrName, 
                                       const SgMap &attrsMap,
                                       const int defaultVal = 0, 
                                       const InvalidAttrMode invalidAttrMode = INVALID_ATTR_THROW_EXCEPTION);

    virtual const bool getAttrValueAsBool(const std::string &attrName, 
                                          const bool defaultVal = false) const; 
    static const bool getAttrValueAsBool(const std::string &attrName, 
                                         const SgMap &attrsMap,
                                         const bool defaultVal = false, 
                                         const InvalidAttrMode invalidAttrMode = INVALID_ATTR_THROW_EXCEPTION);

    virtual const double getAttrValueAsDouble(const std::string &attrName, 
                                              const double defaultVal = 0.0) const; 
    static const double getAttrValueAsDouble(const std::string &attrName, 
                                             const SgMap &attrsMap,
                                             const double defaultVal = 0.0, 
                                             const InvalidAttrMode invalidAttrMode = INVALID_ATTR_THROW_EXCEPTION);

    virtual const time_t getAttrValueAsDatetime(const std::string &attrName, 
                                                const time_t defaultVal = 0) const;
    static const time_t getAttrValueAsDatetime(const std::string &attrName, 
                                               const SgMap &attrsMap,
                                               const time_t defaultVal = 0, 
                                               const InvalidAttrMode invalidAttrMode = INVALID_ATTR_THROW_EXCEPTION);

    virtual const std::string getAttrValueAsString(const std::string &attrName, 
                                                   const std::string &defaultVal = "") const;
    static const std::string getAttrValueAsString(const std::string &attrName, 
                                                  const SgMap &attrsMap,
                                                  const std::string &defaultVal = "", 
                                                  const InvalidAttrMode invalidAttrMode = INVALID_ATTR_THROW_EXCEPTION);

    virtual const SgArray getAttrValueAsArray(const std::string &attrName, 
                                              const SgArray &defaultVal = SgArray()) const;
    static const SgArray getAttrValueAsArray(const std::string &attrName, 
                                             const SgMap &attrsMap,
                                             const SgArray &defaultVal = SgArray(), 
                                             const InvalidAttrMode invalidAttrMode = INVALID_ATTR_THROW_EXCEPTION);

    // This member function can't take a default value because it has the same 
    // type as the attrsMap, and therefore creates an ambiguous overload.
    //const SgMap getAttrValueAsMap(const std::string &attrName, 
    //                              const SgMap &defaultVal = SgMap()) const;
    virtual const SgMap getAttrValueAsMap(const std::string &attrName) const;
    static const SgMap getAttrValueAsMap(const std::string &attrName, 
                                         const SgMap &attrsMap,
                                         const SgMap &defaultVal = SgMap(), 
                                         const InvalidAttrMode invalidAttrMode = INVALID_ATTR_THROW_EXCEPTION);

    virtual const Strings getAttrValueAsTags(const std::string &attrName) const;
    static const Strings getAttrValueAsTags(const std::string &attrName,
                                            const SgMap &attrsMap);

    virtual const Entity *getAttrValueAsEntityPtr(const std::string &attrName) const;
    static const Entity *getAttrValueAsEntityPtr(Shotgun *sg,
                                                 const std::string &attrName,
                                                 const SgMap &attrsMap);

    virtual const EntityPtrs getAttrValueAsMultiEntityPtr(const std::string &attrName) const;
    static const EntityPtrs getAttrValueAsMultiEntityPtr(Shotgun *sg,
                                                   const std::string &attrName,
                                                   const SgMap &attrsMap);

    virtual const std::string getAttrValueAsUserLogin(const std::string &attrName) const;
    static const std::string getAttrValueAsUserLogin(Shotgun *sg,
                                                     const std::string &attrName,
                                                     const SgMap &attrsMap);

    // Set a attribute's value - Omitted the optional "parent_entity" for now
    virtual void setAttrValue(const std::string &attrName, 
                              const xmlrpc_c::value &attrValue,
                              const SgArray &multiValues = SgArray());
    virtual void setAttrValue(const SgMap &attrPairs); 

    // TODO: Explore making this operator overload virtual
    Entity &operator=(const Entity &that)
    {
        if (this != &that)
        {
            m_sg = that.m_sg;
            m_invalidAttrMode = that.m_invalidAttrMode;
            m_type = that.m_type;

            delete m_attrs;
            m_attrs = new xmlrpc_c::value(*(that.m_attrs));
        }

        return *this;
    }

protected:
    Entity(Shotgun *sg);

    // Create a new entity
#warning This should be obsoleted
    static xmlrpc_c::value createSGEntity(Shotgun *sg, 
                                          const std::string &entityType, 
                                          const SgMap &data);

    static xmlrpc_c::value createSGEntity(Shotgun *sg, const SgMap &createMap);

    // Update an attribute of an existing entity
    static xmlrpc_c::value updateSGEntity(Shotgun *sg,
                                          const std::string &entityType,
                                          const int entityId,
                                          const SgArray &fieldsToUpdate);

    // Find a list of entities that match the search map
    static SgArray findSGEntities(Shotgun *sg, SgMap &findMap);

    // Delete an existing entity
    static bool deleteSGEntity(Shotgun *sg, 
                               const std::string &entityType,
                               const int id);

#if 0
    static Dict buildCreateMap(const std::string &entityType,
                               const Dict &data,
                               const List &returnFields = List());
#endif

    static SgMap buildCreateMap(const std::string &entityType,
                                const SgMap &data,
                                const SgArray &returnFields = SgArray());

    static SgMap buildUpdateMap(const std::string &entityType,
                                const int entityId,
                                const SgArray &fieldsToUpdate);

    // Construct a search map based on the given data
    static SgMap buildFindMap(const std::string &entityType,
                              const FilterBy &filterList = FilterBy(), // Update .sip for the line
                              const SgArray &returnFields = SgArray(),
                              const bool retiredOnly = false,
                              const int limit = 0,
                              const SortBy &order = SortBy());

    // The result of the method call is a struct. This function is to extract 
    // a list of entities from the find result struct.
    static SgArray getFindResultEntityList(xmlrpc_c::value &rawResult);

    // Get the paging info from the raw result of the method calls
    static SgMap getResultPagingInfo(xmlrpc_c::value &rawResult);

    // Convert an entity's attr map of xmlrpc_c::value type to an Entity pointer type.
    // This is simply a helper function
//     static Entity *entityAttrMapToEntityPtr(Shotgun *sg,
//                                             const xmlrpc_c::value &entityAttrMap);

    // Validate a link map and see if it contains the required fields
    static void validateLink(const SgMap &link);
    static void validateLink(const xmlrpc_c::value &link);

    const std::string getProjectName() const;
    const std::string getProjectCode() const;

protected:
    Shotgun *m_sg; 
    InvalidAttrMode m_invalidAttrMode;
    std::string m_type;

    // This has to be an pointer since xmlrpc_c::value will not allow the
    // assignment of an already-instantiated xmlrpc_c::value. For details,
    // see: http://xmlrpc-c.sourceforge.net/doc/libxmlrpc++.html
    xmlrpc_c::value *m_attrs;
};

} // End namespace Shotgun

#endif    // End #ifdef __ENTITY_H__
