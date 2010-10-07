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

#include <Shotgun/NoteMixin.h>
#include <Shotgun/Shotgun.h>
#include <Shotgun/Entity.h>
#include <Shotgun/Shot.h>

namespace Shotgun {

// *****************************************************************************
NotePtrs NoteMixin::getNotes(const int limit)
{
    // Dynamic_cast can cast it to the other base class of this class' 
    // derived class.
    if (Entity *entity = dynamic_cast<Entity *>(this))
    {
        FilterBy filterList = FilterBy("project", "is", entity->sg()->getProjectLink(entity->sgProjectCode()))
                                  .And("note_links", "is", entity->asLink());

        return entity->sg()->findEntities<Note>(filterList, limit);
    }
    else
    {
        throw SgEntityDynamicCastError("Entity");
    }
}

// *****************************************************************************
NotePtrs NoteMixin::getDisclaimerNotes(const int limit)
{
    NotePtrs notes = getNotes();

    NotePtrs outNotes;
    for (size_t i = 0; i < notes.size(); i++)
    {
        if (notes[i]->sgType() == "Disclaimer")
        {
            outNotes.push_back(notes[i]);

            if (outNotes.size() >= limit) break;
        }
    }

    return outNotes;
}

// *****************************************************************************
NotePtrs NoteMixin::getClientNotes(const int limit)
{
    NotePtrs notes = getNotes();

    NotePtrs outNotes;
    for (size_t i = 0; i < notes.size(); i++)
    {
        if (notes[i]->sgType() == "Client")
        {
            outNotes.push_back(notes[i]);

            if (outNotes.size() >= limit) break;
        }
    }

    return outNotes;
}

// *****************************************************************************
Note *NoteMixin::addNote(const std::string &noteFromUserName,
                         const Strings &noteToUserNames,
                         const Strings &noteCcUserNames,
                         const std::string &noteSubject,
                         const std::string &noteBody,
                         const std::string &noteType,
                         const List &noteLinks,
                         const std::string &noteOrigin)
{
    if (Entity *entity = dynamic_cast<Entity *>(this))
    {
        // Add extra entity-specific note links
        List links = noteLinks;

        if (entity->entityType() == "Version")
        {
            if (Version *version = dynamic_cast<Version *>(this))
            {
                try
                {
                    const Shot *shot = version->sgShot();
                    links.append(shot->asLink());
                    delete shot;
                }
                catch (SgEntityNotFoundError)
                {
                    // Do nothing
                }
            }
            else
            {
                throw SgEntityDynamicCastError("Version");
            }
        }
        else if (entity->entityType() == "Asset")
        {
            links.append(entity->asLink());
        }

        // Prepare the data for creating a Note entity
        HumanUser *user = entity->sg()->findEntity<HumanUser>(FilterBy("login", "is", noteFromUserName));
        Dict attrsMap = Dict("project", entity->sg()->getProjectLink(entity->sgProjectCode()))
                        .add("user", user->asLink())
                        .add("subject", noteSubject)
                        .add("content", noteBody)
                        .add("sg_note_type", noteType)
                        .add("sg_note_origin", noteOrigin);
        delete user;

        if (links.size() > 0)
        {
            attrsMap.add("note_links", links);
        }


        // "addressings_to"
        List addressingsTo;
        for (size_t i = 0; i < noteToUserNames.size(); i++)
        {
            try
            {
                HumanUser *toUser = entity->sg()->findEntity<HumanUser>(FilterBy("login", "is", noteToUserNames[i]));
                addressingsTo.append(toUser->asLink());

                delete toUser;
            }
            catch (SgEntityNotFoundError)
            {
                // Do nothing
            }
        }
        attrsMap.add("addressings_to", addressingsTo);

        // "addressings_cc"
        List addressingsCc;
        for (size_t i = 0; i < noteCcUserNames.size(); i++)
        {
            try
            {
                HumanUser *toUser = entity->sg()->findEntity<HumanUser>(FilterBy("login", "is", noteCcUserNames[i]));
                addressingsCc.append(toUser->asLink());
    
                delete toUser;
            }
            catch (SgEntityNotFoundError)
            {
                // Do nothing
            }
        }
        attrsMap.add("addressings_cc", addressingsCc);

        return entity->sg()->createEntity<Note>(attrsMap);
    }
    else
    {
        throw SgEntityDynamicCastError("Entity");
    }
}

} // End namespace Shotgun
