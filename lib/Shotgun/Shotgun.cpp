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

#include <iostream>
#include <map>

#include <Shotgun/Shotgun.h>
#include <Shotgun/utils.h>

namespace Shotgun {

// *****************************************************************************
Shotgun::Shotgun(const std::string &serverURL,
                 const std::string &authKey)
    : m_serverURL(serverURL),
      m_authKey(authKey),
      m_client(NULL)
{
    // Client
    m_client = new xmlrpc_c::client_xml(&m_transport);

    // Authetication info comes from Shotgun Admin Pages->Scripts
    m_authMap.clear();
    m_authMap.add("script_name", "shotgun.main.Shotgun")
             .add("script_key", m_authKey);

    // Register the classes
    registerClass("Asset",        &Asset::factory,        &Asset::defaultReturnFields);
    registerClass("Delivery",     &Delivery::factory,     &Delivery::defaultReturnFields);
    registerClass("Element",      &Element::factory,      &Element::defaultReturnFields);
    registerClass("Group",        &Group::factory,        &Group::defaultReturnFields);
    registerClass("HumanUser",    &HumanUser::factory,    &HumanUser::defaultReturnFields);
    registerClass("Note",         &Note::factory,         &Note::defaultReturnFields);
    registerClass("Playlist",     &Playlist::factory,     &Playlist::defaultReturnFields);
    registerClass("Project",      &Project::factory,      &Project::defaultReturnFields);
    registerClass("PublishEvent", &PublishEvent::factory, &PublishEvent::defaultReturnFields);
    registerClass("Review",       &Review::factory,       &Review::defaultReturnFields);
    registerClass("ReviewItem",   &ReviewItem::factory,   &ReviewItem::defaultReturnFields);
    registerClass("Sequence",     &Sequence::factory,     &Sequence::defaultReturnFields);
    registerClass("Shot",         &Shot::factory,         &Shot::defaultReturnFields);
    registerClass("Task",         &Task::factory,         &Task::defaultReturnFields);
    registerClass("Version",      &Version::factory,      &Version::defaultReturnFields);
}

// *****************************************************************************
Shotgun::~Shotgun()
{
    delete m_client;
}

// *****************************************************************************
void Shotgun::registerClass(const std::string &entityType,
                            const FactoryFunc &factoryFunc,
                            const DefaultReturnFieldsFunc &defaultReturnFieldsFunc)
{
    m_classRegistry[entityType] = RegistryFuncPair(factoryFunc, defaultReturnFieldsFunc);
}

// *****************************************************************************
EntityPtrs Shotgun::entityFactoryFind(const std::string &entityType, 
                                      Dict &findMap,
                                      const int limit)
{
    EntityPtrs entities;

    // Find the factory func and the defaultReturnFields func for the given type of entity
    ClassRegistry::iterator foundRegistryIter = m_classRegistry.find(entityType);

    if (foundRegistryIter == m_classRegistry.end())
    {
        throw SgEntityFunctionNotFoundError(entityType, "m_classRegistry");
    }

    // The registry function pair 
    RegistryFuncPair registryFuncPair = (*foundRegistryIter).second;

    FactoryFunc factoryFunc = registryFuncPair.first;
    DefaultReturnFieldsFunc defaultReturnFieldsFunc = registryFuncPair.second;

    // ------------------------------------------------------------------------
    // If the given findMap already has a "return_fields", merge its contents 
    // with the poupulated default return Fields of the given entity type. 
    // Shotgun will ignore the duplicated fields when it returns the search result. 
    // To update the findMap's "return_fields", erase it first since the 
    // xmlrpc_c::value type can't be reassigned once it's been instantiated. 
    // ------------------------------------------------------------------------

    // Populate the default return fields and add the extra return fields
    // before passing them to the findMap
    List returnFields = (*defaultReturnFieldsFunc)();
    try
    {
        // Check to see if the findMap has "return_fields" already
        returnFields.extend(findMap.value<List>("return_fields"));
        findMap.erase("return_fields");
    }
    catch (SgDictKeyNotFoundError)
    {
        // Do nothing
    }

    findMap.add("return_fields", returnFields);

    // If the findMap already has a "type" field, override it with the
    // given "entityType" to ensure the type will not conflict with the
    // factory function.
    if (findMap.find("type"))
    {
        findMap.erase("type");
    }
    findMap.add("type", entityType);

    // Find the shotgun entities by the findMap
    List xmlrpcFindResult = Entity::findSGEntities(this, findMap, limit); 
    
    // Create entity class object.
    for (size_t i = 0; i < xmlrpcFindResult.size(); i++)
    {
        entities.push_back((*factoryFunc)(this, xmlrpcFindResult[i]));
    }

    return entities;
}

// *****************************************************************************
Entity *Shotgun::entityFactoryCreate(const std::string &entityType, Dict &createMap)
{
    // Find the factory func and the defaultReturnFields func for the given type of entity
    ClassRegistry::iterator foundRegistryIter = m_classRegistry.find(entityType);

    if (foundRegistryIter == m_classRegistry.end())
    {
        throw SgEntityFunctionNotFoundError(entityType, "m_classRegistry");
    }

    // The registry function pair 
    RegistryFuncPair registryFuncPair = (*foundRegistryIter).second;

    FactoryFunc factoryFunc = registryFuncPair.first;
    DefaultReturnFieldsFunc defaultReturnFieldsFunc = registryFuncPair.second;

    // ------------------------------------------------------------------------
    // If the given createMap already has a "return_fields", merge its contents 
    // with the poupulated default return fields of the given entity type. 
    // Shotgun will ignore the duplicated fields when it returns the search result. 
    // To update the createMap's "return_fields", erase it first since the 
    // xmlrpc_c::value type can't be reassigned once it's been instantiated. 
    // ------------------------------------------------------------------------

    // Populate the default return fields and add the extra return fields
    // before passing them to the createMap
    List returnFields = (*defaultReturnFieldsFunc)();
    try
    {
        // Check to see if the createMap has "return_fields" already
        returnFields.extend(createMap.value<List>("return_fields"));
        createMap.erase("return_fields");
    }
    catch (SgDictKeyNotFoundError)
    {
        // Do nothing
    }

    createMap.add("return_fields", returnFields);

    // If the createMap already has a "type" field, override it with the
    // given "entityType" to ensure the type will not conflict with the
    // factory function.
    if (createMap.find("type"))
    {
        createMap.erase("type");
    }
    createMap.add("type", entityType);

    // Create the shotgun entity by the createMap
    xmlrpc_c::value xmlrpcCreateResult = Entity::createSGEntity(this, createMap); 
    
    // Create entity class object.
    if (xmlrpcCreateResult.type() != xmlrpc_c::value::TYPE_NIL)
    {
        return (*factoryFunc)(this, xmlrpcCreateResult);
    }
    else
    {
        throw SgEntityCreateError(entityType);
    }
}

// *****************************************************************************
Entity *Shotgun::createEntity(const std::string &entityType,
                              const Dict &data,
                              const List &extraReturnFields)
{
    Dict createMap = Entity::buildCreateMap(entityType,
                                            data,
                                            extraReturnFields);

    return this->entityFactoryCreate(entityType, createMap);
}
 
// *****************************************************************************
Entity *Shotgun::findEntity(const std::string &entityType,
                            const FilterBy &filterList,
                            const List &extraReturnFields,
                            const bool retiredOnly,
                            const SortBy &order)
{
    Dict findMap = Entity::buildFindMap(entityType,
                                        filterList,
                                        extraReturnFields,
                                        retiredOnly,
                                        1, // limit
                                        order);

    EntityPtrs entities = this->entityFactoryFind(entityType, findMap, 1);
    if (entities.size() > 0)
    {
        return entities[0];
    }
    else
    {
        throw SgEntityNotFoundError(entityType);
    }
}

// *****************************************************************************
EntityPtrs Shotgun::findEntities(const std::string &entityType,
                                 const FilterBy &filterList,
                                 const int limit,
                                 const List &extraReturnFields,
                                 const bool retiredOnly,
                                 const SortBy &order)
{
    Dict findMap = Entity::buildFindMap(entityType,
                                        filterList,
                                        extraReturnFields,
                                        retiredOnly,
                                        limit,
                                        order);

    return this->entityFactoryFind(entityType, findMap, limit);
}

// *****************************************************************************
bool Shotgun::deleteEntity(const std::string &entityType, const int id)
{
    return Entity::deleteSGEntity(this, entityType, id);
}
    
} // End namespace Shotgun
