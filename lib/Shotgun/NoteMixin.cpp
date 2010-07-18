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
Notes NoteMixin::getNotes(const int limit)
{
    // Dynamic_cast can cast it to the other base class of this class' 
    // derived class.
    if (Entity *entity = dynamic_cast<Entity *>(this))
    {
        SgArray noteLinks;
        noteLinks.push_back(toXmlrpcValue(entity->asLink()));

        return entity->sg()->findNotesByLinks(noteLinks, 
                                              "", // noteType
                                              "", // projectCode - unnecessary in this case
                                              limit);
    }
    else
    {
        throw SgEntityDynamicCastError("Entity");
    }
}

// *****************************************************************************
Notes NoteMixin::getDisclaimerNotes(const int limit)
{
    Notes notes = getNotes();

    Notes outNotes;
    for (size_t i = 0; i < notes.size(); i++)
    {
        if (notes[i].sgType() == "Disclaimer")
        {
            outNotes.push_back(notes[i]);

            if (outNotes.size() >= limit) break;
        }
    }

    return outNotes;
}

// *****************************************************************************
Notes NoteMixin::getClientNotes(const int limit)
{
    Notes notes = getNotes();

    Notes outNotes;
    for (size_t i = 0; i < notes.size(); i++)
    {
        if (notes[i].sgType() == "Client")
        {
            outNotes.push_back(notes[i]);

            if (outNotes.size() >= limit) break;
        }
    }

    return outNotes;
}

// *****************************************************************************
Note NoteMixin::addNote(const std::string &noteFromUserName,
                        const Strings &noteToUserNames,
                        const Strings &noteCcUserNames,
                        const std::string &noteSubject,
                        const std::string &noteBody,
                        const std::string &noteType,
                        const SgArray &noteLinks,
                        const std::string &noteOrigin)
{
    if (Entity *entity = dynamic_cast<Entity *>(this))
    {
        // Add extra entity-specific note links
        SgArray links = noteLinks;
        if (entity->entityType() == "Version") // Daily
        {
            if (Daily *daily = dynamic_cast<Daily *>(this))
            {
                try
                {
                    Shot shot = daily->sgShot();
                    links.push_back(toXmlrpcValue(shot.asLink()));
                }
                catch (SgEntityNotFoundError)
                {
                    // Do nothing
                }
            }
            else
            {
                throw SgEntityDynamicCastError("Daily");
            }
        }
        else if (entity->entityType() == "Asset")
        {
            links.push_back(toXmlrpcValue(entity->asLink()));
        }

        return entity->sg()->createNote(entity->sgProjectCode(),
                                        noteFromUserName,
                                        noteToUserNames,
                                        noteCcUserNames,
                                        noteSubject,
                                        noteBody,
                                        noteType,
                                        links,
                                        noteOrigin);
    }
    else
    {
        throw SgEntityDynamicCastError("Entity");
    }
}

} // End namespace Shotgun
