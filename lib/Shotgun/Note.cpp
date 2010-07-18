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

#include <Shotgun/Method.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Note.h>
#include <Shotgun/Project.h>
#include <Shotgun/Review.h>
#include <Shotgun/Shot.h>
#include <Shotgun/Daily.h>

namespace Shotgun {

// *****************************************************************************
Note::Note(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Note";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Note::Note()
    : Entity(NULL)
{
    m_type = "Note";
    m_attrs = NULL;
}

// *****************************************************************************
Note::Note(const Note &ref)
    : Entity(ref.m_sg)
{
    m_type = "Note";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Note::~Note()
{
    // Nothing
}

// *****************************************************************************
Note Note::create(Shotgun *sg, 
                  const std::string &projectCode,
                  const std::string &noteFromUserName,
                  const Strings &noteToUserNames,
                  const Strings &noteCcUserNames,
                  const std::string &noteSubject,
                  const std::string &noteBody,
                  const std::string &noteType,
                  const SgArray &noteLinks,
                  const std::string &noteOrigin)
{
    Project project = sg->findProjectByCode(projectCode);
    User user = sg->findUserByLogin(noteFromUserName);

    SgMap attrsMap;
    attrsMap["project"] = toXmlrpcValue(project.asLink());
    attrsMap["user"] = toXmlrpcValue(user.asLink());
    attrsMap["subject"] = toXmlrpcValue(noteSubject);
    attrsMap["content"] = toXmlrpcValue(noteBody);
    attrsMap["sg_note_type"] = toXmlrpcValue(noteType);
    attrsMap["sg_note_origin"] = toXmlrpcValue(noteOrigin);
    
    if (noteLinks.size() > 0)
    {
        attrsMap["note_links"] = toXmlrpcValue(noteLinks);
    }

    // "addressings_to"
    SgArray addressingsTo;
    for (size_t i = 0; i < noteToUserNames.size(); i++)
    {
        try
        {
            User toUser = sg->findUserByLogin(noteToUserNames[i]);

            addressingsTo.push_back(toXmlrpcValue(toUser.asLink()));
        }
        catch (SgEntityNotFoundError)
        {
            // Do nothing
        }
    }
    attrsMap["addressings_to"] = toXmlrpcValue(addressingsTo);

    // "addressings_cc"
    SgArray addressingsCc;
    for (size_t i = 0; i < noteCcUserNames.size(); i++)
    {
        try
        {
            User toUser = sg->findUserByLogin(noteCcUserNames[i]);

            addressingsCc.push_back(toXmlrpcValue(toUser.asLink()));
        }
        catch (SgEntityNotFoundError)
        {
            // Do nothing
        }
    }
    attrsMap["addressings_cc"] = toXmlrpcValue(addressingsCc);


    // Call the base class function to create an entity
    return Note(sg, createEntity(sg, "Note", attrsMap));
}

// *****************************************************************************
Notes Note::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create a Note for each of them
    Notes notes;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            notes.push_back(Note(sg, result[i]));
        }
    }

    return notes;
}

// *****************************************************************************
const Review Note::getLinkedReview() const
{
    SgArray links = sgLinks();

    for (size_t i = 0; i < links.size(); i++)
    {
        SgMap linkAsMap = SgMap(xmlrpc_c::value_struct(links[i]));

        int id = Entity::getAttrValueAsInt("id", linkAsMap);
        std::string type = Entity::getAttrValueAsString("type", linkAsMap);

        if (type == "Review")
        {
            return Review(m_sg, 
                          findOneEntityBySingleFilter(m_sg, type, "id", "is", toXmlrpcValue(id)));
        }
    }

    throw SgEntityNotFoundError("Review");
}

// *****************************************************************************
const Shot Note::getLinkedShot() const
{
    SgArray links = sgLinks();

    for (size_t i = 0; i < links.size(); i++)
    {
        SgMap linkAsMap = SgMap(xmlrpc_c::value_struct(links[i]));

        int id = Entity::getAttrValueAsInt("id", linkAsMap);
        std::string type = Entity::getAttrValueAsString("type", linkAsMap);

        if (type == "Shot")
        {
            return Shot(m_sg, 
                        findOneEntityBySingleFilter(m_sg, type, "id", "is", toXmlrpcValue(id)));
        }
    }

    throw SgEntityNotFoundError("Shot");
}

// *****************************************************************************
const Daily Note::getLinkedDaily() const
{
    SgArray links = sgLinks();

    for (size_t i = 0; i < links.size(); i++)
    {
        SgMap linkAsMap = SgMap(xmlrpc_c::value_struct(links[i]));

        int id = Entity::getAttrValueAsInt("id", linkAsMap);
        std::string type = Entity::getAttrValueAsString("type", linkAsMap);

        if (type == "Version")
        {
            return Daily(m_sg, 
                         findOneEntityBySingleFilter(m_sg, type, "id", "is", toXmlrpcValue(id)));
        }
    }

    throw SgEntityNotFoundError("Version");
}

} // End namespace Shotgun
