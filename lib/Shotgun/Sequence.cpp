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
#include <Shotgun/Sequence.h>
#include <Shotgun/Project.h>
#include <Shotgun/utils.h>

namespace Shotgun {

// *****************************************************************************
Sequence::Sequence(Shotgun *sg, const xmlrpc_c::value &attrs)
    : Entity(sg)
{
    m_type = "Sequence";
    m_attrs = new xmlrpc_c::value(attrs);
}

// *****************************************************************************
Sequence::Sequence(const Sequence &ref)
    : Entity(ref.m_sg)
{
    m_type = "Sequence";
    m_attrs = new xmlrpc_c::value(*ref.m_attrs);
}

// *****************************************************************************
Sequence::~Sequence()
{
    // Nothing
}

// *****************************************************************************
Sequence Sequence::create(Shotgun *sg, 
                          const std::string &projectCode,
                          const std::string &sequenceName)
{
    // By convention, the sequence name is in uppercase
    std::string sequenceNameUpper = toupper(sequenceName);

    // Check if the sequence already exists
    try
    {
        Sequence seq = sg->findSequenceByName(projectCode, sequenceNameUpper);

        std::string err = "Sequence \"" + sequenceNameUpper + "\" already exists for project \"" + projectCode + "\"";
        throw SgEntityCreateError(err);
    }
    catch (SgEntityNotFoundError)
    {
        Project project = sg->findProjectByCode(projectCode);

        SgMap attrsMap;
        attrsMap["project"] = toXmlrpcValue(project.asLink());
        attrsMap["code"] = toXmlrpcValue(sequenceNameUpper);

        // Call the base class function to create an entity
        return Sequence(sg, createEntity(sg, "Sequence", attrsMap));
    }
}

// *****************************************************************************
Sequences Sequence::find(Shotgun *sg, SgMap &findMap)
{
    // Find the entities that match the findMap and create a Sequence for each of them
    Sequences sequences;

    SgArray result = Entity::findEntities(sg, findMap);
    if (result.size() > 0)
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            sequences.push_back(Sequence(sg, result[i]));
        }
    }

    return sequences;
}

} // End namespace Shotgun
