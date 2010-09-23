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
class Dict;

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
xmlrpc_c::value toXmlrpcValue(const Dict &in);
xmlrpc_c::value toXmlrpcValue(const xmlrpc_c::value &in);

// *****************************************************************************
// The template approach won't work since xmlrpc_c::value has to be casted to a
// specific derived xmlrpc_c::value type first, which the compiler doesn't like.
#if 0
template <typename T>
T fromXmlrpcValue(const xmlrpc_c::value &value);
#endif

void fromXmlrpcValue(const xmlrpc_c::value &value, char *out);
void fromXmlrpcValue(const xmlrpc_c::value &value, std::string &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, int &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, double &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, bool &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, time_t &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, SgArray &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, SgMap &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, Strings &out);
//void fromXmlrpcValue(const xmlrpc_c::value &value, MethodSignatures &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, FilterBy &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, SortBy &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, List &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, Dict &out);
void fromXmlrpcValue(const xmlrpc_c::value &value, xmlrpc_c::value &out);

// *****************************************************************************
// Utility func
std::string currDateStr();

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const xmlrpc_c::value &value);
std::string toStdString(const Shotgun::SgArray &array);
std::string toStdString(const Shotgun::SgMap &map);
std::string toStdString(const Shotgun::Strings &strs);
std::string toStdString(const Shotgun::MethodSignatures &sigs);

std::ostream &operator<<(std::ostream& output, const xmlrpc_c::value &value);
std::ostream &operator<<(std::ostream& output, const Shotgun::SgMap &map);
std::ostream &operator<<(std::ostream& output, const Shotgun::SgArray &array);
std::ostream &operator<<(std::ostream& output, const Shotgun::Strings &strs);
std::ostream &operator<<(std::ostream& output, const Shotgun::MethodSignatures &sigs);

#endif    // End #ifdef __TYPE_H__
