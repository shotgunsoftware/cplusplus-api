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

#ifndef __SG_SHOTGUN_H__
#define __SG_SHOTGUN_H__

#include <exception>
#include <string>
#include <utility>

#include <Shotgun/types.h>
#include <Shotgun/exceptions.h>
#include <Shotgun/FilterBy.h>
#include <Shotgun/SortBy.h>
#include <Shotgun/List.h>
#include <Shotgun/Dict.h>
#include <Shotgun/Method.h>
#include <Shotgun/Project.h>
#include <Shotgun/Sequence.h>
#include <Shotgun/Shot.h>
#include <Shotgun/Version.h>
#include <Shotgun/HumanUser.h>
#include <Shotgun/Element.h>
#include <Shotgun/Asset.h>
#include <Shotgun/Delivery.h>
#include <Shotgun/PublishEvent.h>
#include <Shotgun/Review.h>
#include <Shotgun/ReviewItem.h>
#include <Shotgun/Task.h>
#include <Shotgun/Group.h>
#include <Shotgun/Note.h>
#include <Shotgun/Playlist.h>
#include <Shotgun/CustomEntity.h>

namespace SG {

// *****************************************************************************
/// Defines a function pointer to a Shotgun entity's factory() function.
typedef Entity* (*FactoryFunc)(Shotgun *, const xmlrpc_c::value &);

/// Defines a function pointer to a Shotgun entity's defaultReturnFields() function.
typedef List (*DefaultReturnFieldsFunc) ();

/// Defines a struct container to hold the function pointers.
typedef struct 
{ 
    FactoryFunc factoryFunc;
    DefaultReturnFieldsFunc defaultReturnFieldsFunc;

} RegistryFuncs;

/// Defines the ClassRegistry which registers a Shotgun entity's type string
/// with a set of corresponding function pointers.
typedef std::map<std::string, RegistryFuncs> ClassRegistry;

// *****************************************************************************
class TaskMixin;
class NoteMixin;

// *****************************************************************************
/// \class Shotgun
/// A Shotgun class is the main drive of this library. It initiates the connection
/// with the Shotgun server. All access to Shotgun data must go through a Shotgun 
/// class object.
class Shotgun
{
public:
    // -------------------------------------------------------------------------
    /// A constructor that 
    ///    - creates a XML-RPC client pointer.
    ///    - sets authentication info.
    ///    - sets the correct "TZ" time zone environment variable.
    ///    - registers the entity classes.
    ///
    /// The default values for all 3 parameters can be set at the "configure" time.
    ///
    /// \param serverURL - server URL
    /// \param authName - authentication "script_name" which corresponds to 
    ///                   "Script Name" on the [Admin] > [Scripts] page.
    /// \param authKey - authentication "script_key" which corresponds to 
    ///                  "Application Key" on the [Admin] > [Scripts] page.
    ///
    Shotgun(const std::string &serverURL = SG_DEFAULT_URL,
            const std::string &authName = SG_AUTHENTICATION_NAME,
            const std::string &authKey = SG_AUTHENTICATION_KEY);

    /// A destructor that deletes the XML-RPC client pointer.
    virtual ~Shotgun();

    // -------------------------------------------------------------------------
    /// Returns the XML-RPC client pointer.
    xmlrpc_c::client_xml *client() const { return m_client; }

    /// Returns the server URL string.
    const std::string &serverURL() const { return m_serverURL; }

    /// Returns the authentication "script_name".
    const std::string &authName() const { return m_authName; }

    /// Returns the authentication "script_key".
    const std::string &authKey() const { return m_authKey; }

    /// Returns the authentication map which includes both "script_name" and
    /// "script_key".
    const Dict &authMap() const { return m_authMap; } 

    // -------------------------------------------------------------------------
    /// Creates a new instance of Method class object which corresponds to
    /// a Shotgun API function with the specified name.
    Method *method(const std::string &methodName) 
        { return new Method(this, methodName); }

    // -------------------------------------------------------------------------
    /// Registers a class with the specified type. It creates a class registry
    /// that maps a class' string type with its static factory() function and 
    /// static defaultReturnFields() function.
    void registerClass(const std::string &entityType,
                       const FactoryFunc &factoryFunc,
                       const DefaultReturnFieldsFunc &defaultReturnFieldsFunc);

    // -------------------------------------------------------------------------
    /*! 
     A template function that creates an instance of a Shotgun entity. Make sure 
     to delete the entity in your application. Here is an example:

     \htmlonly
     <br>
     <pre>
     Shotgun sg(); <br>
     Project *project = sg.createEntity&lt;Project&gt;(Dict("name", "TEST PROJECT") <br>
                                                 .add("code", "tp")); <br>
     std::cout << project << std::endl; <br>
     ... // Do whatever with the project <br>
     delete project;
     </pre>
     \endhtmlonly

     \param data - a data map that contains the fields' name and value to set
                   for the new entity.
     \param extraReturnFields - extra fields of the entity that will be exposed 
                   to the user. Each entity already has a list of default fields
                   which are populated by defaultReturnFields() function.
     \return a new entity with the specified type.
    */
    template <class T>
    T *createEntity(const Dict &data,
                    const List &extraReturnFields = List());

    // -------------------------------------------------------------------------
    /*!
     A template function that returns one entity by the given filters. Make 
     sure to delete the entity in your application. An example:

     \htmlonly
     <br>
     <pre>
     Shotgun sg(); <br>
     Project *project = sg.findEntity&lt;Project&gt;(FilterBy("name", "is", "TEST PROJECT") <br>
                                                    .Or("code", "is, "tp")); <br>
     ... // Do whatever with the project <br>
     delete project;
     </pre>
     \endhtmlonly

     \param filterList - a list of filters.
     \param extraReturnFields - extra fields of the entity that will be exposed
                   to the user. Each entity already has a list of default fields
                   which are populated by defaultReturnFields() function.
     \param retiredOnly - true ("retired" entity only) or false ("active" entity).
     \param order - the result sort order. 
    */
    template <class T>
    T *findEntity(const FilterBy &filterList = FilterBy(),
                  const List &extraReturnFields = List(),
                  const bool retiredOnly = false,
                  const SortBy &order = SortBy());

    // -------------------------------------------------------------------------
    /// This template function is basically the same as calling findEntity()->asLink().
    /// But it deletes the entity before returning the link. So there won't be a 
    /// entity pointer lingering around after return. 
    template <class T>
    const Dict findEntityAsLink(const FilterBy &filterList = FilterBy(),
                                const List &extraReturnFields = List(),
                                const bool retiredOnly = false,
                                const SortBy &order = SortBy());

    // -------------------------------------------------------------------------
    /*!
     A template function that returns zero or more entities by the given filters. 
     Make sure to delete the entities in your application. An example:

     \htmlonly
     <br>
     <pre>
     Shotgun sg(); <br>
     Dict projectAsLink = sg.findEntity&lt;Project&gt;(FilterBy("name", "is", "TEST PROJECT")); <br>
     VersionPtrs versions = sg.findEntities&lt;Version&gt;(FilterBy("project", "is", projectAsLink)); <br>
     .. // Do whatever with the versions <br>
     for (size_t i = 0; i < versions.size(); i++) <br>
     { <br>
         delete versions[i]; <br>
     }
     </pre>
     \endhtmlonly

     \param filterList - a list of filters.
     \param limit - the upper limit on the number of entities returned.
     \param extraReturnFields - extra fields of the entity that will be exposed
                   to the user. Each entity already has a list of default fields
                   which are populated by defaultReturnFields() function.
     \param retiredOnly - true ("retired" entities only) or false ("active" entities).
     \param order - the result sort order. 
    */
    template <class T>
    std::vector<T *> findEntities(const FilterBy &filterList = FilterBy(),
                                  const int limit = 0,
                                  const List &extraReturnFields = List(),
                                  const bool retiredOnly = false,
                                  const SortBy &order = SortBy());

    // -------------------------------------------------------------------------
    /*!
     A template function that deletes an entity by its id. Here is an example:

     \htmlonly
     <br>
     <pre>
     Shotgun sg(); <br>
     Project *project = sg.findEntity&lt;Project&gt;(FilterBy("name", "is", "TEST PROJECT")); <br>
     sg.deleteEntity(project->getAttrValueAsInt("id")); <br>
     delete project; <br>
     </pre>
     \endhtmlonly
    */
    template <class T>
    bool deleteEntity(const int id);

    // -------------------------------------------------------------------------
    /// Creates a Shotgun entity. The implementation is the same as the template
    /// createEntity() function except that it uses the input "entityType" string 
    /// to decide what type of entity to create and it returns the base Entity * type.
    Entity *createEntity(const std::string &entityType,
                         const Dict &data,
                         const List &extraReturnFields = List());

    // -------------------------------------------------------------------------
    /// Finds a Shotgun entity. The implementation is the same as the template
    /// findEntity() function except that it uses the input "entityType" string 
    /// to decide what type of entity to search and it returns the base Entity * type.
    Entity *findEntity(const std::string &entityType,
                       const FilterBy &filterList = FilterBy(),
                       const List &extraReturnFields = List(),
                       const bool retiredOnly = false,
                       const SortBy &order = SortBy());

    // -------------------------------------------------------------------------
    /// Finds zero or more Shotgun entities. The implementation is the same as 
    /// the template findEntities() function except that it uses the input 
    /// "entityType" string to decide what type of entities to search and it 
    /// returns an array of the base Entity * type (i.e. EntityPtrs).
    EntityPtrs findEntities(const std::string &entityType,
                            const FilterBy &filterList = FilterBy(),
                            const int limit = 0,
                            const List &extraReturnFields = List(),
                            const bool retiredOnly = false,
                            const SortBy &order = SortBy());

    // -------------------------------------------------------------------------
    /// Deletes a Shotgun entity. The implementation is the same as the template
    /// deleteEntity() function except that it uses the input "entityType" string 
    /// to decide what type of entity to delete.
    bool deleteEntity(const std::string &entityType, const int id);

protected:
    // -------------------------------------------------------------------------
    /// This factory function creates an array of entity object pointers which 
    /// link to the existing Shotgun entities. The size of the array can be 0. 
    ///
    /// \param entityType - entity type string.
    /// \param findMap - filter map for finding the entities.
    /// \param limit - upper limit on the number of entities returned.
    /// \return an array of entities.
    EntityPtrs entityFactoryFind(const std::string &entityType, 
                                 Dict &findMap,
                                 const int limit = 0);

    // -------------------------------------------------------------------------
    /// This factory function creates an entity object pointer which links to 
    /// a newly-created Shotgun entity.
    ///
    /// \param entityType - entity type string.
    /// \param data - a data map that contains the fields' name and value to set
    ///               for the new entity.
    /// \return a new entity.
    Entity *entityFactoryCreate(const std::string &entityType, Dict &data);

    // -------------------------------------------------------------------------
    std::string m_serverURL; ///< The server URL string.
    std::string m_authName; ///< The authentication "script_name".
    std::string m_authKey; ///< The authentication "script_key".
    Dict m_authMap; ///< The authentication map.

private:
    // -------------------------------------------------------------------------
    /// Set the "TZ" environment varible which is used by some datetime-related
    /// calls to find the correct local time zone
    void setTimeZoneEnv(); 

    xmlrpc_c::clientXmlTransport_curl m_transport; ///< The XML-RPC transport.
    xmlrpc_c::client_xml *m_client; ///< The XML-RPC client.

    ClassRegistry m_classRegistry; ///< The class registry map.
};

// *****************************************************************************
// G++ requires template header in the same file as implementation. 
// In practice it means implementation inside .h file.
// *****************************************************************************
template <class T>
T *Shotgun::createEntity(const Dict &data,
                         const List &extraReturnFields)
{
    Entity *entity = createEntity(T::entityType(),
                                  data,
                                  extraReturnFields);

    if (T *t = dynamic_cast<T *>(entity))
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
T *Shotgun::findEntity(const FilterBy &filterList,
                       const List &extraReturnFields,
                       const bool retiredOnly,
                       const SortBy &order)
{
    Entity *entity = findEntity(T::entityType(),
                                filterList,
                                extraReturnFields,
                                retiredOnly,
                                order);

    if (T *t = dynamic_cast<T *>(entity))
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
const Dict Shotgun::findEntityAsLink(const FilterBy &filterList,
                                     const List &extraReturnFields,
                                     const bool retiredOnly,
                                     const SortBy &order)
{
    Entity *entity = findEntity(T::entityType(),
                                filterList,
                                extraReturnFields,
                                retiredOnly,
                                order);

    Dict link = entity->asLink();
    delete entity;
   
    return link;
}

// *****************************************************************************
template <class T>
std::vector<T *> Shotgun::findEntities(const FilterBy &filterList,
                                       const int limit,
                                       const List &extraReturnFields,
                                       const bool retiredOnly,
                                       const SortBy &order)
{
    EntityPtrs entities = findEntities(T::entityType(),
                                       filterList,
                                       limit,
                                       extraReturnFields,
                                       retiredOnly,
                                       order);
    std::vector<T *> outEntities;

    for (size_t i = 0; i < entities.size(); i++)
    {
        if (T *t = dynamic_cast<T *>(entities[i]))
        {
             outEntities.push_back(t);
        }
        else
        {
             throw SgEntityDynamicCastError(T::classType());
        }
    }

    return outEntities;
}


// *****************************************************************************
template <class T>
bool Shotgun::deleteEntity(const int id)
{
    return deleteEntity(T::entityType(), id);
}

// *****************************************************************************
} // End namespace SG

#endif    // End #ifdef __SG_SHOTGUN_H__
