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

#include <Shotgun/Type.h>
#include <Shotgun/Method.h>
#include <Shotgun/Project.h>
#include <Shotgun/Sequence.h>
#include <Shotgun/Shot.h>
#include <Shotgun/Version.h>
#include <Shotgun/User.h>
#include <Shotgun/Element.h>
#include <Shotgun/Asset.h>
#include <Shotgun/Delivery.h>
#include <Shotgun/PublishEvent.h>
#include <Shotgun/Review.h>
#include <Shotgun/ReviewItem.h>
#include <Shotgun/Task.h>
#include <Shotgun/Group.h>
#include <Shotgun/Note.h>
#include <Shotgun/Reference.h>
#include <Shotgun/Playlist.h>

namespace Shotgun {

class TaskMixin;
class NoteMixin;

// *****************************************************************************
class Shotgun
{
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

    //-----------------------------------------------------------------------
    // Project Entity
    Project createProject(const std::string &projectName, const std::string &projectCode) 
        { return Project::create(this, projectName, projectCode); }
    Project findProjectByCode(const std::string &projectCode);
    Project findProjectByName(const std::string &projectName);
    Projects findProjectsByStatus(const std::string &projectStatus);
    bool deleteProjectById(const int id) { return Entity::deleteEntity(this, "Project", id); }

    //------------------------------------------------------------------------
    // Sequence Entity
    Sequence createSequence(const std::string &projectCode, const std::string &sequenceName) 
        { return Sequence::create(this, projectCode, sequenceName); }
    Sequence findSequenceByName(const std::string &projectCode, const std::string &sequenceName);
    Sequences findSequencesByProject(const std::string &projectCode, const int limit = 0);
    bool deleteSequenceById(const int id) { return Entity::deleteEntity(this, "Sequence", id); }

    //------------------------------------------------------------------------
    // Shot Entity
    Shot createShot(const std::string &shotName, const std::string &shotType = "") 
        { return Shot::create(this, shotName, shotType); }
    Shot findShotByName(const std::string &shotName);
    Shots findShotsByProject(const std::string &projectCode, const int limit = 0);
    bool deleteShotById(const int id) { return Entity::deleteEntity(this, "Shot", id); }

    //------------------------------------------------------------------------
    // Version Entity
    Version createVersion(const std::string &versionName) 
        { return Version::create(this, versionName); }
    Version findVersionByName(const std::string &versionName);
    Versions findVersionsByProject(const std::string &projectCode, const int limit = 0);
    Versions findVersionsByShot(const std::string &projectCode, 
                              const std::string &shotName, 
                              const int limit = 0);
    Versions findVersionsByReviewStatus(const std::string &projectCode, 
                                      const std::string &reviewStatus,
                                      const int limit = 0);
    bool deleteVersionById(const int id) { return Entity::deleteEntity(this, "Version", id); }

    //-----------------------------------------------------------------------
    // User Entity
    User createUser(const std::string &userName,
                    const std::string &userLogin,
                    const std::string &userEmail,
                    const std::string &userDept)
        { return User::create(this, userName, userLogin, userEmail, userDept); }
    User findUserById(const int userId);
    User findUserByLogin(const std::string &userLogin);
    User findRetiredUser(const std::string &userLogin);
    bool deleteUserById(const int id) { return Entity::deleteEntity(this, "HumanUser", id); }

    //------------------------------------------------------------------------
    // Element Entity
    Element createElement(const std::string &projectCode,
                          const std::string &elementName, 
                          const std::string &elementType) 
        { return Element::create(this, projectCode, elementName, elementType); }
    Element findElementByName(const std::string &projectCode, const std::string &elementName);
    Elements findElementsByProject(const std::string &projectCode, 
                                const std::string &elementType = "",
                                const int limit = 0);
    bool deleteElementById(const int id) { return Entity::deleteEntity(this, "Element", id); }

    //------------------------------------------------------------------------
    // Asset Entity
    Asset createAsset(const std::string &projectCode,
                      const std::string &assetName, 
                      const std::string &assetType,
                      const std::string &assetSource = "") 
        { return Asset::create(this, projectCode, assetName, assetType, assetSource); }
    Asset findAssetByName(const std::string &projectCode, const std::string &assetName);
    Assets findAssetsByProject(const std::string &projectCode, 
                            const std::string &assetType = "",
                            const int limit = 0);
    bool deleteAssetById(const int id) { return Entity::deleteEntity(this, "Asset", id); }

    //------------------------------------------------------------------------
    // Delivery Entity
    Delivery createDelivery(const std::string &projectCode, const std::string &deliveryName) 
        { return Delivery::create(this, projectCode, deliveryName); }
    Delivery findDeliveryByName(const std::string &projectCode, const std::string &deliveryName);
    Delivery findDeliveryById(const int &deliveryId);
    Deliveries findDeliveriesByProject(const std::string &projectCode, 
                                    const std::string &deliveryStatus = "",
                                    const int limit = 0);
    bool deleteDeliveryById(const int id) { return Entity::deleteEntity(this, "Delivery", id); }


    //------------------------------------------------------------------------
    // PublishEvent Entity
    PublishEvent createPublishEvent(const std::string &projectCode,
                                    const std::string &publishEventName, 
                                    const std::string &publishEventSource,
                                    const std::string &publishEventType = "",
                                    const int publishEventVersion = TIPSHOTGUN_INVALID_VERSION_NUM,
                                    const std::string &publishEventResolution = "")
        { return PublishEvent::create(this, 
                                      projectCode, 
                                      publishEventName, 
                                      publishEventSource, 
                                      publishEventType,
                                      publishEventVersion,
                                      publishEventResolution); }
    PublishEvent findPublishEventByName(const std::string &projectCode, 
                                        const std::string &publishEventName);
    PublishEvents findPublishEventsByProject(const std::string &projectCode, 
                                          const std::string &publishEventType = "",
                                          const int limit = 0);
    bool deletePublishEventById(const int id) { return Entity::deleteEntity(this, "PublishEvent", id); }

    //------------------------------------------------------------------------
    // Review Entity
    Review createReview(const std::string &projectCode,
                        const std::string &reviewName, 
                        const std::string &reviewType) 
        { return Review::create(this, projectCode, reviewName, reviewType); }
    Review findReviewByName(const std::string &projectCode, 
                            const std::string &reviewName,
                            const std::string &dateSent = "");
    Review findReviewById(const int &reviewId);
    Reviews findReviewsByProject(const std::string &projectCode, 
                              const std::string &reviewType = "",
                              const int limit = 0);
    bool deleteReviewById(const int id) { return Entity::deleteEntity(this, "Review", id); }

    //------------------------------------------------------------------------
    // ReviewItem Entity
    ReviewItem createReviewItem(const std::string &projectCode,
                                const SgMap &reviewItemShotLink,
                                const SgMap &reviewItemDailyLink,
                                const SgMap &reviewItemReviewLink,
                                const std::string &reviewItemPurpose = "",
                                const int reviewItemOrder = TIPSHOTGUN_INVALID_ORDER_NUM) 
        { return ReviewItem::create(this, 
                                    projectCode,
                                    reviewItemShotLink,
                                    reviewItemDailyLink,
                                    reviewItemReviewLink,
                                    reviewItemPurpose,
                                    reviewItemOrder); }
    ReviewItem findReviewItemByName(const std::string &projectCode, const std::string &reviewItemName);
    ReviewItem findReviewItemById(const int &reviewItemId);
    ReviewItems findReviewItemsByProject(const std::string &projectCode, 
                                      const int limit = 0);
    bool deleteReviewItemById(const int id) { return Entity::deleteEntity(this, "ReviewItem", id); }

    //------------------------------------------------------------------------
    // Task
    Task createTask(const std::string &projectCode,
                    const std::string &taskName,
                    const std::string &taskType,
                    const int taskViewOrder = TIPSHOTGUN_INVALID_ORDER_NUM,
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
                              taskViewOrder,
                              taskAssignee,
                              taskStartDate,
                              taskDueDate,
                              taskStatus,
                              taskColor,
                              taskMilestone,
                              taskEntityLink); }
    Task findTaskByName(const std::string &projectCode, const std::string &taskName);
    Tasks findTasksByType(const std::string &projectCode,
                          const std::string &taskType,
                          const std::string &linkEntityType = "",
                          const int limit = 0);
    Tasks findTasksByLinkEntity(const std::string &projectCode,
                                const SgMap &linkEntity,
                                const int limit = 0);
    Tasks findTasksByMilestone(const std::string &projectCode,
                               const std::string &shotName,
                               const int limit = 0);
    Tasks findTasksByProject(const std::string &projectCode,
                          const int limit = 0);
    bool deleteTaskById(const int id) { return Entity::deleteEntity(this, "Task", id); }

    //------------------------------------------------------------------------
    // Group Entity
    Group createGroup(const std::string &groupName) 
        { return Group::create(this, groupName); }
    Group findGroupByName(const std::string &groupName);
    Group findGroupById(const int &groupId);
    bool deleteGroupById(const int id) { return Entity::deleteEntity(this, "Group", id); }

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
    Notes findNotesByType(const std::string &noteType,
                          const std::string &projectCode = "",
                          const int limit = 0);
    Notes findNotesByAuthor(const std::string &userName,
                            const std::string &projectCode = "",
                            const int limit = 0);
    Notes findNotesByLinks(const SgArray &noteLinks = SgArray(),
                           const std::string &noteType = "",
                           const std::string &projectCode = "",
                           const int limit = 0);
    bool deleteNoteById(const int id) { return Entity::deleteEntity(this, "Note", id); }

    //------------------------------------------------------------------------
    // Reference Entity
    Reference createReference(const std::string &projectCode,
                              const std::string &referencePath,
                              const std::string &referencePurpose = "",
                              const Strings &linkAssets = Strings(),
                              const Strings &linkSequences = Strings(),
                              const Strings &linkShots = Strings(),
                              const Strings &tags = Strings()) 
        { return Reference::create(this, 
                                   projectCode,
                                   referencePath,
                                   referencePurpose,
                                   linkAssets,
                                   linkSequences,
                                   linkShots,
                                   tags); }
    Reference findReferenceByPath(const std::string &projectCode, const std::string &referencePath);
    Reference findReferenceByName(const std::string &projectCode, const std::string &referenceName);
    References findReferencesByProject(const std::string &projectCode, const int limit = 0);
    bool deleteReferenceById(const int id) { return Entity::deleteEntity(this, "CustomEntity02", id); }

    //------------------------------------------------------------------------
    // Playlist Entity
    Playlist createPlaylist(const std::string &projectCode,
                            const std::string &playlistName)
        { return Playlist::create(this, projectCode, playlistName); }
    Playlist findPlaylistByName(const std::string &projectCode, const std::string &playlistName);
    Playlists findPlaylistsByProject(const std::string &projectCode, const int limit = 0);
    bool deletePlaylistById(const int id) { return Entity::deleteEntity(this, "Playlist", id); }

    //------------------------------------------------------------------------
    // Generic find function by entity type and id
    Entity *findEntityById(const std::string &entityType, const int &id);

    //------------------------------------------------------------------------
    // Generic entity search functions with user-constructable findMap 
    Projects findProjects(SgMap &findMap) { return Project::find(this, findMap); }
    Sequences findSequences(SgMap &findMap) { return Sequence::find(this, findMap); }
    Shots findShots(SgMap &findMap) { return Shot::find(this, findMap); }
    Versions findVersions(SgMap &findMap) { return Version::find(this, findMap); }
    Users findUsers(SgMap &findMap) { return User::find(this, findMap); }
    Elements findElements(SgMap &findMap) { return Element::find(this, findMap); }
    Assets findAssets(SgMap &findMap) { return Asset::find(this, findMap); }
    Deliveries findDeliveries(SgMap &findMap) { return Delivery::find(this, findMap); }
    PublishEvents findPublishEvents(SgMap &findMap) { return PublishEvent::find(this, findMap); }
    Reviews findReviews(SgMap &findMap) { return Review::find(this, findMap); }
    ReviewItems findReviewItems(SgMap &findMap) { return ReviewItem::find(this, findMap); }
    Tasks findTasks(SgMap &findMap) { return Task::find(this, findMap); }
    Groups findGroups(SgMap &findMap) { return Group::find(this, findMap); }
    Notes findNotes(SgMap &findMap) { return Note::find(this, findMap); }
    References findReferences(SgMap &findMap) { return Reference::find(this, findMap); }
    Playlists findPlaylists(SgMap &findMap) { return Playlist::find(this, findMap); }

protected:
    std::string m_serverURL;
    std::string m_api;
    xmlrpc_c::clientXmlTransport_curl m_transport;
    xmlrpc_c::client_xml *m_client;
    SgMap m_authMap;
};

} // End namespace Shotgun

#endif    // End #ifdef __SHOTGUN_H__
