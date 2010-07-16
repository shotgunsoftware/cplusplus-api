//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$ 
//******************************************************************************

#ifndef __SHOTGUN_H__
#define __SHOTGUN_H__

#include <exception>

#include <Shotgun/Type.h>
#include <Shotgun/Method.h>
#include <Shotgun/Show.h>
#include <Shotgun/Sequence.h>
#include <Shotgun/Shot.h>
#include <Shotgun/Daily.h>
#include <Shotgun/User.h>
#include <Shotgun/Element.h>
#include <Shotgun/Asset.h>
#include <Shotgun/Delivery.h>
#include <Shotgun/DeliveryItem.h>
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
    Shotgun(const std::string &serverURL);
    virtual ~Shotgun();

    xmlrpc_c::client_xml *client() const { return m_client; }
    const std::string &serverURL() const { return m_serverURL; }
    const std::string &api() const { return m_api; }
    const SgMap &authMap() const { return m_authMap; } 

    Method *method(const std::string &methodName) 
        { return new Method(this, methodName); }

    //-----------------------------------------------------------------------
    // Show Entity
    Show createShow(const std::string &showName, const std::string &showCode) 
        { return Show::create(this, showName, showCode); }
    Show findShowByCode(const std::string &showCode);
    Show findShowByName(const std::string &showName);
    Shows findShowsByStatus(const std::string &showStatus);
    bool deleteShowById(const int id) { return Entity::deleteEntity(this, "Project", id); }

    //------------------------------------------------------------------------
    // Sequence Entity
    Sequence createSequence(const std::string &showCode, const std::string &sequenceName) 
        { return Sequence::create(this, showCode, sequenceName); }
    Sequence findSequenceByName(const std::string &showCode, const std::string &sequenceName);
    Sequences findSequencesByShow(const std::string &showCode, const int limit = 0);
    bool deleteSequenceById(const int id) { return Entity::deleteEntity(this, "Sequence", id); }

    //------------------------------------------------------------------------
    // Shot Entity
    Shot createShot(const std::string &shotName, const std::string &shotType = "") 
        { return Shot::create(this, shotName, shotType); }
    Shot findShotByName(const std::string &shotName);
    Shots findShotsByShow(const std::string &showCode, const int limit = 0);
    bool deleteShotById(const int id) { return Entity::deleteEntity(this, "Shot", id); }

    //------------------------------------------------------------------------
    // Daily Entity
    Daily createDaily(const std::string &dailyName) 
        { return Daily::create(this, dailyName); }
    Daily findDailyByName(const std::string &dailyName);
    Dailies findDailiesByShow(const std::string &showCode, const int limit = 0);
    Dailies findDailiesByShot(const std::string &showCode, 
                              const std::string &shotName, 
                              const int limit = 0);
    Dailies findDailiesByReviewStatus(const std::string &showCode, 
                                      const std::string &reviewStatus,
                                      const int limit = 0);
    bool deleteDailyById(const int id) { return Entity::deleteEntity(this, "Version", id); }

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
    Element createElement(const std::string &showCode,
                          const std::string &elementName, 
                          const std::string &elementType) 
        { return Element::create(this, showCode, elementName, elementType); }
    Element findElementByName(const std::string &showCode, const std::string &elementName);
    Elements findElementsByShow(const std::string &showCode, 
                                const std::string &elementType = "",
                                const int limit = 0);
    bool deleteElementById(const int id) { return Entity::deleteEntity(this, "Element", id); }

    //------------------------------------------------------------------------
    // Asset Entity
    Asset createAsset(const std::string &showCode,
                      const std::string &assetName, 
                      const std::string &assetType,
                      const std::string &assetSource = "") 
        { return Asset::create(this, showCode, assetName, assetType, assetSource); }
    Asset findAssetByName(const std::string &showCode, const std::string &assetName);
    Assets findAssetsByShow(const std::string &showCode, 
                            const std::string &assetType = "",
                            const int limit = 0);
    bool deleteAssetById(const int id) { return Entity::deleteEntity(this, "Asset", id); }

    //------------------------------------------------------------------------
    // Delivery Entity
    Delivery createDelivery(const std::string &showCode, const std::string &deliveryName) 
        { return Delivery::create(this, showCode, deliveryName); }
    Delivery findDeliveryByName(const std::string &showCode, const std::string &deliveryName);
    Delivery findDeliveryById(const int &deliveryId);
    Deliveries findDeliveriesByShow(const std::string &showCode, 
                                    const std::string &deliveryStatus = "",
                                    const int limit = 0);
    bool deleteDeliveryById(const int id) { return Entity::deleteEntity(this, "Delivery", id); }

    //------------------------------------------------------------------------
    // DeliveryItem Entity
    DeliveryItem createDeliveryItem(const std::string &showCode,
                                    const std::string &deliveryItemName,
                                    const SgMap &deliveryLink = SgMap()) 
        { return DeliveryItem::create(this, showCode, deliveryItemName, deliveryLink); }
    DeliveryItem findDeliveryItemByName(const std::string &showCode, 
                                        const std::string &deliveryItemName);
    DeliveryItem findDeliveryItemById(const int &deliveryItemId);
    DeliveryItems findDeliveryItemsByShow(const std::string &showCode, 
                                          const int limit = 0);
    bool deleteDeliveryItemById(const int id) { return Entity::deleteEntity(this, "CustomEntity01", id); }

    //------------------------------------------------------------------------
    // PublishEvent Entity
    PublishEvent createPublishEvent(const std::string &showCode,
                                    const std::string &publishEventName, 
                                    const std::string &publishEventSource,
                                    const std::string &publishEventType = "",
                                    const int publishEventVersion = TIPSHOTGUN_INVALID_VERSION_NUM,
                                    const std::string &publishEventResolution = "")
        { return PublishEvent::create(this, 
                                      showCode, 
                                      publishEventName, 
                                      publishEventSource, 
                                      publishEventType,
                                      publishEventVersion,
                                      publishEventResolution); }
    PublishEvent findPublishEventByName(const std::string &showCode, 
                                        const std::string &publishEventName);
    PublishEvents findPublishEventsByShow(const std::string &showCode, 
                                          const std::string &publishEventType = "",
                                          const int limit = 0);
    bool deletePublishEventById(const int id) { return Entity::deleteEntity(this, "PublishEvent", id); }

    //------------------------------------------------------------------------
    // Review Entity
    Review createReview(const std::string &showCode,
                        const std::string &reviewName, 
                        const std::string &reviewType) 
        { return Review::create(this, showCode, reviewName, reviewType); }
    Review findReviewByName(const std::string &showCode, 
                            const std::string &reviewName,
                            const std::string &dateSent = "");
    Review findReviewById(const int &reviewId);
    Reviews findReviewsByShow(const std::string &showCode, 
                              const std::string &reviewType = "",
                              const int limit = 0);
    bool deleteReviewById(const int id) { return Entity::deleteEntity(this, "Review", id); }

    //------------------------------------------------------------------------
    // ReviewItem Entity
    ReviewItem createReviewItem(const std::string &showCode,
                                const SgMap &reviewItemShotLink,
                                const SgMap &reviewItemDailyLink,
                                const SgMap &reviewItemReviewLink,
                                const std::string &reviewItemPurpose = "",
                                const int reviewItemOrder = TIPSHOTGUN_INVALID_ORDER_NUM) 
        { return ReviewItem::create(this, 
                                    showCode,
                                    reviewItemShotLink,
                                    reviewItemDailyLink,
                                    reviewItemReviewLink,
                                    reviewItemPurpose,
                                    reviewItemOrder); }
    ReviewItem findReviewItemByName(const std::string &showCode, const std::string &reviewItemName);
    ReviewItem findReviewItemById(const int &reviewItemId);
    ReviewItems findReviewItemsByShow(const std::string &showCode, 
                                      const int limit = 0);
    bool deleteReviewItemById(const int id) { return Entity::deleteEntity(this, "ReviewItem", id); }

    //------------------------------------------------------------------------
    // Task
    Task createTask(const std::string &showCode,
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
                              showCode,
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
    Task findTaskByName(const std::string &showCode, const std::string &taskName);
    Tasks findTasksByType(const std::string &showCode,
                          const std::string &taskType,
                          const std::string &linkEntityType = "",
                          const int limit = 0);
    Tasks findTasksByLinkEntity(const std::string &showCode,
                                const SgMap &linkEntity,
                                const int limit = 0);
    Tasks findTasksByMilestone(const std::string &showCode,
                               const std::string &shotName,
                               const int limit = 0);
    Tasks findTasksByShow(const std::string &showCode,
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
    Note createNote(const std::string &showCode,
                    const std::string &noteFromUserName,
                    const Strings &noteToUserNames = Strings(),
                    const Strings &noteCcUserNames = Strings(),
                    const std::string &noteSubject = "",
                    const std::string &noteBody = "",
                    const std::string &noteType = "",
                    const SgArray &noteLinks = SgArray(),
                    const std::string &noteOrigin = "")
        { return Note::create(this, 
                              showCode,
                              noteFromUserName,
                              noteToUserNames,
                              noteCcUserNames,
                              noteSubject,
                              noteBody,
                              noteType,
                              noteLinks,
                              noteOrigin); }
    Notes findNotesByType(const std::string &noteType,
                          const std::string &showCode = "",
                          const int limit = 0);
    Notes findNotesByAuthor(const std::string &userName,
                            const std::string &showCode = "",
                            const int limit = 0);
    Notes findNotesByLinks(const SgArray &noteLinks = SgArray(),
                           const std::string &noteType = "",
                           const std::string &showCode = "",
                           const int limit = 0);
    bool deleteNoteById(const int id) { return Entity::deleteEntity(this, "Note", id); }

    //------------------------------------------------------------------------
    // Reference Entity
    Reference createReference(const std::string &showCode,
                              const std::string &referencePath,
                              const std::string &referencePurpose = "",
                              const Strings &linkAssets = Strings(),
                              const Strings &linkSequences = Strings(),
                              const Strings &linkShots = Strings(),
                              const Strings &tags = Strings()) 
        { return Reference::create(this, 
                                   showCode,
                                   referencePath,
                                   referencePurpose,
                                   linkAssets,
                                   linkSequences,
                                   linkShots,
                                   tags); }
    Reference findReferenceByPath(const std::string &showCode, const std::string &referencePath);
    Reference findReferenceByName(const std::string &showCode, const std::string &referenceName);
    References findReferencesByShow(const std::string &showCode, const int limit = 0);
    bool deleteReferenceById(const int id) { return Entity::deleteEntity(this, "CustomEntity02", id); }

    //------------------------------------------------------------------------
    // Playlist Entity
    Playlist createPlaylist(const std::string &showCode,
                            const std::string &playlistName)
        { return Playlist::create(this, showCode, playlistName); }
    Playlist findPlaylistByName(const std::string &showCode, const std::string &playlistName);
    Playlists findPlaylistsByShow(const std::string &showCode, const int limit = 0);
    bool deletePlaylistById(const int id) { return Entity::deleteEntity(this, "Playlist", id); }

    //------------------------------------------------------------------------
    // Generic find function by entity type and id
    Entity *findEntityById(const std::string &entityType, const int &id);

    //------------------------------------------------------------------------
    // Generic entity search functions with user-constructable findMap 
    Shows findShows(SgMap &findMap) { return Show::find(this, findMap); }
    Sequences findSequences(SgMap &findMap) { return Sequence::find(this, findMap); }
    Shots findShots(SgMap &findMap) { return Shot::find(this, findMap); }
    Dailies findDailies(SgMap &findMap) { return Daily::find(this, findMap); }
    Users findUsers(SgMap &findMap) { return User::find(this, findMap); }
    Elements findElements(SgMap &findMap) { return Element::find(this, findMap); }
    Assets findAssets(SgMap &findMap) { return Asset::find(this, findMap); }
    Deliveries findDeliveries(SgMap &findMap) { return Delivery::find(this, findMap); }
    DeliveryItems findDeliveryItems(SgMap &findMap) { return DeliveryItem::find(this, findMap); }
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
