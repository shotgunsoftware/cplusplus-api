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

#include <iostream>

#include <time.h>

#include <Shotgun/Type.h>
#include <Shotgun/FilterBy.h>
#include <Shotgun/SortBy.h>
#include <Shotgun/List.h>
#include <Shotgun/Project.h>
#include <Shotgun/Sequence.h>
#include <Shotgun/Shot.h>
#include <Shotgun/Version.h>
#include <Shotgun/HumanUser.h>
#include <Shotgun/Element.h>
#include <Shotgun/Asset.h>
#include <Shotgun/Delivery.h>
#include <Shotgun/PublishEvent.h>
#include <Shotgun/Review.h>
#include <Shotgun/ReviewItem.h>
#include <Shotgun/Task.h>
#include <Shotgun/Group.h>
#include <Shotgun/Note.h>
#include <Shotgun/Playlist.h>

namespace Shotgun {

// *****************************************************************************
std::string xmlrpcValueTypeStr(const xmlrpc_c::value::type_t xmlrpcType)
{
    switch (xmlrpcType)
    {
        case xmlrpc_c::value::TYPE_INT:
            return std::string("TYPE_INT");
        case xmlrpc_c::value::TYPE_BOOLEAN:
            return std::string("TYPE_BOOLEAN");
        case xmlrpc_c::value::TYPE_DOUBLE:
            return std::string("TYPE_DOUBLE");
        case xmlrpc_c::value::TYPE_DATETIME:
            return std::string("TYPE_DATETIME");
        case xmlrpc_c::value::TYPE_STRING:
            return std::string("TYPE_STRING");
        case xmlrpc_c::value::TYPE_BYTESTRING:
            return std::string("TYPE_BYTESTRING");
        case xmlrpc_c::value::TYPE_ARRAY:
            return std::string("TYPE_ARRAY");
        case xmlrpc_c::value::TYPE_STRUCT:
            return std::string("TYPE_STRUCT");
        case xmlrpc_c::value::TYPE_C_PTR:
            return std::string("TYPE_C_PTR");
        case xmlrpc_c::value::TYPE_NIL:
            return std::string("TYPE_NIL");
        case xmlrpc_c::value::TYPE_DEAD:
        default:
            return std::string("TYPE_DEAD");
    }
}

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const char *in)
{
    return xmlrpc_c::value(xmlrpc_c::value_string(std::string(in)));
}

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const std::string &in)
{
    return xmlrpc_c::value(xmlrpc_c::value_string(in));
}

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const int &in)
{
    return xmlrpc_c::value(xmlrpc_c::value_int(in));
}

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const double &in)
{
    return xmlrpc_c::value(xmlrpc_c::value_double(in));
}

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const bool &in)
{
    return xmlrpc_c::value(xmlrpc_c::value_boolean(in));
}

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const time_t &in)
{
    return xmlrpc_c::value(xmlrpc_c::value_datetime(in));
}

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const SgArray &in)
{
    return xmlrpc_c::value(xmlrpc_c::value_array(in));
}

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const SgMap &in)
{
    return xmlrpc_c::value(xmlrpc_c::value_struct(in));
}

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const Strings &in)
{
    SgArray strArray;
   
    for (size_t i = 0; i < in.size(); i++)
    {
        strArray.push_back(toXmlrpcValue(in[i]));
    }

    return xmlrpc_c::value(xmlrpc_c::value_array(strArray));
}

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const MethodSignatures &in)
{
    SgArray strArray;
   
    for (size_t i = 0; i < in.size(); i++)
    {
        strArray.push_back(toXmlrpcValue(in[i]));
    }

    return xmlrpc_c::value(xmlrpc_c::value_array(strArray));
}

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const FilterBy &in)
{
    return xmlrpc_c::value(xmlrpc_c::value_struct(in.filters()));
}

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const SortBy &in)
{
    return xmlrpc_c::value(xmlrpc_c::value_array(in.sorts()));
}

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const List &in)
{
    return xmlrpc_c::value(xmlrpc_c::value_array(in.value()));
}

// *****************************************************************************
xmlrpc_c::value toXmlrpcValue(const xmlrpc_c::value &in)
{
    return in;
}

// *****************************************************************************
std::string toStdString(const xmlrpc_c::value &value)
{
    static int depth = 0;
    
    std::string output;
    char str[1024];

    if (value.type() == xmlrpc_c::value::TYPE_INT)
    { 
        sprintf(str, "%d", int(xmlrpc_c::value_int(value)));
        output = str;
    }
    else if (value.type() == xmlrpc_c::value::TYPE_BOOLEAN)
    {
        sprintf(str, "%d", bool(xmlrpc_c::value_boolean(value)));
        output = str;
    }
    else if (value.type() == xmlrpc_c::value::TYPE_DOUBLE)
    {
        sprintf(str, "%f", double(xmlrpc_c::value_double(value)));
        output = str;
    }
    else if (value.type() == xmlrpc_c::value::TYPE_DATETIME)
    {
        sprintf(str, "%u", time_t(xmlrpc_c::value_datetime(value)));
        output = str;
    }
    else if (value.type() == xmlrpc_c::value::TYPE_STRING)
    {
        output = "\"" + std::string(xmlrpc_c::value_string(value)) + "\"";
    }
    else if (value.type() == xmlrpc_c::value::TYPE_BYTESTRING)
    {
        sprintf(str, "%u", (xmlrpc_c::value_bytestring(value)).length());
        output = str;
    }
    else if (value.type() == xmlrpc_c::value::TYPE_ARRAY)
    {
        std::string whitespace = "    ";
        std::string indent;
        std::string indent2;
        for (size_t l = 0; l < depth; l++)
        {
            indent += whitespace;
        }
        indent2 = indent + whitespace;
        depth++;
        
        // This helps save the current recursive state
        size_t old_depth = depth;

        output = "\n" + indent + "[\n";

        SgArray array = xmlrpc_c::value_array(value).vectorValueValue();
        for (size_t i = 0; i < array.size(); i++)
        {
            if (i == (array.size() - 1))
            {
                output += indent2 + toStdString(array[i]) + "\n";
            }
            else
            {
                output += indent2 + toStdString(array[i]) + ", \n";
            }

            // This restores the current recursive state
            depth = old_depth;
        }

        depth = old_depth - 1;

        output += indent + "]";
    }
    else if (value.type() == xmlrpc_c::value::TYPE_STRUCT)
    {
        std::string whitespace = "    ";
        std::string indent;
        std::string indent2;
        for (size_t l = 0; l < depth; l++)
        {
            indent += whitespace;
        }
        indent2 = indent + whitespace;
        depth++;

        // This helps save the current recursive state
        size_t old_depth = depth;

        output = "\n" + indent + "{\n";

        SgMap map = SgMap(xmlrpc_c::value_struct(value));
        size_t count = 0;
        for (SgMap::const_iterator mIter = map.begin(); mIter != map.end(); mIter++)
        {
            count++;
            if (count == map.size())
            {
                output += indent2 + "\"" + (*mIter).first + "\" : " + toStdString((*mIter).second) + "\n";
            }
            else
            {
                output += indent2 + "\"" + (*mIter).first + "\" : " + toStdString((*mIter).second) + ", \n";
            }

            // This restores the current recursive state
            depth = old_depth;
        }

        depth = old_depth - 1;

        output += indent + "}";
    }
    else if (value.type() == xmlrpc_c::value::TYPE_NIL)
    {
        output = "nil";
    }

    return output;
}

// *****************************************************************************
std::string toStdString(const SgMap &map)
{
    return toStdString(xmlrpc_c::value_struct(map));
}

// *****************************************************************************
std::string toStdString(const SgArray &array)
{
    return toStdString(xmlrpc_c::value_array(array));
}

// *****************************************************************************
std::string toStdString(const Strings &strs)
{
    std::string output = "[";

    if (strs.size() > 0)
    {
        for (size_t i = 0; i < strs.size()-1; i++)
        {
            output += "\"" + strs[i] + "\", ";
        }

        output += "\"" + strs[strs.size()-1] + "\"";
    }

    output += "]";

    return output;
}

// *****************************************************************************
std::string toStdString(const MethodSignatures &sigs)
{
    std::string output = "[";

    if (sigs.size() > 0)
    {
        for (size_t i = 0; i < sigs.size()-1; i++)
        {
            output += toStdString(sigs[i]) + ", ";
        }

        output += toStdString(sigs[sigs.size()-1]);
    }

    output += "]";

    return output;
}

// *****************************************************************************
std::string toStdString(const FilterBy &filterList)
{
    return toStdString(filterList.filters());
}

// *****************************************************************************
std::string toStdString(const SortBy &order)
{
    return toStdString(order.sorts());
}

// *****************************************************************************
std::string toStdString(const List &list)
{
    return toStdString(list.value());
}

// *****************************************************************************
std::string toStdString(const Project &project)
{
    return toStdString(project.attrs());
}

// *****************************************************************************
std::string toStdString(const Projects &projects)
{
#if 0
    std::string output = "\n[";

    if (projects.size() > 0)
    {
        for (size_t i = 0; i < projects.size()-1; i++)
        {
            output += toStdString(projects[i].attrs()) + ",\n";
        }

        output += toStdString(projects[projects.size()-1].attrs());
    }

    output += "\n]\n";

    return output;
#else
    // The std::string of xmlrpc_c::value type has been formatted very well.
    // So convert it to xmlrpc_c::value first.
    SgArray array;
    for (size_t i = 0; i < projects.size(); i++)
    {
        array.push_back(projects[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
#endif
}

// *****************************************************************************
std::string toStdString(const Sequence &sequence)
{
    return toStdString(sequence.attrs());
}

// *****************************************************************************
std::string toStdString(const Sequences &sequences)
{
    SgArray array;
    for (size_t i = 0; i < sequences.size(); i++)
    {
        array.push_back(sequences[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
}

// *****************************************************************************
std::string toStdString(const Shot &shot)
{
    return toStdString(shot.attrs());
}

// *****************************************************************************
std::string toStdString(const Shots &shots)
{
    SgArray array;
    for (size_t i = 0; i < shots.size(); i++)
    {
        array.push_back(shots[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
}

// *****************************************************************************
std::string toStdString(const Version &version)
{
    return toStdString(version.attrs());
}

// *****************************************************************************
std::string toStdString(const Versions &versions)
{
    SgArray array;
    for (size_t i = 0; i < versions.size(); i++)
    {
        array.push_back(versions[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
}

// *****************************************************************************
std::string toStdString(const HumanUser &user)
{
    return toStdString(user.attrs());
}

// *****************************************************************************
std::string toStdString(const HumanUsers &users)
{
    SgArray array;
    for (size_t i = 0; i < users.size(); i++)
    {
        array.push_back(users[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
}

// *****************************************************************************
std::string toStdString(const Element &element)
{
    return toStdString(element.attrs());
}

// *****************************************************************************
std::string toStdString(const Elements &elements)
{
    SgArray array;
    for (size_t i = 0; i < elements.size(); i++)
    {
        array.push_back(elements[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
}

// *****************************************************************************
std::string toStdString(const Asset &asset)
{
    return toStdString(asset.attrs());
}

// *****************************************************************************
std::string toStdString(const Assets &assets)
{
    SgArray array;
    for (size_t i = 0; i < assets.size(); i++)
    {
        array.push_back(assets[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
}

// *****************************************************************************
std::string toStdString(const Delivery &delivery)
{
    return toStdString(delivery.attrs());
}

// *****************************************************************************
std::string toStdString(const Deliveries &deliveries)
{
    SgArray array;
    for (size_t i = 0; i < deliveries.size(); i++)
    {
        array.push_back(deliveries[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
}

// *****************************************************************************
std::string toStdString(const PublishEvent &publishEvent)
{
    return toStdString(publishEvent.attrs());
}

// *****************************************************************************
std::string toStdString(const PublishEvents &publishEvents)
{
    SgArray array;
    for (size_t i = 0; i < publishEvents.size(); i++)
    {
        array.push_back(publishEvents[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
}

// *****************************************************************************
std::string toStdString(const Review &review)
{
    return toStdString(review.attrs());
}

// *****************************************************************************
std::string toStdString(const Reviews &reviews)
{
    SgArray array;
    for (size_t i = 0; i < reviews.size(); i++)
    {
        array.push_back(reviews[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
}

// *****************************************************************************
std::string toStdString(const ReviewItem &reviewItem)
{
    return toStdString(reviewItem.attrs());
}

// *****************************************************************************
std::string toStdString(const ReviewItems &reviewItems)
{
    SgArray array;
    for (size_t i = 0; i < reviewItems.size(); i++)
    {
        array.push_back(reviewItems[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
}

// *****************************************************************************
std::string toStdString(const Task &task)
{
    return toStdString(task.attrs());
}

// *****************************************************************************
std::string toStdString(const Tasks &tasks)
{
    SgArray array;
    for (size_t i = 0; i < tasks.size(); i++)
    {
        array.push_back(tasks[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
}

// *****************************************************************************
std::string toStdString(const Group &group)
{
    return toStdString(group.attrs());
}

// *****************************************************************************
std::string toStdString(const Groups &groups)
{
    SgArray array;
    for (size_t i = 0; i < groups.size(); i++)
    {
        array.push_back(groups[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
}

// *****************************************************************************
std::string toStdString(const Note &note)
{
    return toStdString(note.attrs());
}

// *****************************************************************************
std::string toStdString(const Notes &notes)
{
    SgArray array;
    for (size_t i = 0; i < notes.size(); i++)
    {
        array.push_back(notes[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
}

// *****************************************************************************
std::string toStdString(const Playlist &playlist)
{
    return toStdString(playlist.attrs());
}

// *****************************************************************************
std::string toStdString(const Playlists &playlists)
{
    SgArray array;
    for (size_t i = 0; i < playlists.size(); i++)
    {
        array.push_back(playlists[i].attrs());
    }
    
    return toStdString(toXmlrpcValue(array));
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const xmlrpc_c::value &value)
{
    output << toStdString(value);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const SgMap &map)
{
    output << toStdString(map);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const SgArray &array)
{
    output << toStdString(array);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Strings &strs)
{
    output << toStdString(strs);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const MethodSignatures &sigs)
{
    output << toStdString(sigs);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Project &project)
{
    output << toStdString(project);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Projects &projects)
{
    output << toStdString(projects);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Sequence &sequence)
{
    output << toStdString(sequence);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Sequences &sequences)
{
    output << toStdString(sequences);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Shot &shot)
{
    output << toStdString(shot);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Shots &shots)
{
    output << toStdString(shots);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Version &version)
{
    output << toStdString(version);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Versions &versions)
{
    output << toStdString(versions);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const HumanUser &user)
{
    output << toStdString(user);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const HumanUsers &users)
{
    output << toStdString(users);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Element &element)
{
    output << toStdString(element);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Elements &elements)
{
    output << toStdString(elements);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Asset &asset)
{
    output << toStdString(asset);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Assets &assets)
{
    output << toStdString(assets);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Delivery &delivery)
{
    output << toStdString(delivery);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Deliveries &deliveries)
{
    output << toStdString(deliveries);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const PublishEvent &publishEvent)
{
    output << toStdString(publishEvent);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const PublishEvents &publishEvents)
{
    output << toStdString(publishEvents);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Review &review)
{
    output << toStdString(review);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Reviews &reviews)
{
    output << toStdString(reviews);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const ReviewItem &reviewItem)
{
    output << toStdString(reviewItem);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const ReviewItems &reviewItems)
{
    output << toStdString(reviewItems);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Task &task)
{
    output << toStdString(task);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Tasks &tasks)
{
    output << toStdString(tasks);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Group &group)
{
    output << toStdString(group);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Groups &groups)
{
    output << toStdString(groups);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Note &note)
{
    output << toStdString(note);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Notes &notes)
{
    output << toStdString(notes);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Playlist &playlist)
{
    output << toStdString(playlist);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Playlists &playlists)
{
    output << toStdString(playlists);
    return output;
}

// *****************************************************************************
std::string currDateStr()
{
    // Get the current time
    time_t rawTime;
    time(&rawTime);

    // Convert to a time string
    struct tm *timeInfo = localtime(&rawTime);
    char timeStr[10];
    sprintf(timeStr, "%d-%02d-%02d", timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday);

    return std::string(timeStr);
}

} // End namespace Shotgun

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const xmlrpc_c::value &value)
{
    output << Shotgun::toStdString(value);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Shotgun::SgArray &array)
{
    output << Shotgun::toStdString(array);
    return output;
}

// *****************************************************************************
std::ostream &operator<<(std::ostream& output, const Shotgun::SgMap &map)
{
    output << Shotgun::toStdString(map);
    return output;
}


