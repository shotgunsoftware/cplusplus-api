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

#include <Shotgun/Entity.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Note.h>

namespace Shotgun {

// *****************************************************************************
Note::Note(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Note";
    m_attrs = new xmlrpc_c::value(attrs);
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
Note *Note::create(Shotgun *sg, 
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
    HumanUser *user = sg->findHumanUserByLogin(noteFromUserName);

    SgMap attrsMap;
    attrsMap["project"] = toXmlrpcValue(sg->getProjectLink(projectCode));
    attrsMap["user"] = toXmlrpcValue(user->asLink());
    attrsMap["subject"] = toXmlrpcValue(noteSubject);
    attrsMap["content"] = toXmlrpcValue(noteBody);
    attrsMap["sg_note_type"] = toXmlrpcValue(noteType);
    attrsMap["sg_note_origin"] = toXmlrpcValue(noteOrigin);
    
    delete user;

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
            HumanUser *toUser = sg->findHumanUserByLogin(noteToUserNames[i]);
            addressingsTo.push_back(toXmlrpcValue(toUser->asLink()));

            delete toUser;
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
            HumanUser *toUser = sg->findHumanUserByLogin(noteCcUserNames[i]);
            addressingsCc.push_back(toXmlrpcValue(toUser->asLink()));

            delete toUser;
        }
        catch (SgEntityNotFoundError)
        {
            // Do nothing
        }
    }
    attrsMap["addressings_cc"] = toXmlrpcValue(addressingsCc);

    return sg->createEntity<Note>(Dict(attrsMap));
}

// *****************************************************************************
SgArray Note::populateReturnFields(const SgArray &extraReturnFields)
{
    SgArray returnFields = extraReturnFields;

    returnFields.push_back(toXmlrpcValue("id"));
    returnFields.push_back(toXmlrpcValue("project"));
    returnFields.push_back(toXmlrpcValue("created_at"));
    returnFields.push_back(toXmlrpcValue("updated_at"));

    returnFields.push_back(toXmlrpcValue("user"));
    returnFields.push_back(toXmlrpcValue("content"));
    returnFields.push_back(toXmlrpcValue("addressings_cc"));
    returnFields.push_back(toXmlrpcValue("addressings_to"));
    returnFields.push_back(toXmlrpcValue("sg_status_list"));
    returnFields.push_back(toXmlrpcValue("subject"));
    returnFields.push_back(toXmlrpcValue("sg_note_type"));
    returnFields.push_back(toXmlrpcValue("note_links"));

    return returnFields;
}

// *****************************************************************************
Review *Note::getLinkedReview()
{
    SgArray links = sgLinks();

    for (size_t i = 0; i < links.size(); i++)
    {
        SgMap linkAsMap = SgMap(xmlrpc_c::value_struct(links[i]));
        int id = Entity::getAttrValueAsInt("id", linkAsMap);

        return m_sg->findEntity<Review>(FilterBy("id", "is", id));
    }

    throw SgEntityNotFoundError("Review");
}

// *****************************************************************************
Shot *Note::getLinkedShot()
{
    SgArray links = sgLinks();

    for (size_t i = 0; i < links.size(); i++)
    {
        SgMap linkAsMap = SgMap(xmlrpc_c::value_struct(links[i]));
        int id = Entity::getAttrValueAsInt("id", linkAsMap);

        return m_sg->findEntity<Shot>(FilterBy("id", "is", id));
    }

    throw SgEntityNotFoundError("Shot");
}

// *****************************************************************************
Version *Note::getLinkedVersion() 
{
    SgArray links = sgLinks();

    for (size_t i = 0; i < links.size(); i++)
    {
        SgMap linkAsMap = SgMap(xmlrpc_c::value_struct(links[i]));
        int id = Entity::getAttrValueAsInt("id", linkAsMap);

        return m_sg->findEntity<Version>(FilterBy("id", "is", id));
    }

    throw SgEntityNotFoundError("Version");
}

} // End namespace Shotgun

// *****************************************************************************
// *****************************************************************************
std::string toStdString(const Shotgun::Note &note)
{
    return toStdString(note.attrs());
}

// *****************************************************************************
std::string toStdString(const Shotgun::Notes &notes)
{
    Shotgun::SgArray array;
    for (size_t i = 0; i < notes.size(); i++)
    {
        array.push_back(notes[i].attrs());
    }
    
    return toStdString(Shotgun::toXmlrpcValue(array));
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Note &note)
{
    output << toStdString(note);
    return output;
}

// *****************************************************************************
std::ostream& operator<<(std::ostream &output, const Shotgun::Notes &notes)
{
    output << toStdString(notes);
    return output;
}
