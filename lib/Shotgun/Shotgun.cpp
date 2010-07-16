//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$ 
//******************************************************************************

#include <iostream>

#include <Shotgun/Shotgun.h>
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
        m_authMap["script_key"] = toXmlrpcValue("220242e80d0e4f03c36acbc77f5eeef7b88e5a29");
    }
}

// *****************************************************************************
Shotgun::~Shotgun()
{
    delete m_client;
}

// *****************************************************************************
Show Shotgun::findShowByCode(const std::string &showCode)
{
    return Show(this, 
                Entity::findOneEntityBySingleFilter(this,
                                                    "Project",
                                                    "code", "is", toXmlrpcValue(showCode)));
}
    
// *****************************************************************************
Show Shotgun::findShowByName(const std::string &showName)
{
    return Show(this, 
                Entity::findOneEntityBySingleFilter(this,
                                                    "Project",
                                                    "name", "is", toXmlrpcValue(showName)));
}
    
    
// *****************************************************************************
Shows Shotgun::findShowsByStatus(const std::string &showStatus)
{
    SgMap findMap = Entity::buildFindMapWithSingleFilter(this,
                                                         "Project",
                                                         "sg_status", "is", toXmlrpcValue(showStatus));

    return findShows(findMap);
}
    
// *****************************************************************************
Sequence Shotgun::findSequenceByName(const std::string &showCode,
                                     const std::string &sequenceName)
{
    std::string sequenceNameUpper = toupper(sequenceName);

    return Sequence(this, 
                    Entity::findOneEntityBySingleFilter(this,
                                                       "Sequence",
                                                       "code", "is", toXmlrpcValue(sequenceNameUpper),
                                                       showCode));
}
    
// *****************************************************************************
Sequences Shotgun::findSequencesByShow(const std::string &showCode, const int limit)
{
    SgMap findMap = Entity::buildFindMapWithSingleFilter(this,
                                                         "Sequence",
                                                         "", "", xmlrpc_c::value_nil(),
                                                         showCode,
                                                         limit);
    return findSequences(findMap);
}
    
// *****************************************************************************
Shot Shotgun::findShotByName(const std::string &shotName)
{
#warning TODO: Implement in a non-Tippett way
//     TipUtil::ShotName sn = TipUtil::ShotName(shotName);
//   
//     return Shot(this, 
//                 Entity::findOneEntityBySingleFilter(this,
//                                                     "Shot",
//                                                     "code", "is", toXmlrpcValue(sn.shot(true, true)),
//                                                     sn.show()));
}
    
// *****************************************************************************
Shots Shotgun::findShotsByShow(const std::string &showCode, const int limit)
{
    SgMap findMap = Entity::buildFindMapWithNoFilter(this,
                                                     "Shot",
                                                     showCode,
                                                     limit);
    return findShots(findMap);
}
    
// *****************************************************************************
Daily Shotgun::findDailyByName(const std::string &dailyName)
{
#warning TODO: Implement in a non-Tippett way
//     TipUtil::DailyName dn = TipUtil::DailyName(dailyName);
// 
//     return Daily(this, 
//                  Entity::findOneEntityBySingleFilter(this,
//                                                      "Version",
//                                                      "code", "is", toXmlrpcValue(dailyName),
//                                                      dn.show()));
}
    
// *****************************************************************************
Dailies Shotgun::findDailiesByShow(const std::string &showCode, const int limit)
{
    SgMap findMap = Entity::buildFindMapWithNoFilter(this,
                                                     "Version",
                                                     showCode,
                                                     limit);

    return findDailies(findMap);
}
    
// *****************************************************************************
Dailies Shotgun::findDailiesByShot(const std::string &showCode,
                                   const std::string &shotName, 
                                   const int limit)
{
    // Both ways work, but the second one seems much faster. From my observation, 
    // searching by filterOp, "is", is MUCH faster than "name_contains".
#if 0
    std::string theShotName = TipUtil::ShotName(showCode, shotName).shot();

    SgMap findMap = Entity::buildFindMapWithSingleFilter(this,
                                                         "Version",
                                                         "entity", "name_contains", toXmlrpcValue(theShotName),
                                                         showCode,
                                                         limit);
#else 
#warning TODO: Implement in a non-Tippett way
//     std::string theShotName = TipUtil::ShotName(showCode, shotName).shot(true, true);
// 
//     Shot shot = findShotByName(theShotName);
//  
//     SgMap findMap = Entity::buildFindMapWithSingleFilter(this,
//                                                          "Version",
//                                                          "entity", "is", toXmlrpcValue(shot.asLink()),
//                                                          showCode,
//                                                          limit);
#endif

//     Dailies dailies = findDailies(findMap);
// 
//     return dailies;
}

// *****************************************************************************
Dailies Shotgun::findDailiesByReviewStatus(const std::string &showCode,
                                           const std::string &reviewStatus, 
                                           const int limit)
{
    SgMap findMap = Entity::buildFindMapWithSingleFilter(this,
                                                         "Version",
                                                         "sg_status", "is", toXmlrpcValue(reviewStatus),
                                                         showCode,
                                                         limit);

    return findDailies(findMap);
}
    
// *****************************************************************************
User Shotgun::findUserById(const int userId)
{
    return User(this, 
                Entity::findOneEntityBySingleFilter(this, 
                                                    "HumanUser",
                                                    "id", "is", toXmlrpcValue(userId)));
}

// *****************************************************************************
User Shotgun::findUserByLogin(const std::string &userLogin)
{
    return User(this, 
                Entity::findOneEntityBySingleFilter(this, 
                                                    "HumanUser",
                                                    "login", "is", toXmlrpcValue(userLogin)));
}

// *****************************************************************************
User Shotgun::findRetiredUser(const std::string &userLogin)
{
    return User(this, 
                Entity::findOneEntityBySingleFilter(this, 
                                                    "HumanUser",
                                                    "login", "is", toXmlrpcValue(userLogin),
                                                    "", // showCode
                                                    SgArray(), // extraReturnFields
                                                    true)); // retiredOnly
}

// *****************************************************************************
Element Shotgun::findElementByName(const std::string &showCode,
                                   const std::string &elementName)
{
    return Element(this, 
                   Entity::findOneEntityBySingleFilter(this, 
                                                       "Element",
                                                       "code", "is", toXmlrpcValue(elementName),
                                                       showCode));
}
    
// *****************************************************************************
Elements Shotgun::findElementsByShow(const std::string &showCode, 
                                     const std::string &elementType,
                                     const int limit)
{
    SgMap findMap;
    if (elementType != "")
    {
        findMap = Entity::buildFindMapWithSingleFilter(this,
                                                       "Element",
                                                       "sg_element_type", "is", toXmlrpcValue(elementType),
                                                       showCode,
                                                       limit);
    }
    else
    {
        findMap = Entity::buildFindMapWithNoFilter(this,
                                                   "Element",
                                                   showCode,
                                                   limit);
    }

    return findElements(findMap);
}
    
// *****************************************************************************
Asset Shotgun::findAssetByName(const std::string &showCode,
                               const std::string &assetName)
{
    return Asset(this, 
                 Entity::findOneEntityBySingleFilter(this, 
                                                     "Asset",
                                                     "code", "is", toXmlrpcValue(assetName),
                                                     showCode));
}
    
// *****************************************************************************
Assets Shotgun::findAssetsByShow(const std::string &showCode, 
                                 const std::string &assetType,
                                 const int limit)
{
    SgMap findMap;
    if (assetType != "")
    {
        findMap = Entity::buildFindMapWithSingleFilter(this,
                                                       "Asset",
                                                       "sg_asset_type", "is", toXmlrpcValue(assetType),
                                                       showCode,
                                                       limit);
    }
    else
    {
        findMap = Entity::buildFindMapWithNoFilter(this,
                                                   "Asset",
                                                   showCode,
                                                   limit);

    }

    return findAssets(findMap);
}
    
// *****************************************************************************
Delivery Shotgun::findDeliveryByName(const std::string &showCode,
                                     const std::string &deliveryName)
{
    return Delivery(this, 
                    Entity::findOneEntityBySingleFilter(this, 
                                                        "Delivery",
                                                        "title", "is", toXmlrpcValue(deliveryName),
                                                        showCode));
}
    
// *****************************************************************************
Delivery Shotgun::findDeliveryById(const int &deliveryId)
{
    return Delivery(this, 
                    Entity::findOneEntityBySingleFilter(this, 
                                                        "Delivery",
                                                        "id", "is", toXmlrpcValue(deliveryId)));
}
    
// *****************************************************************************
Deliveries Shotgun::findDeliveriesByShow(const std::string &showCode, 
                                         const std::string &deliveryStatus,
                                         const int limit)
{
    SgMap findMap;
    if (deliveryStatus != "")
    {
        findMap = Entity::buildFindMapWithSingleFilter(this,
                                                       "Delivery",
                                                       "sg_delivery_status", "is", toXmlrpcValue(deliveryStatus),
                                                       showCode,
                                                       limit);
    }
    else
    {
        findMap = Entity::buildFindMapWithNoFilter(this,
                                                   "Delivery",
                                                   showCode,
                                                   limit);
    }

    return findDeliveries(findMap);
}
    
// *****************************************************************************
DeliveryItem Shotgun::findDeliveryItemByName(const std::string &showCode,
                                             const std::string &deliveryItemName)
{
    return DeliveryItem(this, 
                        Entity::findOneEntityBySingleFilter(this, 
                                                            "CustomEntity01",
                                                            "code", "is", toXmlrpcValue(deliveryItemName),
                                                            showCode));
}
    
// *****************************************************************************
DeliveryItem Shotgun::findDeliveryItemById(const int &deliveryItemId)
{
    return DeliveryItem(this, 
                        Entity::findOneEntityBySingleFilter(this, 
                                                            "CustomEntity01",
                                                            "id", "is", toXmlrpcValue(deliveryItemId)));
}
    
// *****************************************************************************
DeliveryItems Shotgun::findDeliveryItemsByShow(const std::string &showCode, 
                                               const int limit)
{
    SgMap findMap = Entity::buildFindMapWithNoFilter(this,
                                                     "CustomEntity01",
                                                     showCode,
                                                     limit);
    return findDeliveryItems(findMap);
}

// *****************************************************************************
PublishEvent Shotgun::findPublishEventByName(const std::string &showCode,
                                             const std::string &publishEventName)
{
    return PublishEvent(this, 
                        Entity::findOneEntityBySingleFilter(this, 
                                                            "PublishEvent",
                                                            "code", "is", toXmlrpcValue(publishEventName),
                                                            showCode));
}
    
// *****************************************************************************
PublishEvents Shotgun::findPublishEventsByShow(const std::string &showCode, 
                                               const std::string &publishEventType,
                                               const int limit)
{
    SgMap findMap;
    if (publishEventType != "")
    {
        findMap = Entity::buildFindMapWithSingleFilter(this,
                                                       "PublishEvent",
                                                       "sg_type", "is", toXmlrpcValue(publishEventType),
                                                       showCode,
                                                       limit);
    }
    else
    {
        findMap = Entity::buildFindMapWithNoFilter(this,
                                                   "PublishEvent",
                                                   showCode,
                                                   limit);
    }

    return findPublishEvents(findMap);
}
    
// *****************************************************************************
Review Shotgun::findReviewByName(const std::string &showCode,
                                 const std::string &reviewName,
                                 const std::string &dateSent)
{
    SgMap findMap = Entity::buildFindMapWithSingleFilter(this,
                                                        "Review",
                                                        "code", "is", toXmlrpcValue(reviewName),
                                                        showCode,
                                                        1);
    if (dateSent != "")
    {
        Entity::addOneConditionToFindMap(findMap,
                                         "sg_review_date_sent", "is", toXmlrpcValue(dateSent));
    }

    Reviews reviews = findReviews(findMap);
    if (reviews.size() > 0)
    {
        return reviews[0];     
    }
    else
    {
        throw SgEntityNotFoundError("Review");
    }
}
    
// *****************************************************************************
Review Shotgun::findReviewById(const int &reviewId)
{
    return Review(this, 
                  Entity::findOneEntityBySingleFilter(this, 
                                                      "Review",
                                                      "id", "is", toXmlrpcValue(reviewId)));
}
    
// *****************************************************************************
Reviews Shotgun::findReviewsByShow(const std::string &showCode, 
                                   const std::string &reviewType,
                                   const int limit)
{
    SgMap findMap;
    if (reviewType != "")
    {
        findMap = Entity::buildFindMapWithSingleFilter(this,
                                                       "Review",
                                                       "sg_review_type", "is", toXmlrpcValue(reviewType),
                                                       showCode,
                                                       limit);
    }
    else
    {
        findMap = Entity::buildFindMapWithNoFilter(this,
                                                   "Review",
                                                   showCode,
                                                   limit);
    }

    return findReviews(findMap);
}
    
// *****************************************************************************
ReviewItem Shotgun::findReviewItemByName(const std::string &showCode,
                                         const std::string &reviewItemName)
{
    // There could be multiple ReviewItems that share the same name.
    // So the result might not be unique. In this case, search by
    // "id" is better since "id" is unique.
    return ReviewItem(this, 
                      Entity::findOneEntityBySingleFilter(this, 
                                                          "ReviewItem",
                                                          "code", "is", toXmlrpcValue(reviewItemName),
                                                          showCode));
}
    
// *****************************************************************************
ReviewItem Shotgun::findReviewItemById(const int &reviewItemId)
{
    return ReviewItem(this, 
                      Entity::findOneEntityBySingleFilter(this, 
                                                          "ReviewItem",
                                                          "id", "is", toXmlrpcValue(reviewItemId)));
}
    
// *****************************************************************************
ReviewItems Shotgun::findReviewItemsByShow(const std::string &showCode, 
                                           const int limit)
{
    SgMap findMap = Entity::buildFindMapWithNoFilter(this,
                                                     "ReviewItem",
                                                     showCode,
                                                     limit);

    return findReviewItems(findMap);
}

// *****************************************************************************
Task Shotgun::findTaskByName(const std::string &showCode,
                                 const std::string &taskName)
{
    return Task(this, 
                Entity::findOneEntityBySingleFilter(this, 
                                                    "Task",
                                                    "content", "is", toXmlrpcValue(taskName),
                                                    showCode));
}
    
// *****************************************************************************
Tasks Shotgun::findTasksByType(const std::string &showCode,
                               const std::string &taskType,
                               const std::string &linkEntityType,
                               const int limit)
{
    SgMap findMap = Entity::buildFindMapWithSingleFilter(this,
                                                         "Task",
                                                         "sg_system_task_type", "is", toXmlrpcValue(taskType),
                                                         showCode,
                                                         limit);

    if (linkEntityType != "")
    {
        Entity::addOneConditionToFindMap(findMap, 
                                         "entity", "type_is", toXmlrpcValue(linkEntityType));
    }

    return findTasks(findMap);
}

// *****************************************************************************
Tasks Shotgun::findTasksByLinkEntity(const std::string &showCode,
                                     const SgMap &linkEntity,
                                     const int limit)
{
    SgMap findMap = Entity::buildFindMapWithSingleFilter(this,
                                                         "Task",
                                                         "entity", "is", toXmlrpcValue(linkEntity),
                                                         showCode,
                                                         limit);

    return findTasks(findMap);
}

// *****************************************************************************
Tasks Shotgun::findTasksByMilestone(const std::string &showCode,
                                    const std::string &shotName,
                                    const int limit)
{
    Shot shot = findShotByName(shotName);

    SgMap findMap = Entity::buildFindMapWithSingleFilter(this,
                                                         "Task",
                                                         "entity", "is", toXmlrpcValue(shot.asLink()),
                                                         showCode,
                                                         limit);
    Entity::addOneConditionToFindMap(findMap, 
                                     "milestone", "is", toXmlrpcValue(true));

    return findTasks(findMap);
}
    

// *****************************************************************************
Tasks Shotgun::findTasksByShow(const std::string &showCode,
                               const int limit)
{
    SgMap findMap = Entity::buildFindMapWithNoFilter(this,
                                                     "Task",
                                                     showCode,
                                                     limit);

    return findTasks(findMap);
}
    
// *****************************************************************************
Group Shotgun::findGroupByName(const std::string &groupName)
{
    return Group(this, 
                 Entity::findOneEntityBySingleFilter(this, 
                                                     "Group",
                                                     "code", "is", toXmlrpcValue(groupName)));
}
    
// *****************************************************************************
Group Shotgun::findGroupById(const int &groupId)
{
    return Group(this, 
                 Entity::findOneEntityBySingleFilter(this, 
                                                     "Group",
                                                     "id", "is", toXmlrpcValue(groupId)));
}
    
// *****************************************************************************
Notes Shotgun::findNotesByType(const std::string &noteType,
                               const std::string &showCode,
                               const int limit)
{
    SgMap findMap = Entity::buildFindMapWithSingleFilter(this,
                                                         "Note",
                                                         "sg_note_type", "is", toXmlrpcValue(noteType),
                                                         showCode,
                                                         limit);

    return findNotes(findMap);

}

// *****************************************************************************
Notes Shotgun::findNotesByAuthor(const std::string &userName,
                                 const std::string &showCode,
                                 const int limit)
{
    User user = findUserByLogin(userName);

    SgMap findMap = Entity::buildFindMapWithSingleFilter(this,
                                                         "Note",
                                                         "user", "is", toXmlrpcValue(user.asLink()),
                                                         showCode,
                                                         limit);

    return findNotes(findMap);
}

// *****************************************************************************
Notes Shotgun::findNotesByLinks(const SgArray &noteLinks,
                                const std::string &noteType,
                                const std::string &showCode,
                                const int limit)
{
    SgMap findMap = Entity::buildFindMapWithNoFilter(this,
                                                     "Note",
                                                     showCode,
                                                     limit);

#if 1
    // This seems to work with only ONE noteLink.
    //
    for (size_t i = 0; i < noteLinks.size(); i++)
    {
        SgMap linkAsMap = SgMap(xmlrpc_c::value_struct(noteLinks[i]));


        Entity::addOneConditionToFindMap(findMap, 
                                         "note_links", "is", toXmlrpcValue(noteLinks[i]));

        // None of these seem to work
        //Entity::addOneConditionToFindMap(findMap, 
        //                                 "note_links", "contains", toXmlrpcValue(noteLinks[i])); // "contains" is not valid Op
        //
        //Entity::addOneConditionToFindMap(findMap, 
        //                                 "note_links", "type_is", toXmlrpcValue("Shot"));
        //
        //std::string linkName = Entity::getAttrValueAsString("name", linkAsMap);
        //Entity::addOneConditionToFindMap(findMap, 
        //                                 "note_links", "name_contains", toXmlrpcValue(linkName));
    }
#else
    if (noteLinks.size() > 0)
    {
        // "is" (relation Op) expects a one-element array
        Entity::addOneConditionToFindMap(findMap, 
                                         "note_links", "is", toXmlrpcValue(noteLinks));

        // This doesn't work
        //Entity::addOneConditionToFindMap(findMap, 
        //                                 "note_links", "in", toXmlrpcValue(noteLinks)); // "in" is not valid Op
    }
#endif

    if (noteType != "")
    {
        Entity::addOneConditionToFindMap(findMap, 
                                         "sg_note_type", "is", toXmlrpcValue(noteType));
    }

    return findNotes(findMap);
}
    
// *****************************************************************************
Reference Shotgun::findReferenceByPath(const std::string &showCode,
                                       const std::string &referencePath)
{
    return Reference(this, 
                     Entity::findOneEntityBySingleFilter(this, 
                                                         "CustomEntity02",
                                                         "code", "is", toXmlrpcValue(referencePath),
                                                         showCode));
}
    
// *****************************************************************************
Reference Shotgun::findReferenceByName(const std::string &showCode,
                                       const std::string &referenceName)
{
    return findReferenceByPath(showCode, referenceName);
}
    
// *****************************************************************************
References Shotgun::findReferencesByShow(const std::string &showCode, 
                                         const int limit)
{
    SgMap findMap = Entity::buildFindMapWithNoFilter(this,
                                                     "CustomEntity02",
                                                     showCode,
                                                     limit);

    return findReferences(findMap);
}
    
// *****************************************************************************
Playlist Shotgun::findPlaylistByName(const std::string &showCode,
                                     const std::string &playlistName)
{
    return Playlist(this, 
                    Entity::findOneEntityBySingleFilter(this, 
                                                        "Playlist",
                                                        "code", "is", toXmlrpcValue(playlistName),
                                                        showCode));
}
    
// *****************************************************************************
Playlists Shotgun::findPlaylistsByShow(const std::string &showCode, 
                                       const int limit)
{
    SgMap findMap = Entity::buildFindMapWithNoFilter(this,
                                                     "Playlist",
                                                     showCode,
                                                     limit);

    return findPlaylists(findMap);
}
    
// *****************************************************************************
Entity *Shotgun::findEntityById(const std::string &entityType, const int &id)
{
    xmlrpc_c::value entity = Entity::findOneEntityBySingleFilter(this,
                                                                 sgEntityType(entityType),
                                                                 "id", "is", toXmlrpcValue(id));
    std::string tipType = tipEntityType(entityType);

    // IMPORTANT: user is responsible to delete them in C++ app.
    if (tipType == "Show")
    {
        return new Show(this, entity);
    }
    else if (tipType == "Sequence")
    {
        return new Sequence(this, entity);
    }
    else if (tipType == "Shot")
    {
        return new Shot(this, entity);
    }
    else if (tipType == "Daily")
    {
        return new Daily(this, entity);
    }
    else if (tipType == "User")
    {
        return new User(this, entity);
    }
    else if (tipType == "Element")
    {
        return new Element(this, entity);
    }
    else if (tipType == "Asset")
    {
        return new Asset(this, entity);
    }
    else if (tipType == "Delivery")
    {
        return new Delivery(this, entity);
    }
    else if (tipType == "DeliveryItem")
    {
        return new DeliveryItem(this, entity);
    }
    else if (tipType == "PublishEvent")
    {
        return new PublishEvent(this, entity);
    }
    else if (tipType == "Review")
    {
        return new Review(this, entity);
    }
    else if (tipType == "ReviewItem")
    {
        return new ReviewItem(this, entity);
    }
    else if (tipType == "Task")
    {
        return new Task(this, entity);
    }
    else if (tipType == "Group")
    {
        return new Group(this, entity);
    }
    else if (tipType == "Note")
    {
        return new Note(this, entity);
    }
    else if (tipType == "Reference")
    {
        return new Reference(this, entity);
    }
    else if (tipType == "Playlist")
    {
        return new Playlist(this, entity);
    }
    else
    {
        return NULL;
    }
}
    
} // End namespace Shotgun
