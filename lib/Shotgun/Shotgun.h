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

#ifndef __SHOTGUN_H__
#define __SHOTGUN_H__

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

namespace Shotgun {

// Define the ClassRegistry
typedef Entity* (*FactoryFunc)(Shotgun *, const xmlrpc_c::value &);
typedef List (*PopulateReturnFieldsFunc) ();
typedef std::pair<FactoryFunc, PopulateReturnFieldsFunc> RegistryFuncPair;
typedef std::map<std::string, RegistryFuncPair> ClassRegistry;

class TaskMixin;
class NoteMixin;

// *****************************************************************************
class Shotgun
{
    friend class Entity; 
    friend class TaskMixin;
    friend class NoteMixin;

public:
    Shotgun(const std::string &serverURL = SG_DEFAULT_URL,
            const std::string &authKey = SG_AUTHENTICATION_KEY);
    virtual ~Shotgun();

    //------------------------------------------------------------------------
    xmlrpc_c::client_xml *client() const { return m_client; }
    const std::string &serverURL() const { return m_serverURL; }
    const std::string &authKey() const { return m_authKey; }
    const std::string &api() const { return m_api; }
    const Dict &authMap() const { return m_authMap; } 

    //------------------------------------------------------------------------
    Method *method(const std::string &methodName) 
        { return new Method(this, methodName); }

    //------------------------------------------------------------------------
    void registerClass(const std::string &entityType,
                       const FactoryFunc &factoryFunc,
                       const PopulateReturnFieldsFunc &populateFunc);

    //------------------------------------------------------------------------
    // This is used by most of the search filters, so keep it.
    Dict getProjectLink(const std::string &projectCode);

    //------------------------------------------------------------------------
    template <class T>
    T *createEntity(const Dict &data,
                    const List &extraReturnFields = List());

    //------------------------------------------------------------------------
    template <class T>
    T *findEntity(const FilterBy &filterList = FilterBy(),
                  const List &extraReturnFields = List(),
                  const bool retiredOnly = false,
                  const SortBy &order = SortBy());

    //------------------------------------------------------------------------
    template <class T>
    std::vector<T *> findEntities(const FilterBy &filterList = FilterBy(),
                                  const int limit = 0,
                                  const List &extraReturnFields = List(),
                                  const bool retiredOnly = false,
                                  const SortBy &order = SortBy());

    //------------------------------------------------------------------------
    template <class T>
    bool deleteEntity(const int id);

    //------------------------------------------------------------------------
    Entity *createEntity(const std::string &entityType,
                         const Dict &data,
                         const List &extraReturnFields = List());

    //----------------------------------------------------------------------
    Entity *findEntity(const std::string &entityType,
                       const FilterBy &filterList = FilterBy(),
                       const List &extraReturnFields = List(),
                       const bool retiredOnly = false,
                       const SortBy &order = SortBy());

    //----------------------------------------------------------------------
    EntityPtrs findEntities(const std::string &entityType,
                            const FilterBy &filterList = FilterBy(),
                            const int limit = 0,
                            const List &extraReturnFields = List(),
                            const bool retiredOnly = false,
                            const SortBy &order = SortBy());

    //------------------------------------------------------------------------
    Entity *findEntityById(const std::string &entityType, const int id);

    //------------------------------------------------------------------------
    bool deleteEntity(const std::string &entityType, const int id);

protected:
    //----------------------------------------------------------------------
    // This factory function creates an array of entity object pointers which 
    // link to the existing Shotgun entities. The size of the array can be 0. 
    EntityPtrs entityFactoryFind(const std::string &entityType, Dict &findMap);

    //----------------------------------------------------------------------
    // This factory function creates an entity object pointer which links to 
    // a newly-created Shotgun entity.
    Entity *entityFactoryCreate(const std::string &entityType, Dict &data);

    std::string m_serverURL;
    std::string m_authKey;
    std::string m_api;
    xmlrpc_c::clientXmlTransport_curl m_transport;
    xmlrpc_c::client_xml *m_client;
    Dict m_authMap;

private:
    ClassRegistry m_classRegistry;

};

// *****************************************************************************
// G++ requires template header in the same file as implementation. 
// In practice it means implementation inside .h file.
// *****************************************************************************
template <class T>
T *Shotgun::createEntity(const Dict &data,
                         const List &extraReturnFields)
{
    Entity *entity = createEntity(T::type(),
                                  data,
                                  extraReturnFields);

    if (T *t = dynamic_cast<T *>(entity))
    {
        return t;
    }
    else
    {
        throw SgEntityDynamicCastError(T::type());
    }
}

// *****************************************************************************
template <class T>
T *Shotgun::findEntity(const FilterBy &filterList,
                       const List &extraReturnFields,
                       const bool retiredOnly,
                       const SortBy &order)
{
    Entity *entity = findEntity(T::type(),
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
        throw SgEntityDynamicCastError(T::type());
    }

                            
}

// *****************************************************************************
template <class T>
std::vector<T *> Shotgun::findEntities(const FilterBy &filterList,
                                       const int limit,
                                       const List &extraReturnFields,
                                       const bool retiredOnly,
                                       const SortBy &order)
{
    EntityPtrs entities = findEntities(T::type(),
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
             throw SgEntityDynamicCastError(T::type());
        }
    }

    return outEntities;
}


// *****************************************************************************
template <class T>
bool Shotgun::deleteEntity(const int id)
{
    return Entity::deleteSGEntity(this, T::type(), id);
}

// *****************************************************************************
} // End namespace Shotgun

#endif    // End #ifdef __SHOTGUN_H__
