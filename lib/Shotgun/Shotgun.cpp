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
#include <Shotgun/FilterBy.h>
#include <Shotgun/utils.h>

namespace Shotgun {

// *****************************************************************************
Shotgun::Shotgun(const std::string &serverURL)
    : m_serverURL(serverURL),
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
        m_authMap["script_name"] = toXmlrpcValue("shotgun.main.Shotgun");
        m_authMap["script_key"] = toXmlrpcValue(SG_AUTHENTICATION_KEY);
    }

    registerClass();
}

// *****************************************************************************
Shotgun::~Shotgun()
{
    delete m_client;
}

void Shotgun::registerClass()
{
    m_classRegistry["Asset"]        = RegistryFuncPair(&Asset::factory,        &Asset::populateReturnFields);
    m_classRegistry["Delivery"]     = RegistryFuncPair(&Delivery::factory,     &Delivery::populateReturnFields);
    m_classRegistry["Element"]      = RegistryFuncPair(&Element::factory,      &Element::populateReturnFields);
    m_classRegistry["Group"]        = RegistryFuncPair(&Group::factory,        &Group::populateReturnFields);
    m_classRegistry["HumanUser"]    = RegistryFuncPair(&HumanUser::factory,    &HumanUser::populateReturnFields);
    m_classRegistry["Note"]         = RegistryFuncPair(&Note::factory,         &Note::populateReturnFields);
    m_classRegistry["Playlist"]     = RegistryFuncPair(&Playlist::factory,     &Playlist::populateReturnFields);
    m_classRegistry["Project"]      = RegistryFuncPair(&Project::factory,      &Project::populateReturnFields);
    m_classRegistry["PublishEvent"] = RegistryFuncPair(&PublishEvent::factory, &PublishEvent::populateReturnFields);
    m_classRegistry["Review"]       = RegistryFuncPair(&Review::factory,       &Review::populateReturnFields);
    m_classRegistry["ReviewItem"]   = RegistryFuncPair(&ReviewItem::factory,   &ReviewItem::populateReturnFields);
    m_classRegistry["Sequence"]     = RegistryFuncPair(&Sequence::factory,     &Sequence::populateReturnFields);
    m_classRegistry["Shot"]         = RegistryFuncPair(&Shot::factory,         &Shot::populateReturnFields);
    m_classRegistry["Task"]         = RegistryFuncPair(&Task::factory,         &Task::populateReturnFields);
    m_classRegistry["Version"]      = RegistryFuncPair(&Version::factory,      &Version::populateReturnFields);
}

#warning This one should be deprecated 
// *****************************************************************************
Entity *Shotgun::entityFactoryFind(const std::string &entityType)
{
    ClassRegistry::iterator foundIter = m_classRegistry.find(entityType);
    if (foundIter != m_classRegistry.end())
    {
        FactoryFunc factorFunc = (*foundIter).second.first;
        return (*factorFunc)(this, xmlrpc_c::value_nil());
    }
    else
    {
#warning Add throw error instead
        return NULL;
    }
}

// *****************************************************************************
EntityPtrs Shotgun::entityFactoryFind(const std::string &entityType, SgMap &findMap)
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

    // If the given findMap already has a "return_fields", merge its contents 
    // with the poupulated returnFields of the given entity type. Shotgun
    // will ignore the duplicated fields when it returns the search result. 
    // To update the findMap's "return_fields", erase it first since the 
    // xmlrpc_c::value type can't be reassigned once it's been instantiated. 
    SgArray extraReturnFields = SgArray();
    SgMap::iterator foundReturnFieldsIter = findMap.find("return_fields");
    if (foundReturnFieldsIter != findMap.end())
    {
        extraReturnFields = (xmlrpc_c::value_array((*foundReturnFieldsIter).second)).vectorValueValue();
        findMap.erase(foundReturnFieldsIter);
    }

    // Populate the return fields and pass them to the findMap
    SgArray returnFields = (*populateFunc)(extraReturnFields);
    findMap["return_fields"] = toXmlrpcValue(returnFields);

    // If the findMap already has a "type" field, override it with the
    // given "entityType" to ensure the type will not conflict with the
    // factory function.
    SgMap::iterator foundTypeIter = findMap.find("type");
    if (foundTypeIter != findMap.end())
    {
        findMap.erase(foundTypeIter);
    }
    findMap["type"] = toXmlrpcValue(entityType);

    // Find the shotgun entities by the findMap
    SgArray xmlrpcFindResult = Entity::findSGEntities(this, findMap); 
    
    // Create entity class object.
    for (size_t i = 0; i < xmlrpcFindResult.size(); i++)
    {
        entities.push_back((*factorFunc)(this, xmlrpcFindResult[i]));
    }

    return entities;
}

// *****************************************************************************
Project *Shotgun::findProjectByCode(const std::string &projectCode)
{
    return findEntity<Project>(FilterBy("code", "is", projectCode));
}
    
// *****************************************************************************
Project *Shotgun::findProjectByName(const std::string &projectName)
{
    return findEntity<Project>(FilterBy("name", "is", projectName));
}
    
// *****************************************************************************
ProjectPtrs Shotgun::allProjects()
{
    return findEntities<Project>();
}
    
// *****************************************************************************
SgMap Shotgun::getProjectLink(const std::string &projectCode)
{
    Project *project = findProjectByCode(projectCode);
    SgMap link = project->asLink();
    delete project;

    return link;
}
    
// *****************************************************************************
Sequence *Shotgun::findSequenceByName(const std::string &projectCode,
                                     const std::string &sequenceName)
{
    std::string sequenceNameUpper = toupper(sequenceName);

    return findEntity<Sequence>(FilterBy("code", "is", sequenceNameUpper)
                                    .And("project", "is", getProjectLink(projectCode)));
}
    
// *****************************************************************************
SequencePtrs Shotgun::findSequencesByProject(const std::string &projectCode, const int limit)
{
    return findEntities<Sequence>(FilterBy("project", "is", getProjectLink(projectCode)),
                                  limit);
}
    
// *****************************************************************************
Shot *Shotgun::findShotByName(const std::string &shotName)
{
#warning TODO: Implement in a non-Tippett way
#if 0
    TipUtil::ShotName sn = TipUtil::ShotName(shotName);
  
    return findEntity<Shot>(FilterBy("code", "is", sn.shot(true, true))
                                .And("project", "is", findProjectByCode(sn.project())));

#else
    throw SgEntityError("[Not implemented yet] Shotgun::findShotByName(..) - implement in a non-Tippett way");
#endif
}
    
// *****************************************************************************
ShotPtrs Shotgun::findShotsByProject(const std::string &projectCode, const int limit)
{
    return findEntities<Shot>(FilterBy("project", "is", getProjectLink(projectCode)),
                              limit);
}
    
// *****************************************************************************
Version *Shotgun::findVersionByName(const std::string &versionName)
{
#warning TODO: Implement in a non-Tippett way
#if 0
    TipUtil::DailyName dn = TipUtil::DailyName(dailyName);

    return findEntity<Version>(FilterBy("code", "is", dailyName)
                                   .And("project", "is", findProjectByCode(dn.project())));
#else
    throw SgEntityError("[Not implemented yet] Shotgun::findVersionByName(..) - implement in a non-Tippett way");
#endif 
}
    
// *****************************************************************************
VersionPtrs Shotgun::findVersionsByProject(const std::string &projectCode, const int limit)
{
    return findEntities<Version>(FilterBy("project", "is", getProjectLink(projectCode)),
                                 limit);
}
    
// *****************************************************************************
VersionPtrs Shotgun::findVersionsByShot(const std::string &projectCode,
                                        const std::string &shotName, 
                                        const int limit)
{
#warning TODO: Implement in a non-Tippett way
#if 0
    std::string theShotName = TipUtil::ShotName(projectCode, shotName).shot(true, true);
    Shot *shot = findShotByName(theShotName);
    SgMap shotLink = shot->asLink();
    delete shot;
 
    return findEntities<Version>(FilterBy("entity", "is", shotLink)
                                     .And("project", "is", getProjectLink(projectCode)),,
                                 limit);
#else
    throw SgEntityError("[Not implemented yet] Shotgun::findVersionByName(..) - implement in a non-Tippett way");
#endif
}

// *****************************************************************************
VersionPtrs Shotgun::findVersionsByReviewStatus(const std::string &projectCode,
                                                const std::string &reviewStatus, 
                                                const int limit)
{
    return findEntities<Version>(FilterBy("sg_status", "is", reviewStatus)
                                     .And("project", "is", getProjectLink(projectCode)),
                                 limit);
}
    
// *****************************************************************************
HumanUser *Shotgun::findHumanUserById(const int userId)
{
    return findEntity<HumanUser>(FilterBy("id", "is", userId));
}

// *****************************************************************************
HumanUser *Shotgun::findHumanUserByLogin(const std::string &userLogin)
{
    return findEntity<HumanUser>(FilterBy("login", "is", userLogin));
}

// *****************************************************************************
HumanUser *Shotgun::findRetiredHumanUser(const std::string &userLogin)
{
    return findEntity<HumanUser>(FilterBy("login", "is", userLogin),
                                 SgArray(), // extraReturnFields
                                 true); // retiredOnly
}

// *****************************************************************************
Element *Shotgun::findElementByName(const std::string &projectCode,
                                    const std::string &elementName)
{
    return findEntity<Element>(FilterBy("code", "is", elementName)
                                   .And("project", "is", getProjectLink(projectCode)));
}
    
// *****************************************************************************
ElementPtrs Shotgun::findElementsByProject(const std::string &projectCode, 
                                           const std::string &elementType,
                                           const int limit)
{
    if (elementType != "")
    {
        return findEntities<Element>(FilterBy("sg_element_type", "is", elementType)
                                         .And("project", "is", getProjectLink(projectCode)),
                                     limit);
    }
    else
    {
        return findEntities<Element>(FilterBy("project", "is", getProjectLink(projectCode)),
                                     limit);
    }
}
    
// *****************************************************************************
Asset *Shotgun::findAssetByName(const std::string &projectCode,
                                const std::string &assetName)
{
    return findEntity<Asset>(FilterBy("code", "is", assetName)
                                 .And("project", "is", getProjectLink(projectCode)));
}
    
// *****************************************************************************
AssetPtrs Shotgun::findAssetsByProject(const std::string &projectCode, 
                                       const std::string &assetType,
                                       const int limit)
{
    if (assetType != "")
    {
        return findEntities<Asset>(FilterBy("sg_asset_type", "is", assetType)
                                       .And("project", "is", getProjectLink(projectCode)),
                                   limit);
    }
    else
    {
        return findEntities<Asset>(FilterBy("project", "is", getProjectLink(projectCode)),
                                   limit);
    }
}
    
// *****************************************************************************
Delivery *Shotgun::findDeliveryByName(const std::string &projectCode,
                                      const std::string &deliveryName)
{
    return findEntity<Delivery>(FilterBy("title", "is", deliveryName)
                                    .And("project", "is", getProjectLink(projectCode)));
}
    
// *****************************************************************************
Delivery *Shotgun::findDeliveryById(const int &deliveryId)
{
    return findEntity<Delivery>(FilterBy("id", "is", deliveryId));
}
    
// *****************************************************************************
DeliveryPtrs Shotgun::findDeliveriesByProject(const std::string &projectCode, 
                                              const std::string &deliveryStatus,
                                              const int limit)
{
    if (deliveryStatus != "")
    {
        return findEntities<Delivery>(FilterBy("sg_delivery_status", "is", deliveryStatus)
                                          .And("project", "is", getProjectLink(projectCode)),
                                      limit);
    }
    else
    {
        return findEntities<Delivery>(FilterBy("project", "is", getProjectLink(projectCode)),
                                      limit);
    }
}
    
// *****************************************************************************
PublishEvent *Shotgun::findPublishEventByName(const std::string &projectCode,
                                              const std::string &publishEventName)
{
    return findEntity<PublishEvent>(FilterBy("code", "is", publishEventName)
                                        .And("project", "is", getProjectLink(projectCode)));
}
    
// *****************************************************************************
PublishEventPtrs Shotgun::findPublishEventsByProject(const std::string &projectCode, 
                                                     const std::string &publishEventType,
                                                     const int limit)
{
    if (publishEventType != "")
    {
        return findEntities<PublishEvent>(FilterBy("sg_type", "is", publishEventType)
                                              .And("project", "is", getProjectLink(projectCode)),
                                          limit);
    }
    else
    {
        return findEntities<PublishEvent>(FilterBy("project", "is", getProjectLink(projectCode)),
                                          limit);
    }
}
    
// *****************************************************************************
Review *Shotgun::findReviewByName(const std::string &projectCode,
                                  const std::string &reviewName,
                                  const std::string &dateSent)
{
    if (dateSent != "")
    {
        return findEntity<Review>(FilterBy("code", "is", reviewName)
                                      .And("sg_review_date_sent", "is", dateSent)
                                      .And("project", "is", getProjectLink(projectCode)));
    }
    else
    {
        return findEntity<Review>(FilterBy("code", "is", reviewName)
                                      .And("project", "is", getProjectLink(projectCode)));
    }
}
    
// *****************************************************************************
Review *Shotgun::findReviewById(const int &reviewId)
{
    return findEntity<Review>(FilterBy("id", "is", reviewId));
}
    
// *****************************************************************************
ReviewPtrs Shotgun::findReviewsByProject(const std::string &projectCode, 
                                         const int limit)
{
    return findEntities<Review>(FilterBy("project", "is", getProjectLink(projectCode)),
                                limit);
}
    
// *****************************************************************************
ReviewItem *Shotgun::findReviewItemByName(const std::string &projectCode,
                                          const std::string &reviewItemName)
{
    // There could be multiple ReviewItems that share the same name.
    // So the result might not be unique. In this case, search by
    // "id" is better since "id" is unique.
    return findEntity<ReviewItem>(FilterBy("code", "is", reviewItemName)
                                      .And("project", "is", getProjectLink(projectCode)));
}
    
// *****************************************************************************
ReviewItem *Shotgun::findReviewItemById(const int &reviewItemId)
{
    return findEntity<ReviewItem>(FilterBy("id", "is", reviewItemId));
}
    
// *****************************************************************************
ReviewItemPtrs Shotgun::findReviewItemsByProject(const std::string &projectCode, 
                                                 const int limit)
{
    return findEntities<ReviewItem>(FilterBy("project", "is", getProjectLink(projectCode)),
                                    limit);
}

// *****************************************************************************
Task *Shotgun::findTaskByName(const std::string &projectCode,
                              const std::string &taskName)
{
    return findEntity<Task>(FilterBy("content", "is", taskName)
                                .And("project", "is", getProjectLink(projectCode)));
}
    
// // *****************************************************************************
// // The "sg_system_task_type" field seems no longer exist
// //
// TaskPtrs Shotgun::findTasksByType(const std::string &projectCode,
//                                   const std::string &taskType,
//                                   const std::string &linkEntityType,
//                                   const int limit)
// {
//     if (linkEntityType != "")
//     {
//         return findEntities<Task>(FilterBy("sg_system_task_type", "is", taskType)
//                                       .And("entity", "type_is", linkEntityType)
//                                       .And("project", "is", getProjectLink(projectCode)),
//                                   limit);
//     }
//     else
//     {
//         return findEntities<Task>(FilterBy("sg_system_task_type", "is", taskType)
//                                       .And("project", "is", getProjectLink(projectCode)),
//                                   limit);
//     }
// }

// *****************************************************************************
TaskPtrs Shotgun::findTasksByLinkEntity(const std::string &projectCode,
                                        const SgMap &linkEntity,
                                        const int limit)
{
    return findEntities<Task>(FilterBy("entity", "is", linkEntity)
                                  .And("project", "is", getProjectLink(projectCode)),
                              limit);
}

// *****************************************************************************
TaskPtrs Shotgun::findTasksByMilestone(const std::string &projectCode,
                                       const std::string &shotName,
                                       const int limit)
{
    Shot *shot = findShotByName(shotName);
    SgMap shotLink = shot->asLink();
    delete shot;

    return findEntities<Task>(FilterBy("entity", "is", shotLink)
                                  .And("milestone", "type_is", true)
                                  .And("project", "is", getProjectLink(projectCode)),
                              limit);
}
    

// *****************************************************************************
TaskPtrs Shotgun::findTasksByProject(const std::string &projectCode,
                                     const int limit)
{
    return findEntities<Task>(FilterBy("project", "is", getProjectLink(projectCode)),
                              limit);
}
    
// *****************************************************************************
Group *Shotgun::findGroupByName(const std::string &groupName)
{
    return findEntity<Group>(FilterBy("code", "is", groupName));
}
    
// *****************************************************************************
Group *Shotgun::findGroupById(const int &groupId)
{
    return findEntity<Group>(FilterBy("id", "is", groupId));
}
    
// *****************************************************************************
NotePtrs Shotgun::findNotesByType(const std::string &projectCode,
                                  const std::string &noteType,
                                  const int limit)
{
    return findEntities<Note>(FilterBy("sg_note_type", "is", noteType)
                                  .And("project", "is", getProjectLink(projectCode)),
                              limit);
}

// *****************************************************************************
NotePtrs Shotgun::findNotesByAuthor(const std::string &projectCode,
                                    const std::string &userName,
                                    const int limit)
{
    HumanUser *user = findHumanUserByLogin(userName);
    SgMap userLink = user->asLink();
    delete user;

    return findEntities<Note>(FilterBy("user", "is", userLink)
                                  .And("project", "is", getProjectLink(projectCode)),
                              limit);
}

// *****************************************************************************
NotePtrs Shotgun::findNotesByLinks(const std::string &projectCode,
                                   const SgArray &noteLinks,
                                   const std::string &noteType,
                                   const int limit)
{
    FilterBy filterList = FilterBy("project", "is", getProjectLink(projectCode))
                              .And("sg_note_type", "is", noteType);

    // None of these works:
    //     - ("note_links", "contains", noteLinks[i])
    //     - ("note_links", "type_is", "Shot")
    //     - ("note_links", "name_contains", linkName)
    //     - "note_links", "in", noteLinks)

#warning This seems to work with only ONE noteLink.
    for (size_t i = 0; i < noteLinks.size(); i++)
    {
        filterList.And("note_links", "is", noteLinks[i]);
    }

    return findEntities<Note>(filterList, limit);
}
    
// *****************************************************************************
Playlist *Shotgun::findPlaylistByName(const std::string &projectCode,
                                      const std::string &playlistName)
{
    return findEntity<Playlist>(FilterBy("code", "is", playlistName)
                                    .And("project", "is", getProjectLink(projectCode)));
}
    
// *****************************************************************************
PlaylistPtrs Shotgun::findPlaylistsByProject(const std::string &projectCode, 
                                             const int limit)
{
    return findEntities<Playlist>(FilterBy("project", "is", getProjectLink(projectCode)),
                                  limit);
}
 

// *****************************************************************************
// protected - called within this library
Entity *Shotgun::findEntity(const std::string &entityType,
                            const FilterBy &filterList,
                            const SgArray &extraReturnFields,
                            const bool retiredOnly,
                            const SgArray &order)
{
    SgMap findMap = Entity::buildFindMap(entityType,
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
Entity *Shotgun::findEntityById(const std::string &entityType, const int &id)
{
    return findEntity(entityType,
                      FilterBy("id", "is", id));

}
    
} // End namespace Shotgun
