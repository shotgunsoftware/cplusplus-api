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

#ifndef __NOTE_MIXIN_H__
#define __NOTE_MIXIN_H__

#include <string>

#include <Shotgun/Note.h>

namespace Shotgun {

// *****************************************************************************
/// \class NoteMixin
/// A NoteMixin class is used as "add-on"s to any entity class that shares a
/// common set of Note-related functions. The entity class needs to derive
/// from the NoteMixin class.
class NoteMixin
{
public:
    /// A destructor that does nothing.
    virtual ~NoteMixin() {};

    /// Returns an array of Note entities which link to the current entity.
    NotePtrs getNotes(const int limit = 0);

    /// Returns an array of "Disclaimer" type Note entities which link to the 
    /// current entity.
    NotePtrs getDisclaimerNotes(const int limit = 0);

    /// Returns an array of "Client" type Note entities which link to the 
    /// current entity.
    NotePtrs getClientNotes(const int limit = 0);

    /// Creates a new Note entity with data from the current entity.
    Note *addNote(const std::string &noteFromUserName,
                  const Strings &noteToUserNames = Strings(),
                  const Strings &noteCcUserNames = Strings(),
                  const std::string &noteSubject = "",
                  const std::string &noteBody = "",
                  const std::string &noteType = "",
                  const List &noteLinks = List(),
                  const std::string &noteOrigin = "");

protected:
    /// A constructor that does nothing.
    NoteMixin() {}

};

} // End namespace Shotgun

#endif    // End #ifdef __NOTE_MIXIN_H__
