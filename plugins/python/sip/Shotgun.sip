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

namespace Shotgun {

// *****************************************************************************
class Shotgun
{
%TypeHeaderCode
#include <Shotgun/Shotgun.h>
%End

public:
    // TODO: Figure out why this doesn't work:
//    Shotgun(const std::string &serverURL) throw (Shotgun::SgApiError);
    Shotgun(const std::string &serverURL);

    virtual ~Shotgun(); // This might not need to be listed here at all

    //xmlrpc_c::client_xml *client() const; - no need to expose to Python
    const std::string &serverURL() const;
    const std::string &api() const;
    const Shotgun::SgMap &authMap() const;

    // The namespace need to be added to the Method type
    Shotgun::Method *method(const std::string &methodName);

    //-----------------------------------------------------------------------
    // Project Entity
    Shotgun::Project createProject(const std::string &projectName,
                                const std::string &projectCode) throw(Shotgun::SgEntityError);
    Shotgun::Project findProjectByCode(const std::string &projectCode) throw(Shotgun::SgEntityError);
    Shotgun::Project findProjectByName(const std::string &projectName) throw(Shotgun::SgEntityError);
    Shotgun::Projects findProjectsByStatus(const std::string &projectStatus) throw(Shotgun::SgEntityError);
    bool deleteProjectById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // Sequence Entity
    Shotgun::Sequence createSequence(const std::string &projectCode,
                                        const std::string &sequenceName) throw(Shotgun::SgEntityError);
    Shotgun::Sequence findSequenceByName(const std::string &projectCode, 
                                            const std::string &sequenceName) throw(Shotgun::SgEntityError);
    Shotgun::Sequences findSequencesByProject(const std::string &projectCode, 
                                              const int limit = 0) throw(Shotgun::SgEntityError);
    bool deleteSequenceById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // Shot Entity
    Shotgun::Shot createShot(const std::string &shotName, 
                                const std::string &shotType = "") throw(Shotgun::SgEntityError);
    Shotgun::Shot findShotByName(const std::string &shotName) throw(Shotgun::SgEntityError);
    Shotgun::Shots findShotsByProject(const std::string &projectCode, const int limit = 0) throw(Shotgun::SgEntityError);
    bool deleteShotById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // Daily Entity
    Shotgun::Daily createDaily(const std::string &dailyName) throw(Shotgun::SgEntityError);
    Shotgun::Daily findDailyByName(const std::string &dailyName) throw(Shotgun::SgEntityError);
    Shotgun::Dailies findDailiesByProject(const std::string &projectCode, 
                                          const int limit = 0) throw(Shotgun::SgEntityError);
    Shotgun::Dailies findDailiesByShot(const std::string &projectCode, 
                                          const std::string &shotName, 
                                          const int limit = 0) throw(Shotgun::SgEntityError);
    Shotgun::Dailies findDailiesByReviewStatus(const std::string &projectCode, 
                                                  const std::string &reviewStatus,
                                                  const int limit = 0) throw(Shotgun::SgEntityError);
    bool deleteDailyById(const int id) throw(Shotgun::SgEntityError);

    //-----------------------------------------------------------------------
    // User Entity
    Shotgun::User createUser(const std::string &userName,
                                const std::string &userLogin,
                                const std::string &userEmail,
                                const std::string &userDept) throw(Shotgun::SgEntityError);
    Shotgun::User findUserById(const int userId) throw(Shotgun::SgEntityError);
    Shotgun::User findUserByLogin(const std::string &userLogin) throw(Shotgun::SgEntityError);
    Shotgun::User findRetiredUser(const std::string &userLogin) throw(Shotgun::SgEntityError);
    bool deleteUserById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // Element Entity
    Shotgun::Element createElement(const std::string &projectCode,
                                      const std::string &elementName, 
                                      const std::string &elementType) throw(Shotgun::SgEntityError);
    Shotgun::Element findElementByName(const std::string &projectCode, 
                                          const std::string &elementName) throw(Shotgun::SgEntityError);
    Shotgun::Elements findElementsByProject(const std::string &projectCode,
                                            const std::string &elementType = "",
                                            const int limit = 0) throw(Shotgun::SgEntityError);
    bool deleteElementById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // Asset Entity
    Shotgun::Asset createAsset(const std::string &projectCode,
                                  const std::string &assetName, 
                                  const std::string &assetType,
                                  const std::string &assetSource = "") throw(Shotgun::SgEntityError);
    Shotgun::Asset findAssetByName(const std::string &projectCode, 
                                      const std::string &assetName) throw(Shotgun::SgEntityError);
    Shotgun::Assets findAssetsByProject(const std::string &projectCode,
                                        const std::string &assetType = "",
                                        const int limit = 0) throw(Shotgun::SgEntityError);
    bool deleteAssetById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // Delivery Entity
    Shotgun::Delivery createDelivery(const std::string &projectCode,
                                        const std::string &deliveryName) throw(Shotgun::SgEntityError);
    Shotgun::Delivery findDeliveryByName(const std::string &projectCode, 
                                            const std::string &deliveryName) throw(Shotgun::SgEntityError);
    Shotgun::Delivery findDeliveryById(const int &deliveryId) throw(Shotgun::SgEntityError);
    Shotgun::Deliveries findDeliveriesByProject(const std::string &projectCode,
                                                const std::string &deliveryStatus = "",
                                                const int limit = 0) throw(Shotgun::SgEntityError);
    bool deleteDeliveryById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // DeliveryItem Entity
    Shotgun::DeliveryItem createDeliveryItem(const std::string &projectCode,
                                                const std::string &deliveryItemName,
                                                const Shotgun::SgMap &deliveryLink = Shotgun::SgMap()) throw(Shotgun::SgEntityError);
    Shotgun::DeliveryItem findDeliveryItemByName(const std::string &projectCode,
                                                    const std::string &deliveryItemName) throw(Shotgun::SgEntityError);
    Shotgun::DeliveryItem findDeliveryItemById(const int &deliveryItemId) throw(Shotgun::SgEntityError);
    Shotgun::DeliveryItems findDeliveryItemsByProject(const std::string &projectCode,
                                                      const int limit = 0) throw(Shotgun::SgEntityError);
    bool deleteDeliveryItemById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // PublishEvent Entity
    Shotgun::PublishEvent createPublishEvent(const std::string &projectCode,
                                                const std::string &publishEventName,
                                                const std::string &publishEventSource,
                                                const std::string &publishEventType = "",
                                                const int publishEventVersion = TIPSHOTGUN_INVALID_VERSION_NUM,
                                                const std::string &publishEventResolution = "") throw(Shotgun::SgEntityError);
    Shotgun::PublishEvent findPublishEventByName(const std::string &projectCode,
                                                    const std::string &publishEventName) throw(Shotgun::SgEntityError);
    Shotgun::PublishEvents findPublishEventsByProject(const std::string &projectCode,
                                                      const std::string &publishEventType,
                                                      const int limit = 0) throw(Shotgun::SgEntityError);
    bool deletePublishEventById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // Review Entity
    Shotgun::Review createReview(const std::string &projectCode,
                                    const std::string &reviewName, 
                                    const std::string &reviewType) throw(Shotgun::SgEntityError);
    Shotgun::Review findReviewByName(const std::string &projectCode, 
                                        const std::string &reviewName,
                                        const std::string &dateSent = "") throw(Shotgun::SgEntityError);
    Shotgun::Review findReviewById(const int &reviewId) throw(Shotgun::SgEntityError);
    Shotgun::Reviews findReviewsByProject(const std::string &projectCode,
                                          const std::string &reviewType = "",
                                          const int limit = 0) throw(Shotgun::SgEntityError);
    bool deleteReviewById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // ReviewItem Entity
    Shotgun::ReviewItem createReviewItem(const std::string &projectCode,
                                            const Shotgun::SgMap &reviewItemShotLink,
                                            const Shotgun::SgMap &reviewItemDailyLink,
                                            const Shotgun::SgMap &reviewItemReviewLink,
                                            const std::string &reviewItemPurpose = "",
                                            const int reviewItemOrder = TIPSHOTGUN_INVALID_ORDER_NUM) throw(Shotgun::SgEntityError);
    Shotgun::ReviewItem findReviewItemByName(const std::string &projectCode, 
                                                const std::string &reviewItemName) throw(Shotgun::SgEntityError);
    Shotgun::ReviewItem findReviewItemById(const int &reviewItemId) throw(Shotgun::SgEntityError);
    Shotgun::ReviewItems findReviewItemsByProject(const std::string &projectCode,
                                                  const int limit = 0) throw(Shotgun::SgEntityError);
    bool deleteReviewItemById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // Task
    Shotgun::Task createTask(const std::string &projectCode,
                                const std::string &taskName,
                                const std::string &taskType,
                                const int taskViewOrder = TIPSHOTGUN_INVALID_ORDER_NUM,
                                const std::string &taskAssignee = "",
                                const std::string &taskStartDate = "",
                                const std::string &taskDueDate = "",
                                const std::string &taskStatus = "",
                                const std::string &taskColor = "",
                                const bool taskMilestone = false,
                                const Shotgun::SgMap &taskEntityLink = Shotgun::SgMap()) throw(Shotgun::SgEntityError);
    Shotgun::Task findTaskByName(const std::string &projectCode, 
                                    const std::string &taskName) throw(Shotgun::SgEntityError);
    Shotgun::Tasks findTasksByType(const std::string &projectCode,
                                      const std::string &taskType,
                                      const std::string &linkEntityType = "",
                                      const int limit = 0) throw(Shotgun::SgEntityError);
    Shotgun::Tasks findTasksByLinkEntity(const std::string &projectCode,
                                            const Shotgun::SgMap &linkEntity,
                                            const int limit = 0) throw(Shotgun::SgEntityError);
    Shotgun::Tasks findTasksByMilestone(const std::string &projectCode,
                                           const std::string &shotName,
                                           const int limit = 0) throw(Shotgun::SgEntityError);
    Shotgun::Tasks findTasksByProject(const std::string &projectCode,
                                      const int limit = 0) throw(Shotgun::SgEntityError);
    bool deleteTaskById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // Group Entity
    Shotgun::Group createGroup(const std::string &groupName) throw(Shotgun::SgEntityError);
    Shotgun::Group findGroupByName(const std::string &groupName) throw(Shotgun::SgEntityError);
    Shotgun::Group findGroupById(const int &groupId) throw(Shotgun::SgEntityError);
    bool deleteGroupById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // Note
    Shotgun::Note createNote(const std::string &projectCode,
                                const std::string &noteFromUserName,
                                const Shotgun::Strings &noteToUserNames = Shotgun::Strings(),
                                const Shotgun::Strings &noteCcUserNames = Shotgun::Strings(),
                                const std::string &noteSubject = "",
                                const std::string &noteBody = "",
                                const std::string &noteType = "",
                                const Shotgun::SgArray &noteLinks = Shotgun::SgArray(),
                                const std::string &noteOrigin = "") throw(Shotgun::SgEntityError);
    Shotgun::Notes findNotesByType(const std::string &noteType,
                                      const std::string &projectCode = "",
                                      const int limit = 0) throw(Shotgun::SgEntityError);
    Shotgun::Notes findNotesByAuthor(const std::string &userName,
                                        const std::string &projectCode = "",
                                        const int limit = 0) throw(Shotgun::SgEntityError);
    Shotgun::Notes findNotesByLinks(const Shotgun::SgArray &noteLinks = Shotgun::SgArray(),
                                       const std::string &noteType = "",
                                       const std::string &projectCode = "",
                                       const int limit = 0) throw(Shotgun::SgEntityError);
    bool deleteNoteById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // Reference Entity
    Shotgun::Reference createReference(const std::string &projectCode,
                                          const std::string &referencePath,
                                          const std::string &referencePurpose = "",
                                          const Shotgun::Strings &linkAssets = Shotgun::Strings(),
                                          const Shotgun::Strings &linkSequences = Shotgun::Strings(),
                                          const Shotgun::Strings &linkShots = Shotgun::Strings(),
                                          const Shotgun::Strings &tags = Shotgun::Strings()) throw(Shotgun::SgEntityError);
    Shotgun::Reference findReferenceByPath(const std::string &projectCode, 
                                              const std::string &referencePath) throw(Shotgun::SgEntityError);
    Shotgun::Reference findReferenceByName(const std::string &projectCode, 
                                              const std::string &referenceName) throw(Shotgun::SgEntityError);
    Shotgun::References findReferencesByProject(const std::string &projectCode, 
                                                const int limit = 0);
    bool deleteReferenceById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // Playlist Entity
    Shotgun::Playlist createPlaylist(const std::string &projectCode,
                                        const std::string &playlistName) throw(Shotgun::SgEntityError);
    Shotgun::Playlist findPlaylistByName(const std::string &projectCode, 
                                            const std::string &playlistName) throw(Shotgun::SgEntityError);
    Shotgun::Playlists findPlaylistsByProject(const std::string &projectCode, const int limit = 0);
    bool deletePlaylistById(const int id) throw(Shotgun::SgEntityError);

    //------------------------------------------------------------------------
    // Generic find function by entity type and id
    Shotgun::Entity *findEntityById(const std::string &entityType, 
                                       const int &id) throw(Shotgun::SgEntityError) /Factory/;

    //------------------------------------------------------------------------
    // Generic entity search functions with user-constructable findMap.
    Shotgun::Projects findProjects(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::Sequences findSequences(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::Shots findShots(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::Dailies findDailies(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::Users findUsers(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::Elements findElements(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::Assets findAssets(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::Deliveries findDeliveries(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::DeliveryItems findDeliveryItems(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::PublishEvents findPublishEvents(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::Reviews findReviews(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::ReviewItems findReviewItems(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::Tasks findTasks(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::Groups findGroups(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::Notes findNotes(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::References findReferences(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
    Shotgun::Playlists findPlaylists(Shotgun::SgMap &findMap) throw(Shotgun::SgEntityError);
};

}; // End namespace Shotgun - IMPORTANT: must have the semi-colon
