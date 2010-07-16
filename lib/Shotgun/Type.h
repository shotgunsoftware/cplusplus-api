//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#ifndef __TYPE_H__
#define __TYPE_H__

#include <iostream>
#include <map>

#include <xmlrpc-c/base.hpp>

//TODO: update these to some numbers that make sense
#define TIPSHOTGUN_INVALID_VERSION_NUM -1
#define TIPSHOTGUN_INVALID_ORDER_NUM -1

namespace Shotgun {

class Entity;
class Show;
class Sequence;
class Shot;
class Daily;
class User;
class Element;
class Asset;
class Delivery;
class DeliveryItem;
class PublishEvent;
class Review;
class ReviewItem;
class Task;
class Group;
class Note;
class Reference;
class Playlist;

// *****************************************************************************
typedef std::vector<std::string> Strings;
typedef Strings MethodSignature;
typedef std::vector<Strings> MethodSignatures;
typedef std::map<std::string, xmlrpc_c::value> SgMap;
typedef std::vector<xmlrpc_c::value> SgArray;
typedef std::vector<Entity *> EntityPtrs; // Only (Entity *) can be dynamic_casted, not (Entity)
typedef std::vector<Show> Shows;
typedef std::vector<Sequence> Sequences;
typedef std::vector<Shot> Shots;
typedef std::vector<Daily> Dailies;
typedef std::vector<User> Users;
typedef std::vector<Element> Elements;
typedef std::vector<Asset> Assets;
typedef std::vector<Delivery> Deliveries;
typedef std::vector<DeliveryItem> DeliveryItems;
typedef std::vector<PublishEvent> PublishEvents;
typedef std::vector<Review> Reviews;
typedef std::vector<ReviewItem> ReviewItems;
typedef std::vector<Task> Tasks;
typedef std::vector<Group> Groups;
typedef std::vector<Note> Notes;
typedef std::vector<Reference> References;
typedef std::vector<Playlist> Playlists;

// *****************************************************************************
std::string xmlrpcValueTypeStr(const xmlrpc_c::value::type_t xmlrpcType);
std::string tipEntityType(const std::string &sgEntityType);
std::string sgEntityType(const std::string &tipEntityType);

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
xmlrpc_c::value toXmlrpcValue(const xmlrpc_c::value &in);

// *****************************************************************************
std::string toStdString(const xmlrpc_c::value &value);
std::string toStdString(const SgMap &map);
std::string toStdString(const SgArray &array);
std::string toStdString(const Strings &strs);
//std::string toStdString(const MethodSignature &sig); // same as Strings
std::string toStdString(const MethodSignatures &sigs);
std::string toStdString(const Show &show);
std::string toStdString(const Shows &shows);
std::string toStdString(const Sequence &sequence);
std::string toStdString(const Sequences &sequences);
std::string toStdString(const Shot &shot);
std::string toStdString(const Shots &shots);
std::string toStdString(const Daily &daily);
std::string toStdString(const Dailies &dailies);
std::string toStdString(const User &user);
std::string toStdString(const Users &users);
std::string toStdString(const Element &element);
std::string toStdString(const Elements &elements);
std::string toStdString(const Asset &asset);
std::string toStdString(const Assets &assets);
std::string toStdString(const Delivery &delivery);
std::string toStdString(const Deliveries &deliveries);
std::string toStdString(const DeliveryItem &deliveryItem);
std::string toStdString(const DeliveryItems &deliveryItems);
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
std::string toStdString(const Reference &referece);
std::string toStdString(const References &references);
std::string toStdString(const Playlist &playlist);
std::string toStdString(const Playlists &playlists);

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const xmlrpc_c::value &value);
std::ostream &operator<<(std::ostream& output, const SgMap &map);
std::ostream &operator<<(std::ostream& output, const SgArray &array);
std::ostream &operator<<(std::ostream& output, const Strings &strs);
//std::ostream &operator<<(std::ostream& output, const MethodSignature &sig); // same as Strings
std::ostream &operator<<(std::ostream& output, const MethodSignatures &sigs);
std::ostream &operator<<(std::ostream& output, const Show &show);
std::ostream &operator<<(std::ostream& output, const Shows &shows);
std::ostream &operator<<(std::ostream& output, const Sequence &sequence);
std::ostream &operator<<(std::ostream& output, const Sequences &sequences);
std::ostream &operator<<(std::ostream& output, const Shot &shot);
std::ostream &operator<<(std::ostream& output, const Shots &shots);
std::ostream &operator<<(std::ostream& output, const Daily &daily);
std::ostream &operator<<(std::ostream& output, const Dailies &dailies);
std::ostream &operator<<(std::ostream& output, const User &user);
std::ostream &operator<<(std::ostream& output, const Users &users);
std::ostream &operator<<(std::ostream& output, const Element &element);
std::ostream &operator<<(std::ostream& output, const Elements &elements);
std::ostream &operator<<(std::ostream& output, const Asset &asset);
std::ostream &operator<<(std::ostream& output, const Assets &assets);
std::ostream &operator<<(std::ostream& output, const Delivery &delivery);
std::ostream &operator<<(std::ostream& output, const Deliveries &deliveries);
std::ostream &operator<<(std::ostream& output, const DeliveryItem &deliveryItem);
std::ostream &operator<<(std::ostream& output, const DeliveryItems &deliveryItems);
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
std::ostream &operator<<(std::ostream& output, const Reference &reference);
std::ostream &operator<<(std::ostream& output, const References &references);
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
            if (entityType == tipEntityType(entityType))
                m_msg += "Shotgun \"" + entityType + "\" entity not found.";
            else
                m_msg += "Shotgun \"" + entityType + "\" (Tippett \"" + tipEntityType(entityType) + "\") entity not found.";
        }
    }

    virtual ~SgEntityNotFoundError() throw() {}
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

#endif    // End #ifdef __TYPE_H__
