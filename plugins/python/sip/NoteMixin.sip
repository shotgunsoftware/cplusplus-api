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

namespace Shotgun {

// *****************************************************************************
class NoteMixin
{
%TypeHeaderCode
    #include <Shotgun/NoteMixin.h>
%End

public:
    virtual ~NoteMixin();

    Shotgun::NotePtrs getNotes(const int limit = 0) throw(Shotgun::SgError) /Factory/;
    Shotgun::NotePtrs getDisclaimerNotes(const int limit = 0) throw(Shotgun::SgError) /Factory/;
    Shotgun::NotePtrs getClientNotes(const int limit = 0) throw(Shotgun::SgError) /Factory/;

    Shotgun::Note *addNote(const std::string &noteFromUserName,
                           const Shotgun::Strings &noteToUserNames = Shotgun::Strings(),
                           const Shotgun::Strings &noteCcUserNames = Shotgun::Strings(),
                           const std::string &noteSubject = "",
                           const std::string &noteBody = "",
                           const std::string &noteType = "",
                           const Shotgun::List &noteLinks = Shotgun::List(),
                           const std::string &noteOrigin = "") throw(Shotgun::SgError) /Factory/;

protected:
    NoteMixin();

};

}; // End namespace Shotgun
