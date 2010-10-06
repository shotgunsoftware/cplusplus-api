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
    Shotgun(const std::string &serverURL = SG_DEFAULT_URL,
            const std::string &authKey = SG_AUTHENTICATION_KEY);
    virtual ~Shotgun();

    const std::string &serverURL() const throw(Shotgun::SgError);
    const std::string &authKey() const;
    const std::string &api() const;
    const Shotgun::Dict &authMap() const;

    Shotgun::Method *method(const std::string &methodName);

    //-----------------------------------------------------------------------
    // Project Entity
    Shotgun::Project *createProject(const std::string &projectName, 
                                    const std::string &projectCode) throw(Shotgun::SgError) /Factory/; 
    Shotgun::Project *findProjectByCode(const std::string &projectCode) throw(Shotgun::SgError) /Factory/;
    Shotgun::Project *findProjectByName(const std::string &projectName) throw(Shotgun::SgError) /Factory/;
    Shotgun::ProjectPtrs allProjects() throw(Shotgun::SgError) /Factory/;
    Shotgun::Dict getProjectLink(const std::string &projectCode) throw(Shotgun::SgError);

//     //------------------------------------------------------------------------
//     // Sequence Entity
//     Shotgun::Sequence *createSequence(const std::string &projectCode, 
//                                       const std::string &sequenceName) throw(Shotgun::SgError) /Factory/; 
//     Shotgun::Sequence *findSequenceByName(const std::string &projectCode, 
//                                           const std::string &sequenceName) throw(Shotgun::SgError) /Factory/;
//     Shotgun::SequencePtrs findSequencesByProject(const std::string &projectCode, 
//                                                  const int limit = 0) throw(Shotgun::SgError) /Factory/;
// 
//     //------------------------------------------------------------------------
//     // Shot Entity
//     Shotgun::Shot *createShot(const std::string &shotName, 
//                               const std::string &shotType = "") throw(Shotgun::SgError) /Factory/; 
//     Shotgun::Shot *findShotByName(const std::string &shotName) throw(Shotgun::SgError) /Factory/;
//     Shotgun::ShotPtrs findShotsByProject(const std::string &projectCode, 
//                                          const int limit = 0) throw(Shotgun::SgError) /Factory/;
// 
//     //------------------------------------------------------------------------
//     // Version Entity
//     Shotgun::Version *createVersion(const std::string &versionName) throw(Shotgun::SgError) /Factory/; 
//     Shotgun::Version *findVersionByName(const std::string &versionName) throw(Shotgun::SgError) /Factory/;
//     Shotgun::VersionPtrs findVersionsByProject(const std::string &projectCode, 
//                                                const int limit = 0) throw(Shotgun::SgError) /Factory/;
//     Shotgun::VersionPtrs findVersionsByShot(const std::string &projectCode, 
//                                             const std::string &shotName, 
//                                             const int limit = 0) throw(Shotgun::SgError) /Factory/;
//     Shotgun::VersionPtrs findVersionsByReviewStatus(const std::string &projectCode, 
//                                                     const std::string &reviewStatus,
//                                                     const int limit = 0) throw(Shotgun::SgError) /Factory/;
// 
//     //-----------------------------------------------------------------------
//     // HumanUser Entity
//     Shotgun::HumanUser *createHumanUser(const std::string &userName,
//                                         const std::string &userLogin,
//                                         const std::string &userEmail="") throw(Shotgun::SgError) /Factory/;
//     Shotgun::HumanUser *findHumanUserById(const int userId) throw(Shotgun::SgError) /Factory/;
//     Shotgun::HumanUser *findHumanUserByLogin(const std::string &userLogin) throw(Shotgun::SgError) /Factory/;
//     Shotgun::HumanUser *findRetiredHumanUser(const std::string &userLogin) throw(Shotgun::SgError) /Factory/;
// 
//     //------------------------------------------------------------------------
//     // Element Entity
//     Shotgun::Element *createElement(const std::string &projectCode,
//                                     const std::string &elementName, 
//                                     const std::string &elementType) throw(Shotgun::SgError) /Factory/;
//     Shotgun::Element *findElementByName(const std::string &projectCode, 
//                                         const std::string &elementName) throw(Shotgun::SgError) /Factory/;
//     Shotgun::ElementPtrs findElementsByProject(const std::string &projectCode, 
//                                                const std::string &elementType = "",
//                                                const int limit = 0) throw(Shotgun::SgError) /Factory/;
// 
//     //------------------------------------------------------------------------
//     // Asset Entity
//     Shotgun::Asset *createAsset(const std::string &projectCode,
//                                 const std::string &assetName, 
//                                 const std::string &assetType,
//                                 const std::string &assetSource = "") throw(Shotgun::SgError) /Factory/; 
//     Shotgun::Asset *findAssetByName(const std::string &projectCode, 
//                                     const std::string &assetName) throw(Shotgun::SgError) /Factory/;
//     Shotgun::AssetPtrs findAssetsByProject(const std::string &projectCode, 
//                                            const std::string &assetType = "",
//                                            const int limit = 0) throw(Shotgun::SgError) /Factory/;
// 
//     //------------------------------------------------------------------------
//     // Delivery Entity
//     Shotgun::Delivery *createDelivery(const std::string &projectCode, 
//                                       const std::string &deliveryName) throw(Shotgun::SgError) /Factory/;
//     Shotgun::Delivery *findDeliveryByName(const std::string &projectCode, 
//                                           const std::string &deliveryName) throw(Shotgun::SgError) /Factory/;
//     Shotgun::Delivery *findDeliveryById(const int deliveryId) throw(Shotgun::SgError) /Factory/;
//     Shotgun::DeliveryPtrs findDeliveriesByProject(const std::string &projectCode, 
//                                                   const std::string &deliveryStatus = "",
//                                                   const int limit = 0) throw(Shotgun::SgError) /Factory/;
// 
//     //------------------------------------------------------------------------
//     // PublishEvent Entity
//     Shotgun::PublishEvent *createPublishEvent(const std::string &projectCode,
//                                               const std::string &publishEventName) throw(Shotgun::SgError) /Factory/;
//     Shotgun::PublishEvent *findPublishEventByName(const std::string &projectCode, 
//                                                   const std::string &publishEventName) throw(Shotgun::SgError) /Factory/;
//     Shotgun::PublishEventPtrs findPublishEventsByProject(const std::string &projectCode, 
//                                                          const std::string &publishEventType = "",
//                                                          const int limit = 0) throw(Shotgun::SgError) /Factory/;
// 
//     //------------------------------------------------------------------------
//     // Review Entity
//     Shotgun::Review *createReview(const std::string &projectCode,
//                                   const std::string &reviewName) throw(Shotgun::SgError) /Factory/; 
//     Shotgun::Review *findReviewByName(const std::string &projectCode, 
//                                       const std::string &reviewName,
//                                       const std::string &dateSent = "") throw(Shotgun::SgError) /Factory/;
//     Shotgun::Review *findReviewById(const int reviewId) throw(Shotgun::SgError) /Factory/;
//     Shotgun::ReviewPtrs findReviewsByProject(const std::string &projectCode,
//                                              const int limit = 0) throw(Shotgun::SgError) /Factory/;
// 
//     //------------------------------------------------------------------------
//     // ReviewItem Entity
//     Shotgun::ReviewItem *createReviewItem(const std::string &projectCode,
//                                           const std::string &reviewItemName) throw(Shotgun::SgError) /Factory/; 
//     Shotgun::ReviewItem *findReviewItemByName(const std::string &projectCode, 
//                                               const std::string &reviewItemName) throw(Shotgun::SgError) /Factory/;
//     Shotgun::ReviewItem *findReviewItemById(const int reviewItemId) throw(Shotgun::SgError) /Factory/;
//     Shotgun::ReviewItemPtrs findReviewItemsByProject(const std::string &projectCode, 
//                                                      const int limit = 0) throw(Shotgun::SgError) /Factory/;
// 
//     //------------------------------------------------------------------------
//     // Task Entity
//     Shotgun::Task *createTask(const std::string &projectCode,
//                               const std::string &taskName,
//                               const std::string &taskType,
//                               const std::string &taskAssignee = "",
//                               const std::string &taskStartDate = "",
//                               const std::string &taskDueDate = "",
//                               const std::string &taskStatus = "",
//                               const std::string &taskColor = "",
//                               const bool taskMilestone = false,
//                               const Dict &taskEntityLink = Dict()) throw(Shotgun::SgError) /Factory/;
//     Shotgun::Task *findTaskByName(const std::string &projectCode, 
//                                   const std::string &taskName) throw(Shotgun::SgError) /Factory/;
//     Shotgun::TaskPtrs findTasksByType(const std::string &projectCode,
//                                       const std::string &taskType,
//                                       const std::string &linkEntityType = "",
//                                       const int limit = 0) throw(Shotgun::SgError) /Factory/;
//     Shotgun::TaskPtrs findTasksByLinkEntity(const std::string &projectCode,
//                                             const Dict &linkEntity,
//                                             const int limit = 0) throw(Shotgun::SgError) /Factory/;
//     Shotgun::TaskPtrs findTasksByMilestone(const std::string &projectCode,
//                                            const std::string &shotName,
//                                            const int limit = 0) throw(Shotgun::SgError) /Factory/;
//     Shotgun::TaskPtrs findTasksByProject(const std::string &projectCode,
//                                          const int limit = 0) throw(Shotgun::SgError) /Factory/;
// 
//     //------------------------------------------------------------------------
//     // Group Entity
//     Shotgun::Group *createGroup(const std::string &groupName) throw(Shotgun::SgError) /Factory/; 
//     Shotgun::Group *findGroupByName(const std::string &groupName) throw(Shotgun::SgError) /Factory/;
//     Shotgun::Group *findGroupById(const int groupId) throw(Shotgun::SgError) /Factory/;
// 
//     //------------------------------------------------------------------------
//     // Note Entity
//     Shotgun::Note *createNote(const std::string &projectCode,
//                               const std::string &noteFromUserName,
//                               const Shotgun::Strings &noteToUserNames = Shotgun::Strings(),
//                               const Shotgun::Strings &noteCcUserNames = Shotgun::Strings(),
//                               const std::string &noteSubject = "",
//                               const std::string &noteBody = "",
//                               const std::string &noteType = "",
//                               const Shotgun::List &noteLinks = Shotgun::List(),
//                               const std::string &noteOrigin = "") throw(Shotgun::SgError) /Factory/;
//     Shotgun::NotePtrs findNotesByType(const std::string &projectCode,
//                                       const std::string &noteType,
//                                       const int limit = 0) throw(Shotgun::SgError) /Factory/;
//     Shotgun::NotePtrs findNotesByAuthor(const std::string &projectCode,
//                                         const std::string &userName,
//                                         const int limit = 0) throw(Shotgun::SgError) /Factory/;
//     Shotgun::NotePtrs findNotesByLinks(const std::string &projectCode,
//                                        const Shotgun::List &noteLinks = Shotgun::List(),
//                                        const std::string &noteType = "",
//                                        const int limit = 0) throw(Shotgun::SgError) /Factory/;
// 
//     //------------------------------------------------------------------------
//     // Playlist Entity
//     Shotgun::Playlist *createPlaylist(const std::string &projectCode,
//                                       const std::string &playlistName) throw(Shotgun::SgError) /Factory/;
//     Shotgun::Playlist *findPlaylistByName(const std::string &projectCode, 
//                                           const std::string &playlistName) throw(Shotgun::SgError) /Factory/;
//     Shotgun::PlaylistPtrs findPlaylistsByProject(const std::string &projectCode, 
//                                                  const int limit = 0) throw(Shotgun::SgError) /Factory/;
// 

    //------------------------------------------------------------------------
    Shotgun::Entity *createEntity(const std::string &,
                                  const Shotgun::Dict &,
                                  const Shotgun::List &) throw(Shotgun::SgError) /Factory/;

    //------------------------------------------------------------------------
    Shotgun::Entity *findEntity(const std::string &entityType,
                                const Shotgun::FilterBy &filterList = Shotgun::FilterBy(),
                                const Shotgun::List &extraReturnFields = Shotgun::List(),
                                const bool retiredOnly = false,
                                const Shotgun::SortBy &order = Shotgun::SortBy()) throw(Shotgun::SgError) /Factory/;

    //------------------------------------------------------------------------
    Shotgun::EntityPtrs findEntities(const std::string &entityType,
                                     const Shotgun::FilterBy &filterList = Shotgun::FilterBy(),
                                     const int limit = 0,
                                     const Shotgun::List &extraReturnFields = Shotgun::List(),
                                     const bool retiredOnly = false,
                                     const Shotgun::SortBy &order = Shotgun::SortBy()) throw(Shotgun::SgError) /Factory/;

    //------------------------------------------------------------------------
    Shotgun::Entity *findEntityById(const std::string &entityType, const int id) throw(Shotgun::SgError) /Factory/;

    //------------------------------------------------------------------------
    bool deleteEntity(const std::string &entityType, const int id) throw(Shotgun::SgError);
};

}; // End namespace Shotgun
