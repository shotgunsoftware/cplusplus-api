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
    if (m_serverURL.find("api2") != std::string::npos)
    {
        m_api = "api2";
      
        throw SgApiError(m_api);
    }
    else if (m_serverURL.find("api3") != std::string::npos)
    {
        m_api = "api3";

        m_authMap.clear();
        m_authMap.add("script_name", "shotgun.main.Shotgun")
                 .add("script_key", m_authKey);
    }

    // Register the classes
    registerClass("Asset",        &Asset::factory,        &Asset::populateReturnFields);
    registerClass("Delivery",     &Delivery::factory,     &Delivery::populateReturnFields);
    registerClass("Element",      &Element::factory,      &Element::populateReturnFields);
    registerClass("Group",        &Group::factory,        &Group::populateReturnFields);
    registerClass("HumanUser",    &HumanUser::factory,    &HumanUser::populateReturnFields);
    registerClass("Note",         &Note::factory,         &Note::populateReturnFields);
    registerClass("Playlist",     &Playlist::factory,     &Playlist::populateReturnFields);
    registerClass("Project",      &Project::factory,      &Project::populateReturnFields);
    registerClass("PublishEvent", &PublishEvent::factory, &PublishEvent::populateReturnFields);
    registerClass("Review",       &Review::factory,       &Review::populateReturnFields);
    registerClass("ReviewItem",   &ReviewItem::factory,   &ReviewItem::populateReturnFields);
    registerClass("Sequence",     &Sequence::factory,     &Sequence::populateReturnFields);
    registerClass("Shot",         &Shot::factory,         &Shot::populateReturnFields);
    registerClass("Task",         &Task::factory,         &Task::populateReturnFields);
    registerClass("Version",      &Version::factory,      &Version::populateReturnFields);
}

// *****************************************************************************
Shotgun::~Shotgun()
{
    delete m_client;
}

// *****************************************************************************
void Shotgun::registerClass(const std::string &entityType,
                            const FactoryFunc &factoryFunc,
                            const PopulateReturnFieldsFunc &populateFunc)
{
    m_classRegistry[entityType] = RegistryFuncPair(factoryFunc, populateFunc);
}

// *****************************************************************************
EntityPtrs Shotgun::entityFactoryFind(const std::string &entityType, Dict &findMap)
{
    EntityPtrs entities;

    // Find the factory func and the populateReturnFields func for the given type of entity
    ClassRegistry::iterator foundRegistryIter = m_classRegistry.find(entityType);

    if (foundRegistryIter == m_classRegistry.end())
    {
        throw SgEntityFunctionNotFoundError(entityType, "m_classRegistry");
    }

    FactoryFunc factorFunc = (*foundRegistryIter).second.first;
    PopulateReturnFieldsFunc populateFunc = (*foundRegistryIter).second.second;

    // ------------------------------------------------------------------------
    // If the given findMap already has a "return_fields", merge its contents 
    // with the poupulated default return Fields of the given entity type. 
    // Shotgun will ignore the duplicated fields when it returns the search result. 
    // To update the findMap's "return_fields", erase it first since the 
    // xmlrpc_c::value type can't be reassigned once it's been instantiated. 
    // ------------------------------------------------------------------------

    // Populate the default return fields and add the extra return fields
    // before passing them to the findMap
    List returnFields = (*populateFunc)();
    if (findMap.find("return_fields"))
    {
        returnFields.extend(findMap.value<List>("return_fields"));
        findMap.erase("return_fields");
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
    List xmlrpcFindResult = Entity::findSGEntities(this, findMap); 
    
    // Create entity class object.
    for (size_t i = 0; i < xmlrpcFindResult.size(); i++)
    {
        entities.push_back((*factorFunc)(this, xmlrpcFindResult[i]));
    }

    return entities;
}

// *****************************************************************************
Entity *Shotgun::entityFactoryCreate(const std::string &entityType, Dict &createMap)
{
    // Find the factory func and the populateReturnFields func for the given type of entity
    ClassRegistry::iterator foundRegistryIter = m_classRegistry.find(entityType);

    if (foundRegistryIter == m_classRegistry.end())
    {
        throw SgEntityFunctionNotFoundError(entityType, "m_classRegistry");
    }

    FactoryFunc factorFunc = (*foundRegistryIter).second.first;
    PopulateReturnFieldsFunc populateFunc = (*foundRegistryIter).second.second;

    // ------------------------------------------------------------------------
    // If the given createMap already has a "return_fields", merge its contents 
    // with the poupulated default return fields of the given entity type. 
    // Shotgun will ignore the duplicated fields when it returns the search result. 
    // To update the createMap's "return_fields", erase it first since the 
    // xmlrpc_c::value type can't be reassigned once it's been instantiated. 
    // ------------------------------------------------------------------------

    // Populate the default return fields and add the extra return fields
    // before passing them to the createMap
    List returnFields = (*populateFunc)();
    if (createMap.find("return_fields"))
    {
        returnFields.extend(createMap.value<List>("return_fields"));
        createMap.erase("return_fields");
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
        return (*factorFunc)(this, xmlrpcCreateResult);
    }
    else
    {
        throw SgEntityCreateError(entityType);
    }
}

// *****************************************************************************
Dict Shotgun::getProjectLink(const std::string &projectCode)
{
    Project *project = findEntity<Project>(FilterBy("code", "is", projectCode));
    Dict link = project->asLink();
    delete project;

    return link;
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
                                         0,
                                         order);

    EntityPtrs entities = this->entityFactoryFind(entityType, findMap);
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

    return this->entityFactoryFind(entityType, findMap);
}

// *****************************************************************************
Entity *Shotgun::findEntityById(const std::string &entityType, const int id)
{
    return findEntity(entityType,
                      FilterBy("id", "is", id));

}

// *****************************************************************************
bool Shotgun::deleteEntity(const std::string &entityType, const int id)
{
    return Entity::deleteSGEntity(this, entityType, id);
}
    
} // End namespace Shotgun
