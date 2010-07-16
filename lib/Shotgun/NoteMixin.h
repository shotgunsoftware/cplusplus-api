//******************************************************************************
// Copyright (c) 2010 Tippett Studio. All rights reserved.
// $Id$
//******************************************************************************

#ifndef __NOTE_MIXIN_H__
#define __NOTE_MIXIN_H__

#include <string>

#include <Shotgun/Type.h>
#include <Shotgun/Note.h>

namespace Shotgun {

// *****************************************************************************
class NoteMixin
{
protected:
    NoteMixin() {}

public:
    virtual ~NoteMixin() {};

    Notes getNotes(const int limit = 0);
    Notes getDisclaimerNotes(const int limit = 0);
    Notes getClientNotes(const int limit = 0);

    Note addNote(const std::string &noteFromUserName,
                 const Strings &noteToUserNames = Strings(),
                 const Strings &noteCcUserNames = Strings(),
                 const std::string &noteSubject = "",
                 const std::string &noteBody = "",
                 const std::string &noteType = "",
                 const SgArray &noteLinks = SgArray(),
                 const std::string &noteOrigin = "");
};

} // End namespace Shotgun

#endif    // End #ifdef __NOTE_MIXIN_H__
