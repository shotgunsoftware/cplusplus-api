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

#ifndef __SHOT_H__
#define __SHOT_H__

#include <string>

#include <Shotgun/Entity.h>
#include <Shotgun/TaskMixin.h>
#include <Shotgun/NoteMixin.h>

namespace SG {

class Shotgun;

// *****************************************************************************
/// \class Shot
class Shot : public Entity, public TaskMixin, public NoteMixin
{
    friend class Shotgun;
 
public:
    /// A copy constructor.
    Shot(const Shot &ref);

    /// A destructor that does nothing.
    virtual ~Shot();

    /// The string representation of Shot entity type.
    static std::string type() { return std::string("Shot"); }

    // -------------------------------------------------------------------------
    Shot &operator=(const Shot &that)
    {
        if (this != &that)
        {
            Entity::operator=(that);
        }

        return *this;
    }

    // -------------------------------------------------------------------------
    friend std::ostream& operator<<(std::ostream &output, const Shot &shot)
    {
        output << shot.str();
        return output;
    }

protected:
    /// A constructor.
    ///
    /// \param sg - instantiated Shotgun object pointer
    /// \param attrs - raw attribute map for a Shotgun entity
    Shot(Shotgun *sg, const xmlrpc_c::value &attrs);

    /// A Shot entity factory function.
    ///
    /// \param sg - instantiated Shotgun object pointer
    /// \param attrs - raw attribute map for a Shotgun entity
    /// \return a newly-created Shot * as its base Entity * type
    static Entity *factory(Shotgun *sg, const xmlrpc_c::value &attrs) { return new Shot(sg, attrs); }

    /// Builds a list of default "return_fields" which are the attributes
    /// exposed to the users when a Shot entity is created or searched.
    ///
    /// \return a list of default "return_fields" name strings.
    static List defaultReturnFields();
};

// *****************************************************************************
typedef std::vector<Shot *> ShotPtrs;

} // End namespace SG

#endif    // End #ifdef __SHOT_H__
