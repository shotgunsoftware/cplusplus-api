//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

#include <Shotgun/Entity.h>

namespace Shotgun {

class Shotgun;

// *****************************************************************************
class Playlist : public Entity
{
    friend class Shotgun;
    friend class Entity;
 
protected:
    Playlist(Shotgun *sg, const xmlrpc_c::value &attrs);

    static Playlist create(Shotgun *sg,
                           const std::string &showCode,
                           const std::string &playlistName);

    static Playlists find(Shotgun *sg, SgMap &findMap);
    
public:
    Playlist();
    Playlist(const Playlist &ref);
    virtual ~Playlist();

    // Get an attribute's value
    const std::string sgName() const { return getAttrValueAsString("code"); }
    const time_t sgDateTime() const { return getAttrValueAsDatetime("sg_date_and_time"); }
    const std::string sgDescription() const { return getAttrValueAsString("description"); }
    const std::string sgThumbnail() const { return getAttrValueAsString("image"); }
    const Strings sgTags() const { return getAttrValueAsTags("tag_list"); }
    const Notes sgNotes() const;
    const Dailies sgDailies() const;

    // Set an attribute's value
    void sgName(const std::string &val) { setAttrValue("code", toXmlrpcValue(val)); }
    void sgDateTime(const time_t &val) { setAttrValue("sg_date_and_time", toXmlrpcValue(val)); }
    void sgDescription(const std::string &val) { setAttrValue("description", toXmlrpcValue(val)); }
    void sgTags(const Strings &val) { setAttrValue("tag_list", toXmlrpcValue(val)); }
    void sgNotes(const Notes &val);  // An array of Note entities
    void sgNotes(const SgArray &val);  // An array of entity links
    void sgDailies(const Dailies &val);  // An array of Daily entities
    void sgDailies(const SgArray &val);  // An array of entity links

    Playlist &operator=(const Playlist &that)
    {
        Entity::operator=(that);
        return *this;
    }
};

} // End namespace Shotgun

#endif    // End #ifdef __PLAYLIST_H__
