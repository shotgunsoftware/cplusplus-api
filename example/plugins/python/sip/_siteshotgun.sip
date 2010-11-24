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

// *****************************************************************************
// NOTES: The differences between using %Include and %Import directives.
//
// %Include _shotgun.sip
//
//    (1) It takes longer when compiling since it compiles all the .sip files
//        included in "_shotgun.sip".
//
//    (2) It allows Python correctly catches the exceptions thrown by the
//        virtual functions defined only in the base class of the base library
//        but not redefined in the derived class of the derived library.
//
//    (3) Different namespaces (e.g. "SG" and "SiteSG") are both defined in 
//        "_siteshotgun" module. So, in Python apps, only "_siteshotgun" module 
//        needs to be imported.
//
//    (4) This directive has to be put BEFORE "%Module _siteshotgun 0".
//        Otherwise, the %Module directive that is embedded in "_shotgun.sip"
//        will override the one in this file.
//        
// %Import _shotgun.sip
//
//    (1) It takes less time when compiling since the .sip files included
//        in "_shotgun.sip" will not need to be recompiled.
//
//    (2) Python will not be able to catch the exceptions thrown by the
//        virtual functions defined only in the base class of the base library
//        but not redefined in the derived class of the derived library.
//        In order for Python to catch such exceptions, those functions can
//        NOT be declared as "virtual".
//
//    (3) Namespace "SG" is defined in "_shotgun" module while namespace "SiteSG"
//        is defined in "_siteshotgun" module. Therefore, both modules need to
//        be imported into Python apps.
//   
//    (4) This directive can be put BEFORE or AFTER the %Module directive.
// *****************************************************************************

%Include _shotgun.sip

%Module _siteshotgun 0

//%Import _shotgun.sip

%Include SiteProject.sip
%Include SiteReference.sip
%Include SiteShotgun.sip
