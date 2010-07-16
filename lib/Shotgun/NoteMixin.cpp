//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

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
                                              "", // showCode - unnecessary in this case
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

        return entity->sg()->createNote(entity->sgShowCode(),
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
