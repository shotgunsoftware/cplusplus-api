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

#include <Shotgun/Type.h>
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

#include <Shotgun/FilterBy.h>

namespace Shotgun {

// Define the ClassRegistry
typedef Entity* (*FactoryFunc)(Shotgun *, const xmlrpc_c::value &);
typedef SgArray (*PopulateReturnFieldsFunc) (const SgArray &);
typedef std::pair<FactoryFunc, PopulateReturnFieldsFunc> RegistryFuncPair;
typedef std::map<std::string, RegistryFuncPair> ClassRegistry;

class TaskMixin;
class NoteMixin;

// *****************************************************************************
class Shotgun
{
    friend class Entity; // So that Entity class can call its protected findEntity(..).
    friend class TaskMixin;
    friend class NoteMixin;

public:
    Shotgun(const std::string &serverURL=SG_DEFAULT_URL);
    virtual ~Shotgun();

    xmlrpc_c::client_xml *client() const { return m_client; }
    const std::string &serverURL() const { return m_serverURL; }
    const std::string &api() const { return m_api; }
    const SgMap &authMap() const { return m_authMap; } 

    Method *method(const std::string &methodName) 
        { return new Method(this, methodName); }

    void registerClass();

#warning This entityFactoryFind(..) func should be deprecated
    //----------------------------------------------------------------------
    // This factory function creates an entity object which does not link to 
    // any of the existing Shotgun entities.
    Entity *entityFactoryFind(const std::string &entityType);

    //----------------------------------------------------------------------
    // This factory function creates an array of entity objects which link to
    // the existing Shotgun entities. The size of the array can be 0. 
    EntityPtrs entityFactoryFind(const std::string &entityType, SgMap &findMap);

#warning All the create**(..) functions should be updated to return pointer type
    //-----------------------------------------------------------------------
    // Project Entity
    Project createProject(const std::string &projectName, const std::string &projectCode) 
        { return Project::create(this, projectName, projectCode); }
    Project *findProjectByCode(const std::string &projectCode);
    Project *findProjectByName(const std::string &projectName);
    ProjectPtrs allProjects();
    bool deleteProjectById(const int id) { return Entity::deleteSGEntity(this, "Project", id); }
    SgMap getProjectLink(const std::string &projectCode);

    //------------------------------------------------------------------------
    // Sequence Entity
    Sequence createSequence(const std::string &projectCode, const std::string &sequenceName) 
        { return Sequence::create(this, projectCode, sequenceName); }
    Sequence *findSequenceByName(const std::string &projectCode, const std::string &sequenceName);
    SequencePtrs findSequencesByProject(const std::string &projectCode, const int limit = 0);
    bool deleteSequenceById(const int id) { return Entity::deleteSGEntity(this, "Sequence", id); }

    //------------------------------------------------------------------------
    // Shot Entity
    Shot createShot(const std::string &shotName, const std::string &shotType = "") 
        { return Shot::create(this, shotName, shotType); }
    Shot *findShotByName(const std::string &shotName);
    ShotPtrs findShotsByProject(const std::string &projectCode, const int limit = 0);
    bool deleteShotById(const int id) { return Entity::deleteSGEntity(this, "Shot", id); }

    //------------------------------------------------------------------------
    // Version Entity
    Version createVersion(const std::string &versionName) 
        { return Version::create(this, versionName); }
    Version *findVersionByName(const std::string &versionName);
    VersionPtrs findVersionsByProject(const std::string &projectCode, const int limit = 0);
    VersionPtrs findVersionsByShot(const std::string &projectCode, 
                                   const std::string &shotName, 
                                   const int limit = 0);
    VersionPtrs findVersionsByReviewStatus(const std::string &projectCode, 
                                           const std::string &reviewStatus,
                                           const int limit = 0);
    bool deleteVersionById(const int id) { return Entity::deleteSGEntity(this, "Version", id); }

    //-----------------------------------------------------------------------
    // HumanUser Entity
    HumanUser createHumanUser(const std::string &userName,
                              const std::string &userLogin,
                              const std::string &userEmail="")
        { return HumanUser::create(this, userName, userLogin, userEmail); }
    HumanUser *findHumanUserById(const int userId);
    HumanUser *findHumanUserByLogin(const std::string &userLogin);
    HumanUser *findRetiredHumanUser(const std::string &userLogin);
    bool deleteHumanUserById(const int id) { return Entity::deleteSGEntity(this, "HumanUser", id); }

    //------------------------------------------------------------------------
    // Element Entity
    Element createElement(const std::string &projectCode,
                          const std::string &elementName, 
                          const std::string &elementType) 
        { return Element::create(this, projectCode, elementName, elementType); }
    Element *findElementByName(const std::string &projectCode, const std::string &elementName);
    ElementPtrs findElementsByProject(const std::string &projectCode, 
                                      const std::string &elementType = "",
                                      const int limit = 0);
    bool deleteElementById(const int id) { return Entity::deleteSGEntity(this, "Element", id); }

    //------------------------------------------------------------------------
    // Asset Entity
    Asset createAsset(const std::string &projectCode,
                      const std::string &assetName, 
                      const std::string &assetType,
                      const std::string &assetSource = "") 
        { return Asset::create(this, projectCode, assetName, assetType, assetSource); }
    Asset *findAssetByName(const std::string &projectCode, const std::string &assetName);
    AssetPtrs findAssetsByProject(const std::string &projectCode, 
                                  const std::string &assetType = "",
                                  const int limit = 0);
    bool deleteAssetById(const int id) { return Entity::deleteSGEntity(this, "Asset", id); }

    //------------------------------------------------------------------------
    // Delivery Entity
    Delivery createDelivery(const std::string &projectCode, const std::string &deliveryName) 
        { return Delivery::create(this, projectCode, deliveryName); }
    Delivery *findDeliveryByName(const std::string &projectCode, const std::string &deliveryName);
    Delivery *findDeliveryById(const int &deliveryId);
    DeliveryPtrs findDeliveriesByProject(const std::string &projectCode, 
                                         const std::string &deliveryStatus = "",
                                         const int limit = 0);
    bool deleteDeliveryById(const int id) { return Entity::deleteSGEntity(this, "Delivery", id); }

    //------------------------------------------------------------------------
    // PublishEvent Entity
    PublishEvent createPublishEvent(const std::string &projectCode,
                                    const std::string &publishEventName)
        { return PublishEvent::create(this, 
                                      projectCode, 
                                      publishEventName); }
    PublishEvent *findPublishEventByName(const std::string &projectCode, 
                                         const std::string &publishEventName);
    PublishEventPtrs findPublishEventsByProject(const std::string &projectCode, 
                                                const std::string &publishEventType = "",
                                                const int limit = 0);
    bool deletePublishEventById(const int id) { return Entity::deleteSGEntity(this, "PublishEvent", id); }

    //------------------------------------------------------------------------
    // Review Entity
    Review createReview(const std::string &projectCode,
                        const std::string &reviewName) 
        { return Review::create(this, projectCode, reviewName); }
    Review *findReviewByName(const std::string &projectCode, 
                             const std::string &reviewName,
                             const std::string &dateSent = "");
    Review *findReviewById(const int &reviewId);
    ReviewPtrs findReviewsByProject(const std::string &projectCode,
                                    const int limit = 0);
    bool deleteReviewById(const int id) { return Entity::deleteSGEntity(this, "Review", id); }

    //------------------------------------------------------------------------
    // ReviewItem Entity
    ReviewItem createReviewItem(const std::string &projectCode,
                                const std::string &reviewItemName) 
        { return ReviewItem::create(this, 
                                    projectCode,
                                    reviewItemName); }
    ReviewItem *findReviewItemByName(const std::string &projectCode, 
                                     const std::string &reviewItemName);
    ReviewItem *findReviewItemById(const int &reviewItemId);
    ReviewItemPtrs findReviewItemsByProject(const std::string &projectCode, 
                                            const int limit = 0);
    bool deleteReviewItemById(const int id) { return Entity::deleteSGEntity(this, "ReviewItem", id); }

    //------------------------------------------------------------------------
    // Task
    Task createTask(const std::string &projectCode,
                    const std::string &taskName,
                    const std::string &taskType,
                    const std::string &taskAssignee = "",
                    const std::string &taskStartDate = "",
                    const std::string &taskDueDate = "",
                    const std::string &taskStatus = "",
                    const std::string &taskColor = "",
                    const bool taskMilestone = false,
                    const SgMap &taskEntityLink = SgMap())
        { return Task::create(this, 
                              projectCode,
                              taskName,
                              taskType,
                              taskAssignee,
                              taskStartDate,
                              taskDueDate,
                              taskStatus,
                              taskColor,
                              taskMilestone,
                              taskEntityLink); }
    Task *findTaskByName(const std::string &projectCode, const std::string &taskName);
    TaskPtrs findTasksByType(const std::string &projectCode,
                             const std::string &taskType,
                             const std::string &linkEntityType = "",
                             const int limit = 0);
    TaskPtrs findTasksByLinkEntity(const std::string &projectCode,
                                   const SgMap &linkEntity,
                                   const int limit = 0);
    TaskPtrs findTasksByMilestone(const std::string &projectCode,
                                  const std::string &shotName,
                                  const int limit = 0);
    TaskPtrs findTasksByProject(const std::string &projectCode,
                                const int limit = 0);
    bool deleteTaskById(const int id) { return Entity::deleteSGEntity(this, "Task", id); }

    //------------------------------------------------------------------------
    // Group Entity
    Group createGroup(const std::string &groupName) 
        { return Group::create(this, groupName); }
    Group *findGroupByName(const std::string &groupName);
    Group *findGroupById(const int &groupId);
    bool deleteGroupById(const int id) { return Entity::deleteSGEntity(this, "Group", id); }

    //------------------------------------------------------------------------
    // Note
    Note createNote(const std::string &projectCode,
                    const std::string &noteFromUserName,
                    const Strings &noteToUserNames = Strings(),
                    const Strings &noteCcUserNames = Strings(),
                    const std::string &noteSubject = "",
                    const std::string &noteBody = "",
                    const std::string &noteType = "",
                    const SgArray &noteLinks = SgArray(),
                    const std::string &noteOrigin = "")
        { return Note::create(this, 
                              projectCode,
                              noteFromUserName,
                              noteToUserNames,
                              noteCcUserNames,
                              noteSubject,
                              noteBody,
                              noteType,
                              noteLinks,
                              noteOrigin); }
#warning The arg order and the default value have changed. Update .sip
    NotePtrs findNotesByType(const std::string &projectCode,
                             const std::string &noteType,
                             const int limit = 0);
    NotePtrs findNotesByAuthor(const std::string &projectCode,
                               const std::string &userName,
                               const int limit = 0);
    NotePtrs findNotesByLinks(const std::string &projectCode,
                              const SgArray &noteLinks = SgArray(),
                              const std::string &noteType = "",
                              const int limit = 0);
    bool deleteNoteById(const int id) { return Entity::deleteSGEntity(this, "Note", id); }

    //------------------------------------------------------------------------
    // Playlist Entity
    Playlist createPlaylist(const std::string &projectCode,
                            const std::string &playlistName)
        { return Playlist::create(this, projectCode, playlistName); }
    Playlist *findPlaylistByName(const std::string &projectCode, const std::string &playlistName);
    PlaylistPtrs findPlaylistsByProject(const std::string &projectCode, const int limit = 0);
    bool deletePlaylistById(const int id) { return Entity::deleteSGEntity(this, "Playlist", id); }

    //------------------------------------------------------------------------
    // Generic find function by entity type and id
    Entity *findEntityById(const std::string &entityType, const int &id);

    template <class T>
    T *findEntity(const FilterBy &filterList = FilterBy(),
                  const SgArray &extraReturnFields = SgArray(),
                  const bool retiredOnly = false,
                  const SgArray &order = SgArray());

    template <class T>
    std::vector<T *> findEntities(const FilterBy &filterList = FilterBy(),
                                  const int limit = 0,
                                  const SgArray &extraReturnFields = SgArray(),
                                  const bool retiredOnly = false,
                                  const SgArray &order = SgArray());

    ClassRegistry m_classRegistry;

protected:
    std::string m_serverURL;
    std::string m_api;
    xmlrpc_c::clientXmlTransport_curl m_transport;
    xmlrpc_c::client_xml *m_client;
    SgMap m_authMap;

    // Overloaded function that is used within this library
    Entity *findEntity(const std::string &entityType,
                       const FilterBy &filterList = FilterBy(),
                       const SgArray &extraReturnFields = SgArray(),
                       const bool retiredOnly = false,
                       const SgArray &order = SgArray());
};

// *****************************************************************************
// G++ requires template header in the same file as implementation. 
// In practice it means implementation inside .h file.
template <class T>
T *Shotgun::findEntity(const FilterBy &filterList,
                       const SgArray &extraReturnFields,
                       const bool retiredOnly,
                       const SgArray &order)
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
        throw SgEntityDynamicCastError("template type in function: Entity::findEntity(..)");
    }

                            
}


// *****************************************************************************
template <class T>
std::vector<T *> Shotgun::findEntities(const FilterBy &filterList,
                                       const int limit,
                                       const SgArray &extraReturnFields,
                                       const bool retiredOnly,
                                       const SgArray &order)
{
    SgMap findMap = Entity::buildFindMap(T::type(),
                                         filterList,
                                         extraReturnFields,
                                         retiredOnly,
                                         limit,
                                         order);

    EntityPtrs entities = this->entityFactoryFind(T::type(), findMap);
    std::vector<T *> outEntities;

    for (size_t i = 0; i < entities.size(); i++)
    {
        if (T *t = dynamic_cast<T *>(entities[i]))
        {
             outEntities.push_back(t);
        }
    }

    return outEntities;
}

} // End namespace Shotgun

#endif    // End #ifdef __SHOTGUN_H__
