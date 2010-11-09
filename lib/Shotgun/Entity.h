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

#ifndef __SG_ENTITY_H__
#define __SG_ENTITY_H__

#include <iostream>
#include <string>

#include <Shotgun/types.h>
#include <Shotgun/exceptions.h>
#include <Shotgun/Method.h>
#include <Shotgun/FilterBy.h>
#include <Shotgun/SortBy.h>
#include <Shotgun/List.h>
#include <Shotgun/Dict.h>
#include <Shotgun/Fields.h>

namespace SG {

class Shotgun;
class TaskMixin;
class NoteMixin;

// *****************************************************************************
/// \class Entity
class Entity
{
public:
    // -------------------------------------------------------------------------
    /// A destructor that deletes the entity's raw attribute map which is of 
    /// (xmlrpc_c::value *) type.
    virtual ~Entity();

    // -------------------------------------------------------------------------
    /// Returns the Shotgun class instance.
    const Shotgun *sg() const { return m_sg; }
    Shotgun *sg() { return m_sg; }

    // -------------------------------------------------------------------------
    // These are the few common attributes shared by all entities
    
    /// Returns an entity's id.
    virtual const int sgId() const { return getAttrValueAsInt("id"); }

    /// Returns the UTC time when the entity was created.
    virtual const time_t sgDateCreated() const { return getAttrValueAsUTCtime("created_at"); }

    /// Returns the UTC time when the entity was last updated.
    virtual const time_t sgDateUpdated() const { return getAttrValueAsUTCtime("updated_at"); }

    /// Returns the project name associated with the current entity. It will be
    /// reimplemented for the Project entity.
    virtual const std::string sgProjectName() const { return getProjectName(); }

    /// Returns the project code associated with the current entity. It will be
    /// reimplemented for the Project entity.
    virtual const std::string sgProjectCode() const { return getProjectCode(); }

    // -------------------------------------------------------------------------
    /// Returns the string representation of the entity type.
    const std::string entityType() const { return m_entityType; }

    // -------------------------------------------------------------------------
    /// Returns the string representation of the entity class type.
    const std::string classType() const { return m_classType; }

    /// Returns the de-referenced entity's raw attribute map.
    const xmlrpc_c::value &attrs() const { return *m_attrs; }

    /// Returns the string representation of the entity.
    const std::string str() const { return toStdString(*m_attrs); }

    /// Returns the namespace of the class. It is needed in SIP-wrapped python to 
    /// correctly downcast to sub-class.
    virtual const std::string namespaceStr() const { return std::string("SG"); }

    // -------------------------------------------------------------------------
    /*!
     This returns a mini link of the entity. It looks like this:

     \htmlonly
     <br>
     <pre>
         { <br>
             "type" : "Project",<br>
             "id" : 68,<br>
         }
     </pre>
     \endhtmlonly
    */
    const Dict asLink() const;

    // -------------------------------------------------------------------------
    /// If an entity has a link attribute, this returns the entity type of the link.
    const std::string linkEntityType(const std::string &linkName) const;
    
    // -------------------------------------------------------------------------
    /// Gets an attribute's value. It returns as a generic xmlrpc_c::value type.
    /// It checks the entity's raw attribute map first. If the attribute exists,
    /// returns its value. Otherwise, do a fresh search in Shotgun and try to
    /// fetch the value directly from Shotgun.
    virtual const xmlrpc_c::value getAttrValue(const std::string &attrName) const;

    /// Gets an attribute's value from a given attribute map and returns the 
    /// result as a generic xmlrpc_c::value type.
    static const xmlrpc_c::value getAttrValue(const std::string &attrName, 
                                              const Dict &attrsMap);

    // -------------------------------------------------------------------------
    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as an integer. If it fails, throw an exception.
    virtual const int getAttrValueAsInt(const std::string &attrName) const;

    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as an integer. If it fails, use the given default value.
    virtual const int getAttrValueAsInt(const std::string &attrName, 
                                        const int defaultVal) const; 

    /// Gets an attribute's value from the given attribute map and returns
    /// as an integer. If it fails, throw an exception.
    static const int getAttrValueAsInt(const std::string &attrName, 
                                       const Dict &attrsMap);

    /// Gets an attribute's value from the given attribute map and returns
    /// as an integer. If it fails, use the given default value.
    static const int getAttrValueAsInt(const std::string &attrName, 
                                       const Dict &attrsMap,
                                       const int defaultVal); 

    // -------------------------------------------------------------------------
    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a boolean type. If it fails, throw an exception.
    virtual const bool getAttrValueAsBool(const std::string &attrName) const; 

    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a boolean type. If it fails, use the given default value.
    virtual const bool getAttrValueAsBool(const std::string &attrName, 
                                          const bool defaultVal) const; 

    /// Gets an attribute's value from the given attribute map and returns
    /// as a boolean type. If it fails, throw an exception.
    static const bool getAttrValueAsBool(const std::string &attrName, 
                                         const Dict &attrsMap);

    /// Gets an attribute's value from the given attribute map and returns
    /// as a boolean type. If it fails, use the given default value.
    static const bool getAttrValueAsBool(const std::string &attrName, 
                                         const Dict &attrsMap,
                                         const bool defaultVal); 

    // -------------------------------------------------------------------------
    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a double. If it fails, throw an exception.
    virtual const double getAttrValueAsDouble(const std::string &attrName) const;

    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a double. If it fails, use the given default value.
    virtual const double getAttrValueAsDouble(const std::string &attrName, 
                                              const double defaultVal) const; 

    /// Gets an attribute's value from the given attribute map and returns
    /// as a double. If it fails, throw an exception.
    static const double getAttrValueAsDouble(const std::string &attrName, 
                                             const Dict &attrsMap);

    /// Gets an attribute's value from the given attribute map and returns
    /// as a double. If it fails, use the given default value.
    static const double getAttrValueAsDouble(const std::string &attrName, 
                                             const Dict &attrsMap,
                                             const double defaultVal);

    // -------------------------------------------------------------------------
    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a time_t type (UTC time). If it fails, throw an exception.
    virtual const time_t getAttrValueAsUTCtime(const std::string &attrName) const;

    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a time_t type (UTC time). If it fails, use the given default value.
    virtual const time_t getAttrValueAsUTCtime(const std::string &attrName, 
                                               const time_t defaultVal) const;

    /// Gets an attribute's value from the given attribute map and returns
    /// as a time_t type (UTC time). If it fails, throw an exception.
    static const time_t getAttrValueAsUTCtime(const std::string &attrName, 
                                              const Dict &attrsMap);

    /// Gets an attribute's value from the given attribute map and returns
    /// as a time_t type (UTC time). If it fails, use the given default value.
    static const time_t getAttrValueAsUTCtime(const std::string &attrName, 
                                              const Dict &attrsMap,
                                              const time_t defaultVal);

    // -------------------------------------------------------------------------
    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a struct tm type (local time). If it fails, throw an exception.
    virtual const struct tm getAttrValueAsLocaltime(const std::string &attrName) const;

    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a struct tm type (local time). If it fails, use the given default value.
    virtual const struct tm getAttrValueAsLocaltime(const std::string &attrName, 
                                                    const struct tm &defaultVal) const;

    /// Gets an attribute's value from the given attribute map and returns
    /// as a struct tm type (local time). If it fails, throw an exception.
    static const struct tm getAttrValueAsLocaltime(const std::string &attrName, 
                                                   const Dict &attrsMap);

    /// Gets an attribute's value from the given attribute map and returns
    /// as a struct tm type (local time). If it fails, use the given default value.
    static const struct tm getAttrValueAsLocaltime(const std::string &attrName, 
                                                   const Dict &attrsMap,
                                                   const struct tm &defaultVal);

    // -------------------------------------------------------------------------
    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a string. If it fails, throw an exception.
    virtual const std::string getAttrValueAsString(const std::string &attrName) const;

    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a string. If it fails, use the given default value.
    virtual const std::string getAttrValueAsString(const std::string &attrName, 
                                                   const std::string &defaultVal) const;

    /// Gets an attribute's value from the given attribute map and returns
    /// as a string. If it fails, throw an exception.
    static const std::string getAttrValueAsString(const std::string &attrName, 
                                                  const Dict &attrsMap);

    /// Gets an attribute's value from the given attribute map and returns
    /// as a string. If it fails, use the given default value.
    static const std::string getAttrValueAsString(const std::string &attrName, 
                                                  const Dict &attrsMap,
                                                  const std::string &defaultVal);

    // -------------------------------------------------------------------------
    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a List type. If it fails, throw an exception.
    virtual const List getAttrValueAsList(const std::string &attrName) const; 

    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a List type. If it fails, use the given default value.
    virtual const List getAttrValueAsList(const std::string &attrName, 
                                          const List &defaultVal) const;

    /// Gets an attribute's value from the given attribute map and returns
    /// as a List type. If it fails, throw an exception.
    static const List getAttrValueAsList(const std::string &attrName, 
                                         const Dict &attrsMap);

    /// Gets an attribute's value from the given attribute map and returns
    /// as a List type. If it fails, use the given default value.
    static const List getAttrValueAsList(const std::string &attrName, 
                                         const Dict &attrsMap,
                                         const List &defaultVal);

    // -------------------------------------------------------------------------
    // This member function can't take a default value because it has the same 
    // type as the attrsMap, and therefore creates an ambiguous overload.
    //virtual const Dict getAttrValueAsDict(const std::string &attrName, 
    //                                      const Dict &defaultVal) const;

    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a Dict type. If it fails, use the given default value.
    virtual const Dict getAttrValueAsDict(const std::string &attrName) const;

    /// Gets an attribute's value from the given attribute map and returns
    /// as a Dict type. If it fails, throw an exception.
    static const Dict getAttrValueAsDict(const std::string &attrName, 
                                         const Dict &attrsMap);

    /// Gets an attribute's value from the given attribute map and returns
    /// as a Dict type. If it fails, use the given default value.
    static const Dict getAttrValueAsDict(const std::string &attrName, 
                                         const Dict &attrsMap,
                                         const Dict &defaultVal);

    // -------------------------------------------------------------------------
    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as an array of tag strings. The size of the result can be zero.
    virtual const Strings getAttrValueAsTags(const std::string &attrName) const;

    /// Gets an attribute's value from the given attribute map and returns
    /// as an array of tag strings. The size of the result can be zero.
    static const Strings getAttrValueAsTags(const std::string &attrName,
                                            const Dict &attrsMap);

    // -------------------------------------------------------------------------
    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a Shotgun Entity *. If it fails, throw an exception.
    virtual const Entity *getAttrValueAsEntity(const std::string &attrName) const;

    /// Gets an attribute's value from the given attribute map and returns
    /// as a Shotgun Entity *. If it fails, throw an exception.
    static const Entity *getAttrValueAsEntity(Shotgun *sg,
                                              const std::string &attrName,
                                              const Dict &attrsMap);

    /// A template function that gets an attribute's value from the entity's 
    /// raw attribute map and returns as a derived Shotgun entity pointer. 
    /// If it fails, throw an exception.
    template <class T>
    const T *getAttrValueAsEntity(const std::string &attrName) const;

    /// A template function that gets an attribute's value from the given
    /// attribute map and returns as a derived Shotgun entity pointer. 
    /// If it fails, throw an exception.
    template <class T>
    static const T *getAttrValueAsEntity(Shotgun *sg,
                                         const std::string &attrName,
                                         const Dict &attrsMap);

    // -------------------------------------------------------------------------
    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as an array of Shotgun Entity *. The size of the result can be zero.
    virtual const std::vector<Entity *> getAttrValueAsEntities(const std::string &attrName) const;

    /// Gets an attribute's value from the given attribute map and returns
    /// as an array of Shotgun Entity *. The size of the result can be zero.
    static const std::vector<Entity *> getAttrValueAsEntities(Shotgun *sg,
                                                              const std::string &attrName,
                                                              const Dict &attrsMap);

    /// A template function that gets an attribute's value from the entity's 
    /// raw attribute map and returns as an array of derived Shotgun entity 
    /// pointer. If it fails, throw an exception.
    template <class T>
    const std::vector<T *> getAttrValueAsEntities(const std::string &attrName) const;

    /// A template function that gets an attribute's value from the given
    /// attribute map and returns as an array of derived Shotgun entity 
    /// pointer. If it fails, throw an exception.
    template <class T>
    static const std::vector<T *> getAttrValueAsEntities(Shotgun *sg,
                                                         const std::string &attrName,
                                                         const Dict &attrsMap);

    // -------------------------------------------------------------------------
    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a user login string. If it fails, throw an exception.
    virtual const std::string getAttrValueAsUserLogin(const std::string &attrName) const;

    /// Gets an attribute's value from the given attribute map and returns
    /// as a user login string. If it fails, throw an exception.
    static const std::string getAttrValueAsUserLogin(Shotgun *sg,
                                                     const std::string &attrName,
                                                     const Dict &attrsMap);

    // -------------------------------------------------------------------------
    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a quicktime URL. If it fails, throw an exception.
    virtual const std::string getAttrValueAsQtURL(const std::string &attrName) const;

    /// Gets an attribute's value from the given attribute map and returns
    /// as a quicktime URL. If it fails, throw an exception.
    static const std::string getAttrValueAsQtURL(const std::string &attrName,
                                                 const Dict &attrsMap);

    // -------------------------------------------------------------------------
    /// Gets an attribute's value from the entity's raw attribute map and returns
    /// as a quicktime path. If it fails, throw an exception.
    virtual const std::string getAttrValueAsQtPath(const std::string &attrName,
                                                   const std::string &sgAttachmentURL) const;

    /// Gets an attribute's value from the given attribute map and returns
    /// as a quicktime path. If it fails, throw an exception.
    static const std::string getAttrValueAsQtPath(const std::string &attrName,
                                                  const std::string &sgAttachmentURL,
                                                  const Dict &attrsMap);

    // -------------------------------------------------------------------------
    /// Updates an entity's attribute(s) by the given "fields" data.
    virtual void setAttrValue(const Fields &fields); 

    // -------------------------------------------------------------------------
    Entity &operator=(const Entity &that)
    {
        if (this != &that)
        {
            m_sg = that.m_sg;
            m_entityType = that.m_entityType;
            m_classType = that.m_classType;

            delete m_attrs;
            m_attrs = new xmlrpc_c::value(*(that.m_attrs));
        }

        return *this;
    }

protected:
    // -------------------------------------------------------------------------
    /// A constructor that sets the entity's raw attribute map pointer to NULL.
    Entity(Shotgun *sg);

    // -------------------------------------------------------------------------
    /// Creates a new Shotgun entity by the given data map and returns the
    /// result as raw xmlrpc_c::value struct.
    static xmlrpc_c::value createSGEntity(Shotgun *sg, const Dict &createMap);

    /// Finds a list of Shotgun entities that match the search map. Each of
    /// the entity is as raw xmlrpc_c::value struct.
    static List findSGEntities(Shotgun *sg, 
                               Dict &findMap,
                               const int limit = 0);

    /// Updates the attribute(s) of an existing Shotgun entity and returns the
    /// updated entity as raw xmlrpc_c::value struct.
    static xmlrpc_c::value updateSGEntity(Shotgun *sg,
                                          const std::string &entityType,
                                          const int entityId,
                                          const Fields &fieldsToUpdate);

    /// Deletes an existing Shotgun entity
    static bool deleteSGEntity(Shotgun *sg, 
                               const std::string &entityType,
                               const int entityId);

    // -------------------------------------------------------------------------
    /// Builds a data map for creating a new Shotgun entity
    static Dict buildCreateMap(const Dict &data,
                               const List &extraReturnFields = List());

    /// Build a filter map for finding one or more Shotgun entities
    static Dict buildFindMap(const FilterBy &filterList = FilterBy(),
                             const List &extraReturnFields = List(),
                             const bool retiredOnly = false,
                             const int limit = 0,
                             const SortBy &order = SortBy());

    // -------------------------------------------------------------------------
    /// A template function that gets the value for a given attribute and
    /// returns as a specified type. If the attribute is not found in the
    /// entity's raw attribute map, fetch its value directly from Shotgun.
    /// If it fails, an exception will be thrown.
    template <typename T>
    const T getAttrValue(const std::string &attrName) const;

    /// A template function that gets the value for a given attribute and
    /// returns as a specified type. If the attribute is not found in the
    /// entity's raw attribute map, fetch its value directly from Shotgun.
    /// If it fails, the given default value will be used.
    template <typename T>
    const T getAttrValue(const std::string &attrName,
                         const T defaultVal) const;

    /// A template function that gets the value for a given attribute from 
    /// the given attribute map. If it fails, an exception will be thrown.
    template <typename T>
    static const T getAttrValue(const std::string &attrName,
                                const Dict &attrsMap);

    /// A template function that gets the value for a given attribute from 
    /// the given attribute map. If it fails, the given default value will 
    /// be used.
    template <typename T>
    static const T getAttrValue(const std::string &attrName,
                                const Dict &attrsMap,
                                const T defaultVal);

    // -------------------------------------------------------------------------
    /// The result of a method call is a struct. This convenience function 
    /// is to extract a list of raw Shotgun entities from the result struct.
    static List getFindResultEntityList(xmlrpc_c::value &rawResult);

    /// This convenience function gets the paging info from the raw result 
    /// of the method calls
    static Dict getResultPagingInfo(xmlrpc_c::value &rawResult);

    /// Validate an entity link and see if it contains the required fields, 
    /// such as "type", "id".
    static void validateLink(const Dict &link);

    // -------------------------------------------------------------------------
    /// Convenience function for getting the project's name of the entity.
    const std::string getProjectName() const;

    /// Convenience function for getting the project's code of the entity.
    const std::string getProjectCode() const;

protected:
    Shotgun *m_sg; ///< The instantiated Shotgun class object.
    std::string m_entityType; ///< The string representation of the entity type.
    std::string m_classType; ///< The string representation of the entity class type.

    // This has to be an pointer since xmlrpc_c::value will not allow the
    // assignment of an already-instantiated xmlrpc_c::value. For details,
    // see: http://xmlrpc-c.sourceforge.net/doc/libxmlrpc++.html
    xmlrpc_c::value *m_attrs;
};

// *****************************************************************************
template <typename T>
const T Entity::getAttrValue(const std::string &attrName) const
{
    T result;

    xmlrpc_c::value genericResult = getAttrValue(attrName);

    try
    {
        fromXmlrpcValue(genericResult, result);
    }
    catch (SgXmlrpcValueTypeError &error)
    {
        throw SgAttrTypeError(attrName,
                              error.what());
    }

    return result;
}

// *****************************************************************************
template <typename T>
const T Entity::getAttrValue(const std::string &attrName,
                             const T defaultVal) const
{
    T result;

    xmlrpc_c::value genericResult = getAttrValue(attrName);

    try
    {
        fromXmlrpcValue(genericResult, result);
    }
    catch (SgXmlrpcValueTypeError &error)
    {
        result = defaultVal;
    }

    return result;
}

// *****************************************************************************
template <typename T>
const T Entity::getAttrValue(const std::string &attrName,
                             const Dict &attrsMap)
{
    T result;

    xmlrpc_c::value genericResult = getAttrValue(attrName, attrsMap);

    try
    {
        fromXmlrpcValue(genericResult, result);
    }
    catch (SgXmlrpcValueTypeError &error)
    {
        throw SgAttrTypeError(attrName,
                              error.what());
    }

    return result;
}

// *****************************************************************************
template <typename T>
const T Entity::getAttrValue(const std::string &attrName,
                             const Dict &attrsMap,
                             const T defaultVal)
{
    T result;

    xmlrpc_c::value genericResult = getAttrValue(attrName, attrsMap);

    try
    {
        fromXmlrpcValue(genericResult, result);
    }
    catch (SgXmlrpcValueTypeError &error)
    {
        result = defaultVal;
    }

    return result;
}

// *****************************************************************************
template <class T>
const T *Entity::getAttrValueAsEntity(const std::string &attrName) const
{
    const Entity *entity = getAttrValueAsEntity(attrName);

    if (const T *t = dynamic_cast<const T *>(entity))
    {
        return t;
    }
    else
    {
        throw SgEntityDynamicCastError(T::classType());
    }
}

// *****************************************************************************
template <class T>
const T *Entity::getAttrValueAsEntity(Shotgun *sg,
                                      const std::string &attrName,
                                      const Dict &attrsMap)
{
    const Entity *entity = Entity::getAttrValueAsEntity(sg, attrName, attrsMap);

    if (const T *t = dynamic_cast<const T *>(entity))
    {
        return t;
    }
    else
    {
        throw SgEntityDynamicCastError(T::classType());
    }
}

// *****************************************************************************
template <class T>
const std::vector<T *> Entity::getAttrValueAsEntities(const std::string &attrName) const
{
    std::vector<Entity *> entities = getAttrValueAsEntities(attrName);
    std::vector<T *> entityTs;
    
    for (size_t i = 0; i < entities.size(); i++)
    {
        if (T *t = dynamic_cast<T *>(entities[i]))
        {
            entityTs.push_back(t);
        }
    }

    return entityTs;
}

// *****************************************************************************
template <class T>
const std::vector<T *> Entity::getAttrValueAsEntities(Shotgun *sg,
                                                      const std::string &attrName,
                                                      const Dict &attrsMap)
{
    std::vector<Entity *> entities = Entity::getAttrValueAsEntities(sg, attrName, attrsMap);
    std::vector<T *> entityTs;
    
    for (size_t i = 0; i < entities.size(); i++)
    {
        if (T *t = dynamic_cast<T *>(entities[i]))
        {
            entityTs.push_back(t);
        }
    }

    return entityTs;
}

// *****************************************************************************
typedef std::vector<Entity *> EntityPtrs;

} // End namespace SG

#endif    // End #ifdef __SG_ENTITY_H__
