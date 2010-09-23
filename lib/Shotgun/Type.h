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

#ifndef __TYPE_H__
#define __TYPE_H__

#include <iostream>
#include <map>

#include <xmlrpc-c/base.hpp>

namespace Shotgun {

class Entity;
class Project;
class Sequence;
class Shot;
class Version;
class HumanUser;
class Element;
class Asset;
class Delivery;
class PublishEvent;
class Review;
class ReviewItem;
class Task;
class Group;
class Note;
class Playlist;

class FilterBy;
class SortBy;
class List;

// *****************************************************************************
typedef std::vector<std::string> Strings;
typedef Strings MethodSignature;
typedef std::vector<Strings> MethodSignatures;
typedef std::map<std::string, xmlrpc_c::value> SgMap;
typedef std::vector<xmlrpc_c::value> SgArray;

typedef std::vector<Project> Projects;
typedef std::vector<Sequence> Sequences;
typedef std::vector<Shot> Shots;
typedef std::vector<Version> Versions;
typedef std::vector<HumanUser> HumanUsers;
typedef std::vector<Element> Elements;
typedef std::vector<Asset> Assets;
typedef std::vector<Delivery> Deliveries;
typedef std::vector<PublishEvent> PublishEvents;
typedef std::vector<Review> Reviews;
typedef std::vector<ReviewItem> ReviewItems;
typedef std::vector<Task> Tasks;
typedef std::vector<Group> Groups;
typedef std::vector<Note> Notes;
typedef std::vector<Playlist> Playlists;

#warning Add these to sip's mappedTypes
typedef std::vector<Entity *> EntityPtrs;
typedef std::vector<Project *> ProjectPtrs;
typedef std::vector<Sequence *> SequencePtrs;
typedef std::vector<Shot *> ShotPtrs;
typedef std::vector<Version *> VersionPtrs;
typedef std::vector<HumanUser *> HumanUserPtrs;
typedef std::vector<Element *> ElementPtrs;
typedef std::vector<Asset *> AssetPtrs;
typedef std::vector<Delivery *> DeliveryPtrs;
typedef std::vector<PublishEvent *> PublishEventPtrs;
typedef std::vector<Review *> ReviewPtrs;
typedef std::vector<ReviewItem *> ReviewItemPtrs;
typedef std::vector<Task *> TaskPtrs;
typedef std::vector<Group *> GroupPtrs;
typedef std::vector<Note *> NotePtrs;
typedef std::vector<Playlist *> PlaylistPtrs;

// *****************************************************************************
std::string xmlrpcValueTypeStr(const xmlrpc_c::value::type_t xmlrpcType);

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const char *in);
xmlrpc_c::value toXmlrpcValue(const std::string &in);
xmlrpc_c::value toXmlrpcValue(const int &in);
xmlrpc_c::value toXmlrpcValue(const double &in);
xmlrpc_c::value toXmlrpcValue(const bool &in);
xmlrpc_c::value toXmlrpcValue(const time_t &in);
xmlrpc_c::value toXmlrpcValue(const SgArray &in);
xmlrpc_c::value toXmlrpcValue(const SgMap &in);
xmlrpc_c::value toXmlrpcValue(const Strings &in);
xmlrpc_c::value toXmlrpcValue(const MethodSignatures &in);
xmlrpc_c::value toXmlrpcValue(const FilterBy &in);
xmlrpc_c::value toXmlrpcValue(const SortBy &in);
xmlrpc_c::value toXmlrpcValue(const List &in);
xmlrpc_c::value toXmlrpcValue(const xmlrpc_c::value &in);

#warning These should be moved either out of the Shotgun namespace or into indivial classes
// *****************************************************************************
std::string toStdString(const xmlrpc_c::value &value);
std::string toStdString(const SgMap &map);
std::string toStdString(const SgArray &array);
std::string toStdString(const Strings &strs);
std::string toStdString(const MethodSignatures &sigs);
std::string toStdString(const FilterBy &filterList);
std::string toStdString(const SortBy &filterList);
std::string toStdString(const List &list);
std::string toStdString(const Project &project);
std::string toStdString(const Projects &projects);
std::string toStdString(const Sequence &sequence);
std::string toStdString(const Sequences &sequences);
std::string toStdString(const Shot &shot);
std::string toStdString(const Shots &shots);
std::string toStdString(const Version &version);
std::string toStdString(const Versions &versions);
std::string toStdString(const HumanUser &user);
std::string toStdString(const HumanUsers &users);
std::string toStdString(const Element &element);
std::string toStdString(const Elements &elements);
std::string toStdString(const Asset &asset);
std::string toStdString(const Assets &assets);
std::string toStdString(const Delivery &delivery);
std::string toStdString(const Deliveries &deliveries);
std::string toStdString(const PublishEvent &publsihEvent);
std::string toStdString(const PublishEvents &publsihEvents);
std::string toStdString(const Review &review);
std::string toStdString(const Reviews &reviews);
std::string toStdString(const ReviewItem &reviewItem);
std::string toStdString(const ReviewItems &reviewItems);
std::string toStdString(const Task &task);
std::string toStdString(const Tasks &tasks);
std::string toStdString(const Group &group);
std::string toStdString(const Groups &groups);
std::string toStdString(const Note &note);
std::string toStdString(const Notes &notes);
std::string toStdString(const Playlist &playlist);
std::string toStdString(const Playlists &playlists);

// *****************************************************************************
#warning Move these operator<< guys out of the Shotgun namespace
std::ostream &operator<<(std::ostream& output, const xmlrpc_c::value &value);
std::ostream &operator<<(std::ostream& output, const SgMap &map);
std::ostream &operator<<(std::ostream& output, const SgArray &array);
std::ostream &operator<<(std::ostream& output, const Strings &strs);
std::ostream &operator<<(std::ostream& output, const MethodSignatures &sigs);
std::ostream &operator<<(std::ostream& output, const Project &project);
std::ostream &operator<<(std::ostream& output, const Projects &projects);
std::ostream &operator<<(std::ostream& output, const Sequence &sequence);
std::ostream &operator<<(std::ostream& output, const Sequences &sequences);
std::ostream &operator<<(std::ostream& output, const Shot &shot);
std::ostream &operator<<(std::ostream& output, const Shots &shots);
std::ostream &operator<<(std::ostream& output, const Version &version);
std::ostream &operator<<(std::ostream& output, const Versions &versions);
std::ostream &operator<<(std::ostream& output, const HumanUser &user);
std::ostream &operator<<(std::ostream& output, const HumanUsers &users);
std::ostream &operator<<(std::ostream& output, const Element &element);
std::ostream &operator<<(std::ostream& output, const Elements &elements);
std::ostream &operator<<(std::ostream& output, const Asset &asset);
std::ostream &operator<<(std::ostream& output, const Assets &assets);
std::ostream &operator<<(std::ostream& output, const Delivery &delivery);
std::ostream &operator<<(std::ostream& output, const Deliveries &deliveries);
std::ostream &operator<<(std::ostream& output, const PublishEvent &publishEvent);
std::ostream &operator<<(std::ostream& output, const PublishEvents &publishEvents);
std::ostream &operator<<(std::ostream& output, const Review &review);
std::ostream &operator<<(std::ostream& output, const Reviews &reviews);
std::ostream &operator<<(std::ostream& output, const ReviewItem &reviewItem);
std::ostream &operator<<(std::ostream& output, const ReviewItems &reviewItems);
std::ostream &operator<<(std::ostream& output, const Task &task);
std::ostream &operator<<(std::ostream& output, const Tasks &tasks);
std::ostream &operator<<(std::ostream& output, const Group &group);
std::ostream &operator<<(std::ostream& output, const Groups &groups);
std::ostream &operator<<(std::ostream& output, const Note &note);
std::ostream &operator<<(std::ostream& output, const Notes &notes);
std::ostream &operator<<(std::ostream& output, const Playlist &playlist);
std::ostream &operator<<(std::ostream& output, const Playlists &playlists);

// *****************************************************************************
// Utility func
std::string currDateStr();

// *****************************************************************************
class SgError : public std::exception
{
public:
    SgError(const std::string &msg = "") { m_msg = msg; }
    SgError(const char *msg = "") { m_msg = msg; }

    virtual ~SgError() throw() {}

    virtual const char *what() const throw()
    {
        return m_msg.c_str();
    }

protected:
    std::string m_msg;
};

// *****************************************************************************
// "SgAttrError" is nothing more than it's base class, "SgError". It is just an 
// extra container for the attribute-specific exceptions
class SgAttrError : public SgError
{
public:
    SgAttrError(const std::string &msg = "") : SgError(msg) {}
    SgAttrError(const char *msg = "") : SgError(msg) {}

    virtual ~SgAttrError() throw() {}
};

// *****************************************************************************
class SgAttrNotFoundError : public SgAttrError
{
public:
    SgAttrNotFoundError(const std::string &attrName) : SgAttrError("SgAttrNotFoundError: ")
    {
        m_msg += "Attribute, '" + attrName + "', is not found.";
    }

    virtual ~SgAttrNotFoundError() throw() {}
};

// *****************************************************************************
class SgAttrTypeError : public SgAttrError
{
public:
    SgAttrTypeError(const std::string &attrName,
                    const xmlrpc_c::value::type_t wrongType,
                    const xmlrpc_c::value::type_t correctType) : SgAttrError("SgAttrTypeError: ")
    {
        m_msg += "Attribute, '" + attrName + ", ";
        m_msg += "is not of '" + xmlrpcValueTypeStr(wrongType) + "'. ";
        m_msg += "It is of '" + xmlrpcValueTypeStr(correctType) + "'.";
    }

    virtual ~SgAttrTypeError() throw() {}
};

// *****************************************************************************
class SgAttrValueError : public SgAttrError
{
public:
    SgAttrValueError(const std::string &attrName) : SgAttrError("SgAttrValueError: ")
    {
        m_msg += "Attribute, '" + attrName + "', does not have a valid value.";
    }

    virtual ~SgAttrValueError() throw() {}
};


// *****************************************************************************
class SgAttrLinkError : public SgAttrError
{
public:
    SgAttrLinkError(const SgMap &link) : SgAttrError("SgAttrLinkError: ")
    {
        m_msg += "The given link is missing one or more of the required fields: \"id\", \"type\", \"name\"\n";
        m_msg += toStdString(link);
    }

    SgAttrLinkError(const xmlrpc_c::value &link,
                    const xmlrpc_c::value::type_t &type) : SgAttrError("SgAttrLinkError: ")
    {
        m_msg += "The given link has the wrong type: \"" + xmlrpcValueTypeStr(type);
        m_msg += "\", it should be type of \"TYPE_STRUCT\"\n";
        m_msg += toStdString(link);
    }

    virtual ~SgAttrLinkError() throw() {}
};


// *****************************************************************************
class SgAttrSetValueError : public SgAttrError
{
public:
    SgAttrSetValueError(const std::string &attrName,
                        const std::string &errMsg = "") : SgAttrError("SgAttrSetValueError: ")
    {
        m_msg += "Failed to set value for attribute, '" + attrName + "'";
        if (errMsg != "")
        {
            m_msg += "\n" + errMsg;
        }
    }

    SgAttrSetValueError(const SgMap &attrPairs,
                        const std::string &errMsg = "") : SgAttrError("SgAttrSetValueError: ")
    {
        m_msg += "Failed to set values for attribute list, " + toStdString(attrPairs);
        if (errMsg != "")
        {
            m_msg += "\n" + errMsg;
        }
    }

    virtual ~SgAttrSetValueError() throw() {}
};

// *****************************************************************************
class SgEmptyAttrMapError : public SgAttrError
{
public:
    SgEmptyAttrMapError() : SgAttrError("SgEmptyAttrMapError: ")
    {
        m_msg += "Empty attribute map.";
    }

    virtual ~SgEmptyAttrMapError() throw() {}
};

// *****************************************************************************
class SgEntityError : public SgError
{
public:
    SgEntityError(const std::string &msg = "") : SgError(msg) {}
    SgEntityError(const char *msg = "") : SgError(msg) {}

    virtual ~SgEntityError() throw() {}
};

// *****************************************************************************
class SgEntityXmlrpcError : public SgEntityError
{
public:
    SgEntityXmlrpcError(const std::string &msg) : SgEntityError("SgEntityXmlrpcError: ") 
    {
        m_msg += msg;
    }

    virtual ~SgEntityXmlrpcError() throw() {}
};

// *****************************************************************************
class SgEntityNotFoundError : public SgEntityError
{
public:
    SgEntityNotFoundError(const std::string &entityType = "" ) : SgEntityError("SgEntityNotFoundError: ")
    {
        if (entityType == "")
        {
            m_msg += "entity not found.";
        }
        else
        {
            m_msg += "Shotgun \"" + entityType + "\" entity not found.";
        }
    }

    virtual ~SgEntityNotFoundError() throw() {}
};

// *****************************************************************************
class SgEntityFunctionNotFoundError : public SgEntityError
{
public:
    SgEntityFunctionNotFoundError(const std::string &entityType, 
                                  const std::string &funcMapName) : SgEntityError("SgEntityFunctionNotFoundError: ")
    {
        m_msg += "Can't find entry for \"" + entityType + "\" entity in function map \"";
        m_msg += funcMapName + "\". Check Shotgun class' constructor.";
    }

    virtual ~SgEntityFunctionNotFoundError() throw() {}
};

// *****************************************************************************
class SgEntityDynamicCastError : public SgEntityError
{
public:
    SgEntityDynamicCastError(const std::string &castType) : SgEntityError("SgEntityDynamicCastError: ")
    {
        m_msg += "dynamic_casting to type \"" + castType + "\" failed.";
    }

    virtual ~SgEntityDynamicCastError() throw() {}
};

// *****************************************************************************
class SgEntityCreateError : public SgEntityError
{
public:
    SgEntityCreateError(const std::string &err) : SgEntityError("SgEntityCreateError: ")
    {
        m_msg += err;
    }

    virtual ~SgEntityCreateError() throw() {}
};

// *****************************************************************************
class SgApiError : public SgError
{
public:
    SgApiError(const std::string &api) : SgError("SgApiError: ")
    {
        m_msg += api + " is not supported.";
    }

    virtual ~SgApiError() throw() {}
};

} // End namespace Shotgun

// *****************************************************************************
// These are outside of the Shotgun namespace
#warning Finish moving these operators out of Shotgun namespace
std::string toStdString(const xmlrpc_c::value &value);
std::string toStdString(const Shotgun::SgArray &array);
std::string toStdString(const Shotgun::SgMap &map);
std::string toStdString(const Shotgun::Strings &strs);
std::string toStdString(const Shotgun::MethodSignatures &sigs);

std::ostream &operator<<(std::ostream& output, const xmlrpc_c::value &value);
std::ostream &operator<<(std::ostream& output, const Shotgun::SgArray &array);
std::ostream &operator<<(std::ostream& output, const Shotgun::SgMap &map);
std::ostream &operator<<(std::ostream& output, const Shotgun::Strings &strs);
std::ostream &operator<<(std::ostream& output, const Shotgun::MethodSignatures &sigs);

#endif    // End #ifdef __TYPE_H__
