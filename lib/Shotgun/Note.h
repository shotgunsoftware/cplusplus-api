//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#ifndef __NOTE_H__
#define __NOTE_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Entity.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Note : public Entity
{
    friend class Shotgun;
    friend class Entity;
    friend class Playlist;
 
protected:
    Note(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Note create(Shotgun *sg, 
                       const std::string &showCode,
                       const std::string &noteFromUserName,
                       const Strings &noteToUserNames = Strings(),
                       const Strings &noteCcUserNames = Strings(),
                       const std::string &noteSubject = "",
                       const std::string &noteBody = "",
                       const std::string &noteType = "",
                       const SgArray &noteLinks = SgArray(),
                       const std::string &noteOrigin = "");
    static Notes find(Shotgun *sg, SgMap &findMap);
    
public:
    Note();
    Note(const Note &ref);
    virtual ~Note();

    // Get an attribute's value
    const std::string sgAuthor() const { return getAttrValueAsUserLogin("user"); } 
    const std::string sgBody() const { return getAttrValueAsString("content"); } 
    const std::string sgStatus() const { return getAttrValueAsString("sg_status_list"); } 
    const std::string sgSubject() const { return getAttrValueAsString("subject"); } 
    const std::string sgName() const { return sgSubject(); } 
    const std::string sgType() const { return getAttrValueAsString("sg_note_type"); } 
    const Review getLinkedReview() const;
    const Shot getLinkedShot() const;
    const Daily getLinkedDaily() const;
    // Both sgCc() and sgTo() could be a mixed list of User and Group entities.
    // sgLinks() is a list of mixed types of entities. If we want to these 
    // functions to return a list of entities instead of a list of mini maps, 
    // check function, sgAssignees() in "Task.h".
    const SgArray sgCc() const { return getAttrValueAsArray("addressings_cc"); } 
    const SgArray sgTo() const { return getAttrValueAsArray("addressings_to"); } 
    const SgArray sgLinks() const { return getAttrValueAsArray("note_links"); } 

    Note &operator=(const Note &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __NOTE_H__
